1. A docker container is an isolated process on the machine.
2. A container shares the host's operating system while a virtual machine uses it's own guest operating system.
3. Dockerfile is used to create and run an image
4. Requirements.txt contains all dependencies that need to be installed for the application to function. 
5. Define, Create, and Run all services in one command. Compose can define the startup order and runs the services together in an isolated environment.
6. A docker image is a template with instructions for creating a container. A container is a runnable instance of the image.
7. docker build
8. docker container start containerName
9. docker container stop containerName
10. container: docker container rm containerName 
10. image: docker rmi imageName
11. container running: docker container ls
11. container all: docker container ls -a
12. docker images
13. docker-compose up --build
14. network_mode: host
15. build: ./pathToDockerfile