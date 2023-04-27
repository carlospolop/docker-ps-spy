# Docker ps-spy

This is a container that will **monitor each process executed inside the container using pspy** and saving the results in `/var/log/pspy.log`.

This is useful in environments where:

1. You can configure the Docker image to use
2. Something interesting happens inside the container when it's run and you want to figure out what

This Docker image is public in **docker.io/carlospolop/docker-ps-spy:v3**


**REMEMBER TO CHANGE THE VALUES OF `REMOTE_ADDR` and `REMOTE_PORT` in the `Dockerfile` with the hostname and port to egt the reverse shell**

```bash
# Build
docker build -t docker-ps-spy . 

# Just running bash pspy should be executed and you should get a reverse shell
docker run -it docker-ps-spy bash

# Upload to docker hub 
docker login
docker tag docker-ps-spy carlospolop/docker-ps-spy:vX # Change X
docker docker push carlospolop/docker-ps-spy:vX # Change X
```
