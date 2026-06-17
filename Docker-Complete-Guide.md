# Complete Docker Mastery Guide - From Zero to Expert

> A comprehensive, hands-on guide covering everything you need to know about Docker -- from fundamentals to advanced topics -- with practical exercises and interview preparation.

---

## PART 1: FUNDAMENTALS

---

### 1. What is Docker?

Docker is an open-source platform that automates the deployment, scaling, and management of applications using **containerization**. It packages an application and all its dependencies into a standardized unit called a **container**.

#### Containers vs Virtual Machines

```
+--------------------------------------------------+
|              VIRTUAL MACHINES                     |
+--------------------------------------------------+
|  +----------+  +----------+  +----------+        |
|  |  App A   |  |  App B   |  |  App C   |        |
|  +----------+  +----------+  +----------+        |
|  | Bins/Libs|  | Bins/Libs|  | Bins/Libs|        |
|  +----------+  +----------+  +----------+        |
|  | Guest OS |  | Guest OS |  | Guest OS |        |
|  +----------+  +----------+  +----------+        |
|  +--------------------------------------+        |
|  |           HYPERVISOR                  |        |
|  +--------------------------------------+        |
|  +--------------------------------------+        |
|  |           HOST OS                     |        |
|  +--------------------------------------+        |
|  +--------------------------------------+        |
|  |           HARDWARE                    |        |
|  +--------------------------------------+        |
+--------------------------------------------------+

+--------------------------------------------------+
|              CONTAINERS                           |
+--------------------------------------------------+
|  +----------+  +----------+  +----------+        |
|  |  App A   |  |  App B   |  |  App C   |        |
|  +----------+  +----------+  +----------+        |
|  | Bins/Libs|  | Bins/Libs|  | Bins/Libs|        |
|  +----------+  +----------+  +----------+        |
|  +--------------------------------------+        |
|  |         CONTAINER RUNTIME             |        |
|  |         (Docker Engine)               |        |
|  +--------------------------------------+        |
|  +--------------------------------------+        |
|  |           HOST OS                     |        |
|  +--------------------------------------+        |
|  +--------------------------------------+        |
|  |           HARDWARE                    |        |
|  +--------------------------------------+        |
+--------------------------------------------------+
```

| Feature | Containers | Virtual Machines |
|---------|-----------|-----------------|
| Boot time | Seconds | Minutes |
| Size | MBs | GBs |
| Performance | Near-native | Overhead from hypervisor |
| OS | Shares host kernel | Full guest OS |
| Isolation | Process-level | Hardware-level |
| Portability | Highly portable | Less portable |
| Density | Hundreds per host | Tens per host |

#### Docker Architecture

```
+-----------------------------------------------------------+
|                     DOCKER CLIENT                          |
|                  (docker CLI / API)                        |
|                       |                                    |
|                       | REST API                           |
|                       v                                    |
|              +------------------+                          |
|              |  DOCKER DAEMON   |  (dockerd)               |
|              |                  |                          |
|              |  +------------+  |                          |
|              |  | containerd |  |  (container runtime)     |
|              |  |     |      |  |                          |
|              |  |  +--v---+  |  |                          |
|              |  |  | runc |  |  |  (OCI runtime)           |
|              |  |  +------+  |  |                          |
|              |  +------------+  |                          |
|              +------------------+                          |
|                    |        |                              |
|              +-----+        +------+                       |
|              |                     |                       |
|     +--------v--------+  +--------v--------+              |
|     |   IMAGES         |  |   CONTAINERS    |              |
|     |   VOLUMES        |  |   NETWORKS      |              |
|     +-----------------+  +-----------------+              |
+-----------------------------------------------------------+
```

- **Docker Client (CLI):** The command-line tool users interact with. Sends commands to the Docker daemon via REST API.
- **Docker Daemon (dockerd):** Background service that manages Docker objects. Listens for API requests.
- **containerd:** Industry-standard container runtime that manages the complete container lifecycle.
- **runc:** Low-level OCI-compliant container runtime that actually creates and runs containers.

#### Docker Objects

- **Images:** Read-only templates used to create containers. Built from Dockerfiles in layers.
- **Containers:** Runnable instances of images. Isolated processes with their own filesystem, networking, and process space.
- **Networks:** Enable communication between containers and the outside world.
- **Volumes:** Persistent data storage that outlives containers.

#### Interview Q&A

**Q: What is the difference between Docker and a virtual machine?**
A: Docker containers share the host OS kernel and isolate applications at the process level, making them lightweight (MBs) and fast to start (seconds). VMs run a full guest OS on a hypervisor, providing hardware-level isolation but consuming more resources (GBs) and taking minutes to start.

**Q: What is the role of containerd and runc?**
A: containerd is a high-level container runtime that manages the full container lifecycle (image transfer, storage, execution, supervision). runc is a low-level OCI runtime that creates and runs containers using Linux kernel features like namespaces and cgroups. Docker daemon uses containerd, which in turn uses runc.

**Q: Can Docker containers run on any OS?**
A: Docker containers share the host kernel. Linux containers run on Linux hosts (or via a Linux VM on Windows/Mac). Windows containers run on Windows hosts. Docker Desktop on Mac/Windows runs a lightweight Linux VM behind the scenes.

---

### 2. Docker Installation & Setup

#### Installing on Linux (Ubuntu/Debian)

```bash
# Remove old versions
sudo apt-get remove docker docker-engine docker.io containerd runc

# Install prerequisites
sudo apt-get update
sudo apt-get install ca-certificates curl gnupg lsb-release

# Add Docker official GPG key
sudo mkdir -p /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg

# Set up repository
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] \
  https://download.docker.com/linux/ubuntu \
  $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

# Install Docker Engine
sudo apt-get update
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

# Add user to docker group (avoid sudo)
sudo usermod -aG docker $USER
newgrp docker
```

#### Installing on Windows

1. Download Docker Desktop from https://www.docker.com/products/docker-desktop
2. Run the installer (enable WSL 2 backend when prompted)
3. Restart the computer
4. Launch Docker Desktop

#### Installing on Mac

```bash
# Using Homebrew
brew install --cask docker

# Or download Docker Desktop from the website
```

#### Docker Desktop vs Docker Engine

| Feature | Docker Desktop | Docker Engine |
|---------|---------------|---------------|
| Platform | Windows, Mac, Linux | Linux only |
| GUI | Yes | No (CLI only) |
| Includes | Engine + Compose + BuildKit + Kubernetes | Engine only |
| License | Free for personal/small business, paid for large enterprise | Free and open source |
| VM | Runs Linux VM on Win/Mac | Native on Linux |

#### Verifying Installation

```bash
# Check Docker version
docker version

# Check Docker system info
docker info

# Run test container
docker run hello-world
```

**Expected output from hello-world:**
```
Hello from Docker!
This message shows that your installation appears to be working correctly.
...
```

#### Practical Exercises

```bash
# Exercise 1: Explore Docker info
docker version
docker info

# Exercise 2: Run hello-world and understand the output
docker run hello-world

# Exercise 3: Check running containers
docker ps

# Exercise 4: Check all containers (including stopped)
docker ps -a

# Exercise 5: Remove the hello-world container
docker rm $(docker ps -a -q --filter ancestor=hello-world)
```

---

### 3. Docker Images

#### What Are Images?

A Docker image is a read-only template containing application code, runtime, libraries, environment variables, and configuration files. Images are built in **layers**, where each instruction in a Dockerfile creates a new layer.

#### Union Filesystem and Layers

```
+---------------------------+
|    Writable Container     |  <-- Container layer (read-write)
|         Layer             |
+---------------------------+
|    Layer 5: CMD           |  <-- Read-only
+---------------------------+
|    Layer 4: COPY app      |  <-- Read-only
+---------------------------+
|    Layer 3: RUN npm       |  <-- Read-only
+---------------------------+
|    Layer 2: WORKDIR       |  <-- Read-only
+---------------------------+
|    Layer 1: FROM node:18  |  <-- Base image (read-only)
+---------------------------+
```

Each layer only stores the **differences** from the layer below. This makes images space-efficient and shareable -- multiple images can share common base layers.

#### Core Image Commands

```bash
# Pull an image from Docker Hub
docker pull nginx
docker pull nginx:1.25          # Specific version
docker pull nginx:alpine        # Alpine variant (smaller)

# List local images
docker images
docker image ls

# List with filtering
docker images --filter "dangling=true"
docker images --format "table {{.Repository}}\t{{.Tag}}\t{{.Size}}"

# Remove an image
docker rmi nginx
docker image rm nginx:1.25

# Remove all unused images
docker image prune              # Remove dangling images
docker image prune -a           # Remove all unused images

# Inspect image details
docker image inspect nginx
docker image inspect nginx --format '{{.Config.ExposedPorts}}'

# View image layer history
docker image history nginx

# Tag an image
docker tag nginx:latest myregistry/nginx:v1.0
docker tag nginx:latest myregistry/nginx:prod

# Save image to tar file
docker save -o nginx-backup.tar nginx:latest

# Load image from tar file
docker load -i nginx-backup.tar

# Search Docker Hub
docker search nginx
docker search --filter stars=50 nginx
```

#### Image Tagging and Versioning

```bash
# Format: registry/repository:tag
# Examples:
docker pull ubuntu:22.04
docker pull docker.io/library/ubuntu:22.04    # Full path
docker pull myregistry.com:5000/myapp:v2.1

# The 'latest' tag is just a convention -- it is NOT automatically the newest
docker pull nginx            # Same as docker pull nginx:latest

# Best practice: always use specific tags in production
docker pull node:18-alpine   # Specific version + variant
docker pull python:3.11-slim
```

#### Docker Hub and Registries

Docker Hub is the default public registry. Images are stored as `username/repository:tag`.

```bash
# Login to Docker Hub
docker login

# Push an image
docker tag myapp:latest username/myapp:v1.0
docker push username/myapp:v1.0

# Pull from a private registry
docker pull myregistry.com:5000/myapp:latest
```

#### Practical Exercises

```bash
# Exercise 1: Pull and compare image sizes
docker pull nginx:latest
docker pull nginx:alpine
docker images nginx
# Notice the size difference between latest and alpine

# Exercise 2: Inspect image layers
docker image history nginx:latest
docker image history nginx:alpine

# Exercise 3: Tag and organize images
docker tag nginx:alpine myapp/webserver:v1
docker tag nginx:alpine myapp/webserver:production
docker images myapp/webserver

# Exercise 4: Save and load an image
docker save -o /tmp/nginx-alpine.tar nginx:alpine
docker rmi nginx:alpine
docker load -i /tmp/nginx-alpine.tar
docker images nginx

# Exercise 5: Inspect image configuration
docker image inspect nginx:latest --format '{{.Config.Cmd}}'
docker image inspect nginx:latest --format '{{.Config.ExposedPorts}}'
docker image inspect nginx:latest --format '{{.RootFS.Layers}}'

# Exercise 6: Clean up
docker image prune -a --force
```

#### Interview Q&A

**Q: What is a Docker image layer?**
A: Each instruction in a Dockerfile creates a new read-only layer. Layers are stacked using a union filesystem. Only changed data is stored in each layer, making images efficient. When a container runs, a writable layer is added on top.

**Q: What is a dangling image?**
A: A dangling image is one that is not tagged and not referenced by any container. They typically result from rebuilding an image with the same tag. Clean them with `docker image prune`.

**Q: What is the difference between `docker rmi` and `docker image prune`?**
A: `docker rmi` removes specific images by name/ID. `docker image prune` removes all dangling (untagged, unreferenced) images. With `-a`, it removes all images not used by any container.

---

### 4. Docker Containers

#### Container Lifecycle

```
                docker create
                     |
                     v
    +----------+  docker start  +----------+
    |  CREATED | ------------> |  RUNNING  |<-----+
    +----------+               +----------+      |
                                |    |    |       |
                       docker   |    |    | docker|
                       pause    |    |    |restart|
                                v    |    |       |
                           +--------+|    +-------+
                           | PAUSED ||
                           +--------+|
                       docker        |
                       unpause       |
                                     |
                               docker stop / docker kill
                                     |
                                     v
                              +-----------+
                              |  STOPPED  |
                              +-----------+
                                     |
                               docker rm
                                     |
                                     v
                              +-----------+
                              |  DELETED  |
                              +-----------+
```

#### docker run -- All Important Flags

```bash
# Basic run
docker run nginx

# Run in detached mode (background)
docker run -d nginx

# Run with interactive terminal
docker run -it ubuntu bash

# Run with a name
docker run -d --name my-nginx nginx

# Auto-remove container when it exits
docker run --rm ubuntu echo "Hello"

# Port mapping: -p host_port:container_port
docker run -d -p 8080:80 nginx
docker run -d -p 8080:80 -p 8443:443 nginx

# Volume mount
docker run -d -v mydata:/data nginx                  # Named volume
docker run -d -v /host/path:/container/path nginx     # Bind mount
docker run -d -v /host/path:/container/path:ro nginx  # Read-only bind mount

# Environment variables
docker run -d -e MYSQL_ROOT_PASSWORD=secret mysql
docker run -d --env-file .env myapp

# Network
docker run -d --network my-network nginx

# Restart policy
docker run -d --restart always nginx
docker run -d --restart unless-stopped nginx
docker run -d --restart on-failure:5 nginx

# Resource constraints
docker run -d --memory 512m nginx
docker run -d --cpus 1.5 nginx
docker run -d --memory 512m --cpus 1.5 nginx

# Working directory
docker run -d -w /app node:18

# User
docker run -d --user 1000:1000 nginx

# Hostname
docker run -d --hostname myhost nginx

# Combined real-world example
docker run -d \
  --name production-web \
  -p 80:80 \
  -p 443:443 \
  -v /data/nginx/conf:/etc/nginx/conf.d:ro \
  -v /data/nginx/html:/usr/share/nginx/html:ro \
  -e NGINX_HOST=example.com \
  --restart unless-stopped \
  --memory 256m \
  --cpus 0.5 \
  --network frontend \
  nginx:1.25-alpine
```

#### Container Management Commands

```bash
# List running containers
docker ps

# List all containers (including stopped)
docker ps -a

# List with custom format
docker ps --format "table {{.Names}}\t{{.Status}}\t{{.Ports}}"

# Stop a container (sends SIGTERM, then SIGKILL after grace period)
docker stop my-nginx
docker stop -t 30 my-nginx     # 30-second grace period

# Start a stopped container
docker start my-nginx

# Restart a container
docker restart my-nginx

# Pause / Unpause (freezes processes using cgroups)
docker pause my-nginx
docker unpause my-nginx

# Kill a container (sends SIGKILL immediately)
docker kill my-nginx
docker kill -s SIGTERM my-nginx

# Remove a container
docker rm my-nginx
docker rm -f my-nginx          # Force remove (even if running)

# Remove all stopped containers
docker container prune

# Execute a command in a running container
docker exec my-nginx ls /etc/nginx
docker exec -it my-nginx bash
docker exec -it my-nginx sh          # For alpine images
docker exec -u root my-nginx whoami  # As specific user

# Attach to a running container (attach to PID 1 process)
docker attach my-nginx
# Detach with Ctrl+P, Ctrl+Q

# View container logs
docker logs my-nginx
docker logs -f my-nginx              # Follow (tail -f)
docker logs --tail 100 my-nginx      # Last 100 lines
docker logs --since 2h my-nginx      # Last 2 hours
docker logs --timestamps my-nginx    # Show timestamps

# View container resource usage
docker stats
docker stats my-nginx
docker stats --no-stream              # Snapshot (no live update)

# View running processes in container
docker top my-nginx

# Copy files between host and container
docker cp my-nginx:/etc/nginx/nginx.conf ./nginx.conf
docker cp ./index.html my-nginx:/usr/share/nginx/html/

# Inspect container details
docker inspect my-nginx
docker inspect my-nginx --format '{{.NetworkSettings.IPAddress}}'
docker inspect my-nginx --format '{{.State.Status}}'
docker inspect my-nginx --format '{{json .Mounts}}'

# View container filesystem changes
docker diff my-nginx

# Create image from container
docker commit my-nginx my-custom-nginx:v1

# Rename a container
docker rename my-nginx web-server

# Wait for container to exit and return exit code
docker wait my-nginx

# Export container filesystem to tar
docker export my-nginx -o container-fs.tar
```

#### Practical Exercises

```bash
# Exercise 1: Run an Nginx web server
docker run -d --name web -p 8080:80 nginx
# Visit http://localhost:8080 in your browser
docker logs web
docker stop web && docker rm web

# Exercise 2: Interactive Ubuntu container
docker run -it --name myubuntu ubuntu bash
# Inside the container:
#   apt-get update && apt-get install -y curl
#   curl --version
#   exit
docker rm myubuntu

# Exercise 3: Run MySQL with environment variables
docker run -d \
  --name mydb \
  -e MYSQL_ROOT_PASSWORD=rootpass \
  -e MYSQL_DATABASE=testdb \
  -e MYSQL_USER=testuser \
  -e MYSQL_PASSWORD=testpass \
  -p 3306:3306 \
  mysql:8
# Wait a few seconds for MySQL to initialize
docker logs mydb
docker exec -it mydb mysql -utestuser -ptestpass testdb
# Inside MySQL: SHOW DATABASES; then exit
docker stop mydb && docker rm mydb

# Exercise 4: Container resource monitoring
docker run -d --name stress-test --memory 128m --cpus 0.5 nginx
docker stats stress-test --no-stream
docker inspect stress-test --format '{{.HostConfig.Memory}}'
docker stop stress-test && docker rm stress-test

# Exercise 5: Copy files to/from containers
docker run -d --name web nginx
echo "<h1>Hello Docker</h1>" > /tmp/index.html
docker cp /tmp/index.html web:/usr/share/nginx/html/index.html
docker exec web cat /usr/share/nginx/html/index.html
docker stop web && docker rm web

# Exercise 6: Container lifecycle walkthrough
docker create --name lifecycle nginx
docker ps -a --filter name=lifecycle                # Status: Created
docker start lifecycle
docker ps --filter name=lifecycle                   # Status: Up
docker pause lifecycle
docker ps --filter name=lifecycle                   # Status: Paused
docker unpause lifecycle
docker stop lifecycle
docker ps -a --filter name=lifecycle                # Status: Exited
docker rm lifecycle
```

#### Interview Q&A

**Q: What is the difference between `docker stop` and `docker kill`?**
A: `docker stop` sends SIGTERM to the main process, giving it a grace period (default 10 seconds) to shut down gracefully. If the process does not exit, it sends SIGKILL. `docker kill` sends SIGKILL immediately, forcing the process to terminate without cleanup.

**Q: What is the difference between `docker exec` and `docker attach`?**
A: `docker exec` starts a new process inside a running container (e.g., a new shell). `docker attach` connects your terminal to the container's PID 1 (main process). With attach, pressing Ctrl+C may stop the container; with exec, it only stops the exec process.

**Q: What happens when a container's main process exits?**
A: The container stops. A Docker container runs as long as its PID 1 process is alive. When that process exits, the container transitions to "Exited" state. The `--restart` policy can control whether it restarts automatically.

**Q: What is the difference between `docker run` and `docker create`?**
A: `docker create` creates a container but does not start it (state: Created). `docker run` is equivalent to `docker create` + `docker start` + (optionally) `docker attach`.

---

### 5. Dockerfile - Deep Dive

A Dockerfile is a text file containing instructions to build a Docker image.

#### Every Dockerfile Instruction

##### FROM -- Base image

```dockerfile
# Every Dockerfile must start with FROM (except ARG before FROM)
FROM ubuntu:22.04
FROM node:18-alpine
FROM python:3.11-slim
FROM scratch                     # Empty base image (for static binaries)

# Multi-stage: name the stage
FROM node:18 AS builder
FROM nginx:alpine AS production

# ARG before FROM
ARG VERSION=18
FROM node:${VERSION}-alpine
```

##### RUN -- Execute commands during build

```dockerfile
# Shell form (runs in /bin/sh -c)
RUN apt-get update && apt-get install -y curl

# Exec form
RUN ["apt-get", "update"]

# Best practice: chain commands and clean up in one layer
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        curl \
        git \
        vim && \
    rm -rf /var/lib/apt/lists/*
```

##### CMD -- Default command when container starts

```dockerfile
# Exec form (preferred)
CMD ["node", "server.js"]
CMD ["python", "app.py"]

# Shell form
CMD node server.js

# As parameters to ENTRYPOINT
ENTRYPOINT ["python"]
CMD ["app.py"]                   # Default arg; can be overridden at runtime
```

##### ENTRYPOINT -- Container's main executable

```dockerfile
# Exec form (preferred)
ENTRYPOINT ["node", "server.js"]

# Shell form
ENTRYPOINT node server.js

# Combined with CMD for flexible defaults
ENTRYPOINT ["python"]
CMD ["app.py"]
# docker run myimage              -> runs: python app.py
# docker run myimage script.py    -> runs: python script.py
```

##### CMD vs ENTRYPOINT

| Scenario | CMD | ENTRYPOINT |
|----------|-----|------------|
| Override at runtime | `docker run img cmd` replaces CMD entirely | `docker run img args` appends to ENTRYPOINT |
| Purpose | Default command or default args | The fixed executable |
| Shell form | Runs in `/bin/sh -c` | Runs in `/bin/sh -c` (signals not forwarded) |
| Exec form | `CMD ["executable", "arg"]` | `ENTRYPOINT ["executable", "arg"]` |

```dockerfile
# Example: Flexible entrypoint
FROM python:3.11-slim
WORKDIR /app
COPY . .
ENTRYPOINT ["python"]
CMD ["main.py"]

# docker run myapp              -> python main.py
# docker run myapp test.py      -> python test.py
# docker run --entrypoint bash myapp  -> override entrypoint entirely
```

##### COPY vs ADD

```dockerfile
# COPY: Simple file/directory copy (preferred)
COPY package.json .
COPY . /app
COPY --chown=node:node . /app

# ADD: Like COPY but with extra features
ADD app.tar.gz /app              # Auto-extracts tar archives
ADD https://example.com/file /app/file  # Downloads from URL (not recommended)

# Best practice: Use COPY unless you specifically need tar extraction
```

##### WORKDIR -- Set working directory

```dockerfile
WORKDIR /app
# All subsequent RUN, CMD, COPY, ADD use /app as base
RUN pwd    # Output: /app

# Can be used multiple times
WORKDIR /app
WORKDIR src
RUN pwd    # Output: /app/src
```

##### EXPOSE -- Document listening ports

```dockerfile
EXPOSE 80
EXPOSE 443
EXPOSE 3000/tcp
EXPOSE 5000/udp

# Note: EXPOSE does not publish the port. It is documentation only.
# You still need -p at runtime: docker run -p 8080:80 myimage
```

##### ENV -- Set environment variables

```dockerfile
ENV NODE_ENV=production
ENV APP_PORT=3000
ENV DB_HOST=localhost DB_PORT=5432

# Available during build AND at runtime
# Can be overridden: docker run -e NODE_ENV=development myimage
```

##### ARG -- Build-time variables

```dockerfile
ARG NODE_VERSION=18
FROM node:${NODE_VERSION}-alpine

ARG BUILD_DATE
ARG GIT_COMMIT
LABEL build_date=${BUILD_DATE} git_commit=${GIT_COMMIT}

# ARG is only available during build, not at runtime
# Pass values: docker build --build-arg NODE_VERSION=20 .
```

##### LABEL -- Metadata

```dockerfile
LABEL maintainer="dev@example.com"
LABEL version="1.0"
LABEL description="My application image"
LABEL org.opencontainers.image.source="https://github.com/user/repo"
```

##### USER -- Set the user

```dockerfile
# Create a non-root user and switch to it
RUN groupadd -r appuser && useradd -r -g appuser appuser
USER appuser

# Or use numeric UID/GID
USER 1000:1000
```

##### VOLUME -- Create mount point

```dockerfile
VOLUME /data
VOLUME ["/data", "/logs"]

# Creates an anonymous volume at runtime if no volume is explicitly mounted
```

##### HEALTHCHECK -- Container health monitoring

```dockerfile
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
  CMD curl -f http://localhost:3000/health || exit 1

# Disable healthcheck inherited from base image
HEALTHCHECK NONE
```

##### SHELL -- Change default shell

```dockerfile
# Default is ["/bin/sh", "-c"]
SHELL ["/bin/bash", "-c"]
RUN echo "now using bash"

# Useful for Windows containers
SHELL ["powershell", "-Command"]
```

##### STOPSIGNAL -- Set stop signal

```dockerfile
# Default is SIGTERM
STOPSIGNAL SIGQUIT
```

##### ONBUILD -- Trigger for child images

```dockerfile
# These instructions execute when this image is used as a base
ONBUILD COPY . /app
ONBUILD RUN npm install
```

#### .dockerignore

Create a `.dockerignore` file in the build context to exclude files:

```
node_modules
npm-debug.log
.git
.gitignore
.env
Dockerfile
docker-compose.yml
.dockerignore
README.md
.vscode
*.md
__pycache__
*.pyc
.pytest_cache
coverage
.nyc_output
dist
build
```

#### Build Context

The build context is the set of files at the specified path sent to the Docker daemon. Keep it minimal using `.dockerignore`.

```bash
# Current directory as build context
docker build -t myapp .

# Specific directory
docker build -t myapp ./src

# Specify Dockerfile location
docker build -t myapp -f docker/Dockerfile .

# Build from URL
docker build -t myapp https://github.com/user/repo.git
```

#### Multi-Stage Builds

Multi-stage builds let you use multiple FROM statements, keeping the final image small by copying only artifacts you need.

```dockerfile
# Stage 1: Build
FROM node:18 AS builder
WORKDIR /app
COPY package*.json ./
RUN npm ci
COPY . .
RUN npm run build

# Stage 2: Production
FROM nginx:alpine AS production
COPY --from=builder /app/dist /usr/share/nginx/html
EXPOSE 80
CMD ["nginx", "-g", "daemon off;"]
```

**Real-world Go example:**

```dockerfile
# Build stage
FROM golang:1.21 AS builder
WORKDIR /app
COPY go.mod go.sum ./
RUN go mod download
COPY . .
RUN CGO_ENABLED=0 GOOS=linux go build -o /app/server .

# Production stage
FROM scratch
COPY --from=builder /app/server /server
EXPOSE 8080
ENTRYPOINT ["/server"]
```

**Real-world Java example:**

```dockerfile
# Build stage
FROM maven:3.9-eclipse-temurin-17 AS builder
WORKDIR /app
COPY pom.xml .
RUN mvn dependency:go-offline
COPY src ./src
RUN mvn package -DskipTests

# Production stage
FROM eclipse-temurin:17-jre-alpine
WORKDIR /app
COPY --from=builder /app/target/*.jar app.jar
EXPOSE 8080
ENTRYPOINT ["java", "-jar", "app.jar"]
```

#### Build Cache Optimization

Order Dockerfile instructions from least to most frequently changing:

```dockerfile
# GOOD: Dependencies cached separately from source code
FROM node:18-alpine
WORKDIR /app

# These change rarely -- cached
COPY package.json package-lock.json ./
RUN npm ci --production

# This changes often -- only this layer rebuilds
COPY . .

CMD ["node", "server.js"]
```

```dockerfile
# BAD: Every code change invalidates npm install cache
FROM node:18-alpine
WORKDIR /app
COPY . .                  # Any code change busts cache here
RUN npm ci --production   # This runs every time
CMD ["node", "server.js"]
```

#### Best Practices for Dockerfiles

1. **Use specific base image tags** -- not `latest`
2. **Use multi-stage builds** to minimize final image size
3. **Order instructions by change frequency** (least changing first)
4. **Combine RUN commands** with `&&` to reduce layers
5. **Clean up in the same layer** (remove apt cache, temp files)
6. **Use .dockerignore** to exclude unnecessary files
7. **Do not run as root** -- create and switch to a non-root USER
8. **Use COPY instead of ADD** unless you need tar extraction
9. **Use exec form for CMD/ENTRYPOINT** for proper signal handling
10. **Add HEALTHCHECK** for production images

#### Practical Exercises

```bash
# Exercise 1: Build a Node.js app image
mkdir -p /tmp/docker-node-app && cd /tmp/docker-node-app

cat > server.js << 'JSEOF'
const http = require('http');
const server = http.createServer((req, res) => {
  res.writeHead(200, { 'Content-Type': 'text/plain' });
  res.end('Hello from Docker!\n');
});
server.listen(3000, () => console.log('Server running on port 3000'));
JSEOF

cat > package.json << 'PKGEOF'
{
  "name": "docker-demo",
  "version": "1.0.0",
  "main": "server.js",
  "scripts": { "start": "node server.js" }
}
PKGEOF

cat > Dockerfile << 'DKEOF'
FROM node:18-alpine
WORKDIR /app
COPY package.json ./
RUN npm install --production
COPY server.js ./
EXPOSE 3000
USER node
CMD ["node", "server.js"]
DKEOF

docker build -t node-demo .
docker run -d -p 3000:3000 --name node-app node-demo
curl http://localhost:3000
docker stop node-app && docker rm node-app

# Exercise 2: Build a Python Flask app
mkdir -p /tmp/docker-python-app && cd /tmp/docker-python-app

cat > app.py << 'PYEOF'
from flask import Flask
app = Flask(__name__)

@app.route('/')
def hello():
    return 'Hello from Docker Flask App!'

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
PYEOF

cat > requirements.txt << 'REQEOF'
flask==3.0.0
REQEOF

cat > Dockerfile << 'DKEOF'
FROM python:3.11-slim
WORKDIR /app
COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt
COPY app.py ./
EXPOSE 5000
RUN useradd -r appuser && chown -R appuser /app
USER appuser
CMD ["python", "app.py"]
DKEOF

docker build -t flask-demo .
docker run -d -p 5000:5000 --name flask-app flask-demo
curl http://localhost:5000
docker stop flask-app && docker rm flask-app

# Exercise 3: Multi-stage build example
mkdir -p /tmp/docker-multistage && cd /tmp/docker-multistage

cat > Dockerfile << 'DKEOF'
# Stage 1: Build
FROM node:18 AS builder
WORKDIR /app
RUN echo '<h1>Built with Multi-Stage Docker</h1>' > index.html

# Stage 2: Production
FROM nginx:alpine
COPY --from=builder /app/index.html /usr/share/nginx/html/
EXPOSE 80
DKEOF

docker build -t multistage-demo .
docker images multistage-demo    # Note the small image size
docker run -d -p 8080:80 --name ms-app multistage-demo
curl http://localhost:8080
docker stop ms-app && docker rm ms-app
```

#### Interview Q&A

**Q: What is the difference between CMD and ENTRYPOINT?**
A: CMD sets the default command that can be completely overridden at runtime. ENTRYPOINT sets the main executable that cannot be easily overridden (runtime arguments are appended). Use ENTRYPOINT for the main executable and CMD for default arguments.

**Q: What is the difference between COPY and ADD?**
A: Both copy files into the image. ADD has two extra features: it auto-extracts compressed tar archives and can download files from URLs. Best practice is to use COPY unless you specifically need ADD's extra features.

**Q: How does build cache work?**
A: Docker caches each layer. If a layer's instruction and its input files have not changed, Docker reuses the cached layer. If any layer is invalidated, all subsequent layers are also invalidated. This is why you should order instructions from least to most frequently changed.

**Q: What is a multi-stage build and why use it?**
A: Multi-stage builds use multiple FROM statements to create intermediate build stages. Only the final stage becomes the image. This lets you include build tools (compilers, SDKs) in early stages without bloating the production image. A Go app image can go from 800MB to 10MB using multi-stage with scratch.

**Q: What is the difference between shell form and exec form?**
A: Shell form (`CMD command arg`) wraps the command in `/bin/sh -c`, which adds a shell process and may prevent proper signal forwarding. Exec form (`CMD ["command", "arg"]`) runs the command directly as PID 1, enabling proper signal handling. Always use exec form in production.

---

### 6. Docker Volumes & Data Persistence

Containers are ephemeral -- their writable layer is deleted when the container is removed. Volumes provide persistent storage.

#### Types of Mounts

```
+--------------------------------------------------+
|                                                    |
|  +----------+   +----------+   +-----------+      |
|  | Named    |   | Bind     |   | tmpfs     |      |
|  | Volume   |   | Mount    |   | Mount     |      |
|  +----+-----+   +----+-----+   +-----+-----+      |
|       |              |               |              |
|  Managed by     Maps host       In-memory only     |
|  Docker         directory       (Linux only)       |
|  (best for      to container    Never written       |
|  persistence)   (dev use)       to disk             |
|                                                    |
+--------------------------------------------------+
```

| Feature | Named Volume | Bind Mount | tmpfs |
|---------|-------------|------------|-------|
| Location | Docker-managed area | Anywhere on host | Memory only |
| Created by | `docker volume create` or `-v name:/path` | `-v /host/path:/path` | `--tmpfs /path` |
| Managed by Docker | Yes | No | N/A |
| Pre-populated | Yes (from image) | No | No |
| Performance | Good | Depends on host FS | Fastest |
| Use case | Production data | Development, config | Sensitive temp data |

#### Volume Commands

```bash
# Create a named volume
docker volume create mydata
docker volume create --driver local --opt type=nfs mydata-nfs

# List volumes
docker volume ls

# Inspect a volume
docker volume inspect mydata

# Remove a volume
docker volume rm mydata

# Remove all unused volumes
docker volume prune
docker volume prune --all
```

#### Using Volumes with Containers

```bash
# Named volume
docker run -d -v mydata:/data --name vol-test nginx
# Docker creates 'mydata' volume if it does not exist

# Bind mount
docker run -d -v /home/user/website:/usr/share/nginx/html nginx
# Maps host directory into container

# Read-only mount
docker run -d -v /host/config:/etc/app/config:ro nginx

# tmpfs mount
docker run -d --tmpfs /tmp:rw,size=100m nginx

# Using --mount syntax (more explicit, recommended)
docker run -d \
  --mount type=volume,source=mydata,target=/data \
  --name vol-test2 nginx

docker run -d \
  --mount type=bind,source=/home/user/website,target=/usr/share/nginx/html \
  nginx

docker run -d \
  --mount type=tmpfs,target=/tmp,tmpfs-size=100m \
  nginx
```

#### Sharing Data Between Containers

```bash
# Create a shared volume
docker volume create shared-data

# Container 1: writes data
docker run -d -v shared-data:/data --name writer alpine sh -c \
  "while true; do date >> /data/log.txt; sleep 5; done"

# Container 2: reads data
docker run --rm -v shared-data:/data alpine cat /data/log.txt
```

#### Backup and Restore Volumes

```bash
# Backup a volume to a tar file
docker run --rm \
  -v mydata:/source:ro \
  -v /tmp:/backup \
  alpine tar czf /backup/mydata-backup.tar.gz -C /source .

# Restore a volume from a tar file
docker volume create mydata-restored
docker run --rm \
  -v mydata-restored:/target \
  -v /tmp:/backup:ro \
  alpine tar xzf /backup/mydata-backup.tar.gz -C /target
```

#### Practical Exercises

```bash
# Exercise 1: Named volume persistence
docker volume create testdata
docker run --rm -v testdata:/data alpine sh -c "echo 'Hello Volumes' > /data/test.txt"
docker run --rm -v testdata:/data alpine cat /data/test.txt
# The data persists even though the containers were removed

# Exercise 2: Bind mount for development
mkdir -p /tmp/mywebsite
echo "<h1>Live Reload with Bind Mounts</h1>" > /tmp/mywebsite/index.html
docker run -d -p 8080:80 -v /tmp/mywebsite:/usr/share/nginx/html:ro --name devweb nginx
curl http://localhost:8080
# Modify the file on host and refresh
echo "<h1>Updated Content!</h1>" > /tmp/mywebsite/index.html
curl http://localhost:8080
docker stop devweb && docker rm devweb

# Exercise 3: Database with persistent storage
docker volume create pgdata
docker run -d \
  --name postgres \
  -e POSTGRES_PASSWORD=secret \
  -v pgdata:/var/lib/postgresql/data \
  -p 5432:5432 \
  postgres:15
# Stop and remove container, data survives
docker stop postgres && docker rm postgres
# Recreate -- data is still there
docker run -d \
  --name postgres2 \
  -e POSTGRES_PASSWORD=secret \
  -v pgdata:/var/lib/postgresql/data \
  -p 5432:5432 \
  postgres:15
docker stop postgres2 && docker rm postgres2
docker volume rm pgdata

# Exercise 4: Inspect volume details
docker volume create inspectme
docker volume inspect inspectme
docker volume rm inspectme

# Exercise 5: Volume cleanup
docker volume ls
docker volume prune --force
```

#### Interview Q&A

**Q: What is the difference between a named volume and a bind mount?**
A: Named volumes are managed by Docker and stored in Docker's storage area. Bind mounts map a specific host path into the container. Named volumes are portable and Docker handles their lifecycle; bind mounts depend on the host filesystem structure.

**Q: How do you persist database data in Docker?**
A: Use a named volume mapped to the database's data directory. For PostgreSQL: `-v pgdata:/var/lib/postgresql/data`. For MySQL: `-v mysqldata:/var/lib/mysql`. The volume survives container removal.

**Q: What happens to data in a container if the container is removed?**
A: Data in the container's writable layer is lost. Data in volumes (named or bind) persists. This is why volumes are essential for any data that must survive container lifecycle events.

---

### 7. Docker Networking

#### Network Drivers

| Driver | Description | Use Case |
|--------|-------------|----------|
| `bridge` | Default. Isolated network on single host | Standalone containers on same host |
| `host` | Removes network isolation, uses host networking | Performance-sensitive apps, no port mapping needed |
| `none` | No networking | Security-critical containers |
| `overlay` | Multi-host networking (Swarm) | Containers across multiple Docker hosts |
| `macvlan` | Assigns MAC address to container | Legacy apps expecting direct LAN connection |

#### Network Commands

```bash
# List networks
docker network ls

# Create a network
docker network create mynetwork
docker network create --driver bridge --subnet 172.20.0.0/16 mynetwork
docker network create --driver overlay --attachable swarm-net

# Inspect a network
docker network inspect mynetwork
docker network inspect bridge

# Remove a network
docker network rm mynetwork

# Remove all unused networks
docker network prune

# Connect a running container to a network
docker network connect mynetwork mycontainer

# Disconnect a container from a network
docker network disconnect mynetwork mycontainer
```

#### Container DNS Resolution

Containers on the **default bridge** network can only communicate via IP address. Containers on **custom bridge** networks get automatic DNS resolution by container name.

```bash
# Default bridge: NO DNS resolution by name
docker run -d --name web1 nginx
docker run -d --name web2 nginx
# web1 cannot reach web2 by name

# Custom bridge: DNS resolution works
docker network create mynet
docker run -d --name web1 --network mynet nginx
docker run -d --name web2 --network mynet nginx
# web1 can reach web2 by name: curl http://web2
docker exec web1 ping web2      # This works on custom networks
```

#### Port Mapping

```bash
# Specific port mapping
docker run -d -p 8080:80 nginx             # host:8080 -> container:80

# Multiple port mappings
docker run -d -p 8080:80 -p 8443:443 nginx

# Bind to specific interface
docker run -d -p 127.0.0.1:8080:80 nginx   # Only accessible from localhost

# Random host port
docker run -d -P nginx                      # -P publishes all EXPOSE ports to random ports
docker port <container>                      # Show port mappings

# UDP port
docker run -d -p 5000:5000/udp myapp
```

#### Practical Exercises

```bash
# Exercise 1: Container communication on custom network
docker network create app-net

docker run -d --name app-db --network app-net \
  -e POSTGRES_PASSWORD=secret postgres:15-alpine

docker run -d --name app-web --network app-net \
  -p 8080:80 nginx

# Verify DNS resolution
docker exec app-web ping -c 2 app-db

# Cleanup
docker stop app-db app-web
docker rm app-db app-web
docker network rm app-net

# Exercise 2: Isolate containers with separate networks
docker network create frontend
docker network create backend

# Web server on frontend
docker run -d --name web --network frontend -p 80:80 nginx

# Database on backend
docker run -d --name db --network backend \
  -e POSTGRES_PASSWORD=secret postgres:15-alpine

# API on both networks
docker run -d --name api --network backend alpine sleep 3600
docker network connect frontend api

# api can reach both web and db
docker exec api ping -c 1 web    # Works (both on frontend)
docker exec api ping -c 1 db     # Works (both on backend)

# web cannot reach db
# docker exec web ping -c 1 db   # Fails (different networks)

# Cleanup
docker stop web db api
docker rm web db api
docker network rm frontend backend

# Exercise 3: Host networking (Linux only)
docker run -d --network host --name host-nginx nginx
# Nginx is directly on host port 80 -- no port mapping needed
curl http://localhost
docker stop host-nginx && docker rm host-nginx

# Exercise 4: Inspect network details
docker network create inspect-net
docker run -d --name net-test --network inspect-net nginx
docker network inspect inspect-net
docker inspect net-test --format '{{json .NetworkSettings.Networks}}'
docker stop net-test && docker rm net-test
docker network rm inspect-net
```

#### Interview Q&A

**Q: What is the difference between the default bridge and a custom bridge network?**
A: Custom bridge networks provide automatic DNS resolution (containers can reach each other by name), better isolation, and can be connected/disconnected on the fly. The default bridge only allows communication via IP addresses and all containers are on it by default.

**Q: How do containers on different networks communicate?**
A: They cannot communicate directly. To enable communication, either connect a container to both networks (`docker network connect`) or set up routing between the networks.

**Q: What is the host network mode?**
A: Host mode removes network isolation between the container and the host. The container shares the host's network stack directly. No port mapping is needed, but you lose network isolation. Useful for performance-sensitive scenarios. Works only on Linux.

**Q: What is an overlay network?**
A: An overlay network enables communication between containers across multiple Docker hosts. It uses VXLAN to encapsulate traffic. Primarily used with Docker Swarm for multi-host container orchestration.

---

## PART 2: INTERMEDIATE

---

### 8. Docker Compose

Docker Compose defines and runs multi-container applications using a YAML file.

#### docker-compose.yml Structure

```yaml
# docker-compose.yml

services:
  # Frontend service
  frontend:
    build:
      context: ./frontend
      dockerfile: Dockerfile
      args:
        NODE_ENV: production
    image: myapp-frontend:latest
    container_name: frontend
    ports:
      - "3000:3000"
    environment:
      - REACT_APP_API_URL=http://backend:5000
    env_file:
      - ./frontend/.env
    depends_on:
      backend:
        condition: service_healthy
    networks:
      - frontend-net
    restart: unless-stopped
    healthcheck:
      test: ["CMD", "curl", "-f", "http://localhost:3000"]
      interval: 30s
      timeout: 10s
      retries: 3
      start_period: 10s

  # Backend service
  backend:
    build: ./backend
    image: myapp-backend:latest
    container_name: backend
    ports:
      - "5000:5000"
    environment:
      DB_HOST: db
      DB_PORT: 5432
      DB_NAME: myapp
      DB_USER: appuser
      DB_PASSWORD: secret
      REDIS_URL: redis://cache:6379
    depends_on:
      db:
        condition: service_healthy
      cache:
        condition: service_started
    networks:
      - frontend-net
      - backend-net
    volumes:
      - ./backend:/app        # Bind mount for development
      - /app/node_modules     # Anonymous volume to preserve node_modules
    restart: unless-stopped
    healthcheck:
      test: ["CMD", "curl", "-f", "http://localhost:5000/health"]
      interval: 30s
      timeout: 10s
      retries: 3
    deploy:
      resources:
        limits:
          cpus: '1.0'
          memory: 512M
        reservations:
          cpus: '0.5'
          memory: 256M
    logging:
      driver: json-file
      options:
        max-size: "10m"
        max-file: "3"

  # Database service
  db:
    image: postgres:15-alpine
    container_name: db
    environment:
      POSTGRES_DB: myapp
      POSTGRES_USER: appuser
      POSTGRES_PASSWORD: secret
    volumes:
      - pgdata:/var/lib/postgresql/data
      - ./init.sql:/docker-entrypoint-initdb.d/init.sql
    ports:
      - "5432:5432"
    networks:
      - backend-net
    restart: unless-stopped
    healthcheck:
      test: ["CMD-SHELL", "pg_isready -U appuser -d myapp"]
      interval: 10s
      timeout: 5s
      retries: 5

  # Cache service
  cache:
    image: redis:7-alpine
    container_name: cache
    ports:
      - "6379:6379"
    volumes:
      - redisdata:/data
    networks:
      - backend-net
    restart: unless-stopped
    command: redis-server --appendonly yes

volumes:
  pgdata:
    driver: local
  redisdata:
    driver: local

networks:
  frontend-net:
    driver: bridge
  backend-net:
    driver: bridge
```

#### All Important Compose Directives

```yaml
services:
  myservice:
    # Build configuration
    build:
      context: .
      dockerfile: Dockerfile.prod
      args:
        BUILD_ENV: production
      target: production        # Multi-stage build target
      cache_from:
        - myapp:latest

    # Or use a pre-built image
    image: nginx:alpine

    # Container name (default: projectname_service_number)
    container_name: my-container

    # Port mapping
    ports:
      - "8080:80"              # host:container
      - "443:443"
      - "127.0.0.1:9090:9090" # Bind to specific interface

    # Volumes
    volumes:
      - mydata:/data                     # Named volume
      - ./src:/app/src                   # Bind mount
      - ./config:/app/config:ro          # Read-only bind mount
      - type: volume
        source: mydata
        target: /data
        volume:
          nocopy: true

    # Environment variables
    environment:
      NODE_ENV: production
      DB_HOST: db
    # Or as a list
    environment:
      - NODE_ENV=production
      - DB_HOST=db

    # Environment file
    env_file:
      - .env
      - .env.production

    # Dependencies
    depends_on:
      - db
      - cache
    # With health conditions
    depends_on:
      db:
        condition: service_healthy
      cache:
        condition: service_started

    # Restart policy
    restart: "no"              # never restart
    restart: always            # always restart
    restart: on-failure        # only on failure
    restart: unless-stopped    # unless manually stopped

    # Networks
    networks:
      - frontend
      - backend
    networks:
      frontend:
        aliases:
          - web
        ipv4_address: 172.20.0.10

    # Override CMD
    command: ["npm", "run", "dev"]
    command: npm run dev

    # Override ENTRYPOINT
    entrypoint: ["/entrypoint.sh"]

    # Healthcheck
    healthcheck:
      test: ["CMD", "curl", "-f", "http://localhost/health"]
      interval: 30s
      timeout: 10s
      retries: 3
      start_period: 40s
      start_interval: 5s

    # Resource limits (compose v3 with deploy)
    deploy:
      replicas: 3
      resources:
        limits:
          cpus: '0.50'
          memory: 512M
        reservations:
          cpus: '0.25'
          memory: 128M
      restart_policy:
        condition: on-failure
        delay: 5s
        max_attempts: 3

    # Labels
    labels:
      com.example.description: "My web app"
      com.example.department: "Engineering"

    # Logging
    logging:
      driver: json-file
      options:
        max-size: "10m"
        max-file: "5"

    # Working directory
    working_dir: /app

    # User
    user: "1000:1000"

    # Hostname
    hostname: myhost

    # DNS
    dns:
      - 8.8.8.8
      - 8.8.4.4

    # Extra hosts
    extra_hosts:
      - "host.docker.internal:host-gateway"

    # Capabilities
    cap_add:
      - NET_ADMIN
    cap_drop:
      - ALL

    # Read-only root filesystem
    read_only: true

    # tmpfs
    tmpfs:
      - /tmp
      - /run

    # Profiles (only start with --profile)
    profiles:
      - debug
```

#### Compose CLI Commands

```bash
# Start all services (detached)
docker compose up -d

# Start specific services
docker compose up -d backend db

# Build/rebuild images
docker compose build
docker compose build --no-cache
docker compose up -d --build     # Build and start

# Stop services
docker compose stop

# Stop and remove containers, networks
docker compose down

# Stop, remove containers, networks, volumes, and images
docker compose down -v --rmi all

# List running services
docker compose ps
docker compose ps -a             # Including stopped

# View logs
docker compose logs
docker compose logs -f backend   # Follow specific service
docker compose logs --tail 50    # Last 50 lines

# Execute command in a service
docker compose exec backend bash
docker compose exec db psql -U appuser myapp

# Run a one-off command
docker compose run --rm backend npm test

# Scale a service
docker compose up -d --scale backend=3

# Restart services
docker compose restart
docker compose restart backend

# Pull latest images
docker compose pull

# View configuration (merged and validated)
docker compose config
```

#### Multiple Compose Files and Overrides

```bash
# docker-compose.yml        -- base configuration
# docker-compose.override.yml  -- automatically merged (for development)
# docker-compose.prod.yml   -- production overrides

# Development (auto-merges override file)
docker compose up -d

# Production (explicitly specify files)
docker compose -f docker-compose.yml -f docker-compose.prod.yml up -d
```

**docker-compose.yml (base):**
```yaml
services:
  web:
    build: .
    ports:
      - "3000:3000"
```

**docker-compose.override.yml (dev):**
```yaml
services:
  web:
    volumes:
      - .:/app
    environment:
      NODE_ENV: development
    command: npm run dev
```

**docker-compose.prod.yml (prod):**
```yaml
services:
  web:
    environment:
      NODE_ENV: production
    restart: always
    deploy:
      replicas: 3
```

#### Compose Profiles

```yaml
services:
  web:
    image: nginx

  debug-tools:
    image: alpine
    profiles:
      - debug
    command: sleep infinity

  monitoring:
    image: prom/prometheus
    profiles:
      - monitoring
```

```bash
# Only starts 'web' (no profile)
docker compose up -d

# Starts web + debug-tools
docker compose --profile debug up -d

# Starts web + monitoring
docker compose --profile monitoring up -d

# Starts everything
docker compose --profile debug --profile monitoring up -d
```

#### Practical Exercise: Full-Stack Application

```bash
# Create project directory
mkdir -p /tmp/fullstack-app && cd /tmp/fullstack-app

# Create backend
mkdir -p backend
cat > backend/server.js << 'EOF'
const express = require('express');
const { Pool } = require('pg');
const redis = require('redis');

const app = express();
const pool = new Pool({
  host: process.env.DB_HOST || 'db',
  port: 5432,
  database: process.env.DB_NAME || 'myapp',
  user: process.env.DB_USER || 'appuser',
  password: process.env.DB_PASSWORD || 'secret'
});

app.get('/api/health', (req, res) => res.json({ status: 'ok' }));
app.get('/api/data', async (req, res) => {
  try {
    const result = await pool.query('SELECT NOW()');
    res.json({ time: result.rows[0].now });
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
});

app.listen(5000, () => console.log('Backend running on port 5000'));
EOF

cat > backend/package.json << 'EOF'
{
  "name": "backend",
  "version": "1.0.0",
  "dependencies": {
    "express": "^4.18.0",
    "pg": "^8.11.0",
    "redis": "^4.6.0"
  }
}
EOF

cat > backend/Dockerfile << 'EOF'
FROM node:18-alpine
WORKDIR /app
COPY package.json ./
RUN npm install
COPY . .
EXPOSE 5000
CMD ["node", "server.js"]
EOF

# Create docker-compose.yml
cat > docker-compose.yml << 'EOF'
services:
  backend:
    build: ./backend
    ports:
      - "5000:5000"
    environment:
      DB_HOST: db
      DB_NAME: myapp
      DB_USER: appuser
      DB_PASSWORD: secret
    depends_on:
      db:
        condition: service_healthy
    networks:
      - app-net
    restart: unless-stopped

  db:
    image: postgres:15-alpine
    environment:
      POSTGRES_DB: myapp
      POSTGRES_USER: appuser
      POSTGRES_PASSWORD: secret
    volumes:
      - pgdata:/var/lib/postgresql/data
    networks:
      - app-net
    restart: unless-stopped
    healthcheck:
      test: ["CMD-SHELL", "pg_isready -U appuser -d myapp"]
      interval: 5s
      timeout: 5s
      retries: 5

  cache:
    image: redis:7-alpine
    networks:
      - app-net
    restart: unless-stopped

volumes:
  pgdata:

networks:
  app-net:
    driver: bridge
EOF

# Launch the stack
docker compose up -d

# Check status
docker compose ps
docker compose logs backend

# Test the API
curl http://localhost:5000/api/health
curl http://localhost:5000/api/data

# Tear down
docker compose down -v
```

#### Interview Q&A

**Q: What is Docker Compose?**
A: Docker Compose is a tool for defining and running multi-container applications. You describe your application's services, networks, and volumes in a YAML file, then bring everything up with a single command (`docker compose up`).

**Q: What is the difference between `docker compose up` and `docker compose run`?**
A: `docker compose up` starts all services defined in the compose file. `docker compose run` starts a single service and runs a one-off command, useful for running tests, migrations, or administrative tasks.

**Q: How does `depends_on` work?**
A: `depends_on` controls startup order. By default, it only waits for the dependency to start (not be ready). With `condition: service_healthy`, it waits for the dependency's healthcheck to pass before starting the dependent service.

**Q: How do you handle secrets in Docker Compose?**
A: Use `env_file` to load from `.env` files (not committed to git), Docker secrets (in Swarm mode), or external secret management tools. Never hard-code secrets in `docker-compose.yml`.

---

### 9. Docker Registry

A Docker registry stores and distributes Docker images. Docker Hub is the default public registry.

#### Docker Hub

```bash
# Login
docker login
docker login -u username

# Push an image
docker tag myapp:latest username/myapp:v1.0
docker push username/myapp:v1.0

# Pull an image
docker pull username/myapp:v1.0

# Logout
docker logout
```

#### Private Registry Setup

```bash
# Run a private registry
docker run -d \
  --name registry \
  -p 5000:5000 \
  --restart always \
  -v registry-data:/var/lib/registry \
  registry:2

# Tag and push to private registry
docker tag myapp:latest localhost:5000/myapp:v1.0
docker push localhost:5000/myapp:v1.0

# Pull from private registry
docker pull localhost:5000/myapp:v1.0

# List images in private registry (API)
curl http://localhost:5000/v2/_catalog
curl http://localhost:5000/v2/myapp/tags/list
```

#### Registry with TLS and Authentication

```bash
# Generate htpasswd file
mkdir -p /tmp/registry/auth
docker run --rm --entrypoint htpasswd httpd:2 \
  -Bbn admin secretpass > /tmp/registry/auth/htpasswd

# Run registry with auth
docker run -d \
  --name secure-registry \
  -p 5000:5000 \
  --restart always \
  -v registry-data:/var/lib/registry \
  -v /tmp/registry/auth:/auth \
  -e "REGISTRY_AUTH=htpasswd" \
  -e "REGISTRY_AUTH_HTPASSWD_REALM=Registry Realm" \
  -e "REGISTRY_AUTH_HTPASSWD_PATH=/auth/htpasswd" \
  registry:2

# Login to private registry
docker login localhost:5000
```

#### Docker Content Trust (Image Signing)

```bash
# Enable content trust
export DOCKER_CONTENT_TRUST=1

# Push a signed image
docker push username/myapp:v1.0    # Will be signed

# Pull only signed images
docker pull username/myapp:v1.0    # Verifies signature

# Disable content trust
export DOCKER_CONTENT_TRUST=0
```

#### Practical Exercises

```bash
# Exercise 1: Set up a local registry
docker run -d -p 5000:5000 --name myregistry registry:2

# Exercise 2: Push and pull images
docker pull alpine:latest
docker tag alpine:latest localhost:5000/my-alpine:v1
docker push localhost:5000/my-alpine:v1
docker rmi localhost:5000/my-alpine:v1
docker pull localhost:5000/my-alpine:v1

# Exercise 3: Query registry API
curl http://localhost:5000/v2/_catalog
curl http://localhost:5000/v2/my-alpine/tags/list

# Cleanup
docker stop myregistry && docker rm myregistry
docker volume prune -f
```

#### Interview Q&A

**Q: What is a Docker registry?**
A: A Docker registry is a storage and distribution system for Docker images. Docker Hub is the default public registry. You can run private registries using the `registry:2` image for internal use.

**Q: How do you secure a private Docker registry?**
A: Use TLS certificates for encrypted communication, htpasswd or LDAP for authentication, and Docker Content Trust for image signing. You can also put a reverse proxy (like Nginx) in front of the registry.

---

### 10. Docker Logging & Monitoring

#### Logging Drivers

```bash
# Check the default logging driver
docker info --format '{{.LoggingDriver}}'

# Run a container with a specific logging driver
docker run -d \
  --log-driver json-file \
  --log-opt max-size=10m \
  --log-opt max-file=3 \
  nginx

# Available logging drivers:
# json-file   - Default. JSON-formatted log files
# local       - Optimized local logging
# syslog      - Syslog daemon
# journald    - Systemd journal
# fluentd     - Fluentd daemon
# awslogs     - Amazon CloudWatch Logs
# gcplogs     - Google Cloud Logging
# splunk      - Splunk HTTP Event Collector
# none        - No logging
```

#### Docker Logs Options

```bash
docker logs mycontainer                 # All logs
docker logs -f mycontainer              # Follow (live)
docker logs --tail 100 mycontainer      # Last 100 lines
docker logs --since 1h mycontainer      # Last hour
docker logs --until 30m mycontainer     # Until 30 min ago
docker logs -t mycontainer              # With timestamps
docker logs --since 2024-01-01T00:00:00 mycontainer  # Since specific time
```

#### Monitoring with docker stats

```bash
# Live resource usage for all containers
docker stats

# Specific container
docker stats mycontainer

# Snapshot (non-streaming)
docker stats --no-stream

# Custom format
docker stats --format "table {{.Name}}\t{{.CPUPerc}}\t{{.MemUsage}}"
```

#### Setting Up Monitoring Stack (Prometheus + Grafana)

```yaml
# docker-compose-monitoring.yml
services:
  prometheus:
    image: prom/prometheus:latest
    ports:
      - "9090:9090"
    volumes:
      - ./prometheus.yml:/etc/prometheus/prometheus.yml
      - prometheus-data:/prometheus
    restart: unless-stopped

  grafana:
    image: grafana/grafana:latest
    ports:
      - "3000:3000"
    environment:
      GF_SECURITY_ADMIN_PASSWORD: admin
    volumes:
      - grafana-data:/var/lib/grafana
    depends_on:
      - prometheus
    restart: unless-stopped

  cadvisor:
    image: gcr.io/cadvisor/cadvisor:latest
    ports:
      - "8080:8080"
    volumes:
      - /:/rootfs:ro
      - /var/run:/var/run:ro
      - /sys:/sys:ro
      - /var/lib/docker/:/var/lib/docker:ro
    restart: unless-stopped

  node-exporter:
    image: prom/node-exporter:latest
    ports:
      - "9100:9100"
    restart: unless-stopped

volumes:
  prometheus-data:
  grafana-data:
```

```yaml
# prometheus.yml
global:
  scrape_interval: 15s

scrape_configs:
  - job_name: 'cadvisor'
    static_configs:
      - targets: ['cadvisor:8080']

  - job_name: 'node-exporter'
    static_configs:
      - targets: ['node-exporter:9100']
```

#### Practical Exercises

```bash
# Exercise 1: Explore container logs
docker run -d --name logtest nginx
docker logs logtest
docker logs -f logtest &
curl http://localhost:80 2>/dev/null || true  # Generate log entry
docker logs --tail 5 logtest
docker stop logtest && docker rm logtest

# Exercise 2: Configure log rotation
docker run -d \
  --name log-rotate \
  --log-opt max-size=1m \
  --log-opt max-file=3 \
  nginx
docker inspect log-rotate --format '{{.HostConfig.LogConfig}}'
docker stop log-rotate && docker rm log-rotate

# Exercise 3: Monitor resource usage
docker run -d --name stats-test1 --memory 128m --cpus 0.5 nginx
docker run -d --name stats-test2 --memory 256m --cpus 1.0 nginx
docker stats --no-stream
docker stop stats-test1 stats-test2
docker rm stats-test1 stats-test2
```

#### Interview Q&A

**Q: What is the default logging driver in Docker?**
A: The default is `json-file`, which stores container logs as JSON files on the Docker host. You can change the default in the Docker daemon configuration or per-container with `--log-driver`.

**Q: How do you prevent container logs from filling up disk space?**
A: Configure log rotation using `--log-opt max-size=10m --log-opt max-file=3` to limit log file size and count. You can set this per-container, in compose files, or as a Docker daemon default.

---

### 11. Docker Security

#### Namespaces and Cgroups

- **Namespaces** provide isolation: PID, Network, Mount, UTS, IPC, User. Each container gets its own namespace set.
- **Cgroups** limit resources: CPU, memory, I/O, network. They prevent one container from consuming all host resources.

#### Running as Non-Root

```dockerfile
# In Dockerfile
FROM node:18-alpine
RUN addgroup -S appgroup && adduser -S appuser -G appgroup
WORKDIR /app
COPY --chown=appuser:appgroup . .
USER appuser
CMD ["node", "server.js"]
```

```bash
# At runtime
docker run --user 1000:1000 myimage
```

#### Root vs Rootless Mode

```bash
# Check if running rootless
docker info --format '{{.SecurityOptions}}'

# Run Docker in rootless mode (does not require root daemon)
# Install: https://docs.docker.com/engine/security/rootless/
dockerd-rootless-setuptool.sh install
```

#### Read-Only Containers

```bash
# Read-only root filesystem
docker run --read-only --tmpfs /tmp --tmpfs /run nginx

# In Compose
services:
  web:
    image: nginx
    read_only: true
    tmpfs:
      - /tmp
      - /run
      - /var/cache/nginx
```

#### Security Scanning

```bash
# Docker Scout (built-in)
docker scout cves myimage:latest
docker scout quickview myimage:latest
docker scout recommendations myimage:latest

# Trivy (open source)
docker run --rm -v /var/run/docker.sock:/var/run/docker.sock \
  aquasec/trivy:latest image myimage:latest
```

#### Capabilities

```bash
# Drop all capabilities, add only needed ones
docker run --cap-drop ALL --cap-add NET_BIND_SERVICE nginx

# Common capabilities:
# NET_BIND_SERVICE - Bind to ports below 1024
# SYS_PTRACE      - Debug/trace processes
# NET_ADMIN        - Network administration
# SYS_ADMIN        - Broad system admin (avoid)
```

#### Secrets Management

```bash
# Docker Swarm secrets
echo "my-secret-password" | docker secret create db_password -
docker service create \
  --name myapp \
  --secret db_password \
  myimage

# In the container, secrets are available at /run/secrets/db_password
```

#### Seccomp and AppArmor

```bash
# Custom seccomp profile
docker run --security-opt seccomp=./custom-seccomp.json nginx

# Disable seccomp (not recommended)
docker run --security-opt seccomp=unconfined nginx

# AppArmor profile
docker run --security-opt apparmor=docker-default nginx
```

#### Security Best Practices

1. **Use official or verified base images**
2. **Run as non-root user** (USER instruction)
3. **Use multi-stage builds** to exclude build tools
4. **Scan images regularly** for vulnerabilities
5. **Use read-only containers** where possible
6. **Drop all capabilities**, add only what is needed
7. **Set resource limits** (memory, CPU)
8. **Do not mount the Docker socket** unless absolutely necessary
9. **Use secrets management** -- never bake secrets into images
10. **Keep images updated** -- rebuild with latest base images

#### Practical Exercises

```bash
# Exercise 1: Run a read-only container
docker run -d --read-only --tmpfs /tmp --tmpfs /var/cache/nginx \
  --tmpfs /var/run --name secure-nginx nginx
docker exec secure-nginx touch /test 2>&1 || echo "Write blocked (expected)"
docker stop secure-nginx && docker rm secure-nginx

# Exercise 2: Drop capabilities
docker run --rm --cap-drop ALL --cap-add NET_BIND_SERVICE nginx \
  sh -c "echo 'Minimal capabilities'"

# Exercise 3: Scan an image
docker pull nginx:latest
docker scout quickview nginx:latest 2>/dev/null || echo "Install Docker Scout for scanning"

# Exercise 4: Non-root container
docker run --rm --user 1000:1000 alpine id
# Output: uid=1000 gid=1000
```

#### Interview Q&A

**Q: How do you secure a Docker container?**
A: Run as non-root user, drop all capabilities and add only needed ones, use read-only root filesystem, set resource limits, scan images for vulnerabilities, use minimal base images, manage secrets properly, and keep images updated.

**Q: What are namespaces and cgroups in Docker?**
A: Namespaces provide isolation (PID, network, mount, user, etc.) so each container has its own view of the system. Cgroups (control groups) limit and account for resource usage (CPU, memory, I/O) to prevent one container from starving others.

**Q: What is Docker Content Trust?**
A: Docker Content Trust (DCT) uses digital signatures to verify the integrity and publisher of images. When enabled (`DOCKER_CONTENT_TRUST=1`), Docker only pulls and runs signed images, preventing tampered image attacks.

---

## PART 3: ADVANCED

---

### 12. Docker Swarm

Docker Swarm is Docker's native container orchestration tool for managing clusters of Docker hosts.

#### Architecture

```
+-----------------------------------------------------------+
|                     DOCKER SWARM                           |
|                                                           |
|   +------------------+  +------------------+              |
|   | MANAGER NODE 1   |  | MANAGER NODE 2   |  (Raft      |
|   | (Leader)         |  | (Follower)       |   consensus) |
|   +--------+---------+  +--------+---------+              |
|            |                     |                        |
|   +--------+---------+-----------+---------+              |
|   |                  |                     |              |
|   v                  v                     v              |
|   +-----------+  +-----------+  +-----------+             |
|   | WORKER 1  |  | WORKER 2  |  | WORKER 3  |             |
|   | Task A    |  | Task B    |  | Task C    |             |
|   | Task D    |  | Task E    |  |           |             |
|   +-----------+  +-----------+  +-----------+             |
+-----------------------------------------------------------+
```

#### Swarm Commands

```bash
# Initialize a swarm (current node becomes manager)
docker swarm init
docker swarm init --advertise-addr 192.168.1.100

# Get join token for workers
docker swarm join-token worker

# Get join token for managers
docker swarm join-token manager

# Join a swarm as worker
docker swarm join --token <token> 192.168.1.100:2377

# List nodes
docker node ls

# Promote/demote nodes
docker node promote worker1
docker node demote manager2

# Leave the swarm
docker swarm leave
docker swarm leave --force    # For managers

# Drain a node (stop scheduling tasks)
docker node update --availability drain worker1
docker node update --availability active worker1
```

#### Services

```bash
# Create a service
docker service create --name web --replicas 3 -p 80:80 nginx

# List services
docker service ls

# List tasks (containers) of a service
docker service ps web

# Inspect a service
docker service inspect web

# Scale a service
docker service scale web=5

# Update a service
docker service update --image nginx:1.25 web
docker service update --replicas 5 web

# Rolling update
docker service update \
  --image nginx:1.25 \
  --update-parallelism 2 \
  --update-delay 10s \
  --update-failure-action rollback \
  web

# Rollback
docker service rollback web

# Remove a service
docker service rm web

# View service logs
docker service logs web
docker service logs -f web
```

#### Secrets and Configs in Swarm

```bash
# Create a secret
echo "supersecret" | docker secret create db_pass -
docker secret create ssl_cert ./cert.pem

# Use secret in a service
docker service create \
  --name myapp \
  --secret db_pass \
  myimage
# Secret available at /run/secrets/db_pass inside container

# Create a config
docker config create nginx_conf ./nginx.conf

# Use config in a service
docker service create \
  --name web \
  --config source=nginx_conf,target=/etc/nginx/nginx.conf \
  nginx
```

#### Stack Deploy (Compose in Swarm)

```yaml
# stack.yml
services:
  web:
    image: nginx:alpine
    ports:
      - "80:80"
    deploy:
      replicas: 3
      update_config:
        parallelism: 1
        delay: 10s
      rollback_config:
        parallelism: 1
      restart_policy:
        condition: on-failure
      placement:
        constraints:
          - node.role == worker
    networks:
      - webnet

  visualizer:
    image: dockersamples/visualizer
    ports:
      - "8080:8080"
    volumes:
      - /var/run/docker.sock:/var/run/docker.sock
    deploy:
      placement:
        constraints:
          - node.role == manager

networks:
  webnet:
    driver: overlay
```

```bash
# Deploy a stack
docker stack deploy -c stack.yml mystack

# List stacks
docker stack ls

# List services in a stack
docker stack services mystack

# List tasks in a stack
docker stack ps mystack

# Remove a stack
docker stack rm mystack
```

#### Practical Exercises

```bash
# Exercise 1: Initialize swarm and create a service
docker swarm init
docker service create --name demo-web --replicas 3 -p 8080:80 nginx
docker service ls
docker service ps demo-web
docker service scale demo-web=5
docker service ps demo-web
curl http://localhost:8080

# Exercise 2: Rolling update
docker service update --image nginx:alpine demo-web
docker service ps demo-web    # See old and new tasks

# Exercise 3: Rollback
docker service rollback demo-web

# Exercise 4: Use secrets
echo "mysecretvalue" | docker secret create test_secret -
docker service create \
  --name secret-app \
  --secret test_secret \
  alpine sh -c "cat /run/secrets/test_secret && sleep 3600"
docker service logs secret-app

# Cleanup
docker service rm demo-web secret-app
docker secret rm test_secret
docker swarm leave --force
```

#### Interview Q&A

**Q: What is Docker Swarm?**
A: Docker Swarm is Docker's built-in container orchestration solution. It turns a group of Docker hosts into a single virtual Docker host, providing service discovery, load balancing, scaling, rolling updates, and fault tolerance.

**Q: What is the difference between a task and a service in Swarm?**
A: A service defines the desired state (image, replicas, ports, etc.). A task is a running instance of a service -- essentially a container plus the commands to run it. If you have 3 replicas, you have 3 tasks.

**Q: Docker Swarm vs Kubernetes?**
A: Swarm is simpler to set up and learn, tightly integrated with Docker, but has fewer features. Kubernetes is more complex but offers richer functionality (auto-scaling, custom controllers, broader ecosystem). Kubernetes is the industry standard for production orchestration.

---

### 13. Docker in CI/CD

#### Docker in GitHub Actions

```yaml
# .github/workflows/docker.yml
name: Build and Push Docker Image

on:
  push:
    branches: [main]
  pull_request:
    branches: [main]

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Set up Docker Buildx
        uses: docker/setup-buildx-action@v3

      - name: Login to Docker Hub
        uses: docker/login-action@v3
        with:
          username: ${{ secrets.DOCKER_USERNAME }}
          password: ${{ secrets.DOCKER_PASSWORD }}

      - name: Build and push
        uses: docker/build-push-action@v5
        with:
          context: .
          push: ${{ github.event_name != 'pull_request' }}
          tags: |
            username/myapp:latest
            username/myapp:${{ github.sha }}
          cache-from: type=gha
          cache-to: type=gha,mode=max
```

#### Docker in GitLab CI

```yaml
# .gitlab-ci.yml
stages:
  - build
  - test
  - deploy

variables:
  DOCKER_IMAGE: $CI_REGISTRY_IMAGE:$CI_COMMIT_SHA

build:
  stage: build
  image: docker:24
  services:
    - docker:24-dind
  variables:
    DOCKER_TLS_CERTDIR: "/certs"
  script:
    - docker login -u $CI_REGISTRY_USER -p $CI_REGISTRY_PASSWORD $CI_REGISTRY
    - docker build -t $DOCKER_IMAGE .
    - docker push $DOCKER_IMAGE

test:
  stage: test
  image: $DOCKER_IMAGE
  script:
    - npm test

deploy:
  stage: deploy
  script:
    - docker pull $DOCKER_IMAGE
    - docker tag $DOCKER_IMAGE $CI_REGISTRY_IMAGE:latest
    - docker push $CI_REGISTRY_IMAGE:latest
  only:
    - main
```

#### Docker in Jenkins

```groovy
// Jenkinsfile
pipeline {
    agent any

    environment {
        DOCKER_IMAGE = "username/myapp"
        DOCKER_TAG = "${env.BUILD_NUMBER}"
    }

    stages {
        stage('Build') {
            steps {
                script {
                    docker.build("${DOCKER_IMAGE}:${DOCKER_TAG}")
                }
            }
        }

        stage('Test') {
            steps {
                script {
                    docker.image("${DOCKER_IMAGE}:${DOCKER_TAG}").inside {
                        sh 'npm test'
                    }
                }
            }
        }

        stage('Push') {
            steps {
                script {
                    docker.withRegistry('https://registry.hub.docker.com', 'docker-hub-creds') {
                        docker.image("${DOCKER_IMAGE}:${DOCKER_TAG}").push()
                        docker.image("${DOCKER_IMAGE}:${DOCKER_TAG}").push('latest')
                    }
                }
            }
        }
    }
}
```

#### Docker-in-Docker (DinD) vs Socket Mounting

```bash
# DinD: Run Docker daemon inside a container
docker run --privileged -d docker:dind

# Socket mounting: Share host's Docker daemon
docker run -v /var/run/docker.sock:/var/run/docker.sock docker:cli

# DinD: Full isolation, slower, uses --privileged (security concern)
# Socket: Faster, shares host Docker, containers are siblings not children
```

#### Interview Q&A

**Q: What is Docker-in-Docker and when would you use it?**
A: DinD runs a Docker daemon inside a container. It provides full isolation for CI/CD builds but requires `--privileged` mode (security risk). The alternative is mounting the Docker socket, which is faster but means CI containers are siblings to other host containers.

**Q: How do you cache Docker layers in CI/CD?**
A: Use BuildKit cache with `--cache-from` and `--cache-to`. In GitHub Actions, use `cache-from: type=gha`. Also leverage the `docker pull` of the previous image before building to reuse layers. Order Dockerfile instructions to maximize cache hits.

---

### 14. Docker Performance & Optimization

#### Image Size Optimization

```dockerfile
# Alpine-based (5 MB base)
FROM node:18-alpine
# vs node:18 (around 900 MB)

# Slim variant (around 150 MB)
FROM python:3.11-slim

# Distroless (minimal, no shell)
FROM gcr.io/distroless/nodejs18-debian12
COPY --from=builder /app /app
CMD ["server.js"]

# Scratch (empty, for static binaries)
FROM scratch
COPY myapp /myapp
ENTRYPOINT ["/myapp"]
```

**Size comparison:**
| Base Image | Approx Size |
|-----------|-------------|
| ubuntu:22.04 | 77 MB |
| node:18 | 900 MB |
| node:18-slim | 200 MB |
| node:18-alpine | 175 MB |
| python:3.11 | 920 MB |
| python:3.11-slim | 150 MB |
| python:3.11-alpine | 60 MB |
| alpine:3.18 | 7 MB |
| scratch | 0 MB |
| distroless | 20-50 MB |

#### BuildKit Features

```bash
# Enable BuildKit
export DOCKER_BUILDKIT=1

# Or prefix the build command
DOCKER_BUILDKIT=1 docker build -t myapp .

# BuildKit features:
# - Parallel stage execution in multi-stage builds
# - Better caching
# - Build secrets (--secret)
# - SSH forwarding (--ssh)
# - Cache mounts for package managers

# Cache mount for npm
# syntax=docker/dockerfile:1
FROM node:18-alpine
WORKDIR /app
COPY package*.json ./
RUN --mount=type=cache,target=/root/.npm npm ci
COPY . .
CMD ["node", "server.js"]

# Cache mount for pip
RUN --mount=type=cache,target=/root/.cache/pip pip install -r requirements.txt

# Build secrets (not baked into image)
RUN --mount=type=secret,id=npmrc,target=/root/.npmrc npm ci

# Build:
docker build --secret id=npmrc,src=.npmrc -t myapp .
```

#### Multi-Platform Builds with Buildx

```bash
# Create a buildx builder
docker buildx create --name mybuilder --use

# Build for multiple platforms
docker buildx build \
  --platform linux/amd64,linux/arm64,linux/arm/v7 \
  -t username/myapp:latest \
  --push .

# List builders
docker buildx ls

# Inspect builder
docker buildx inspect mybuilder
```

#### Resource Constraints

```bash
# Memory limits
docker run -d --memory 256m --memory-swap 512m nginx
docker run -d --memory 256m --memory-swap -1 nginx   # Unlimited swap

# CPU limits
docker run -d --cpus 1.5 nginx                       # 1.5 CPU cores
docker run -d --cpu-shares 512 nginx                  # Relative weight
docker run -d --cpuset-cpus "0,1" nginx               # Specific CPU cores

# I/O limits
docker run -d --device-read-bps /dev/sda:1mb nginx
docker run -d --device-write-bps /dev/sda:1mb nginx

# PID limit
docker run -d --pids-limit 100 nginx
```

#### Practical Exercises

```bash
# Exercise 1: Compare image sizes
docker pull node:18
docker pull node:18-slim
docker pull node:18-alpine
docker images node --format "table {{.Tag}}\t{{.Size}}"

# Exercise 2: Optimize a Dockerfile
# Before (large image):
cat > /tmp/Dockerfile.before << 'EOF'
FROM ubuntu:22.04
RUN apt-get update
RUN apt-get install -y nodejs npm
RUN apt-get install -y curl git
COPY . /app
WORKDIR /app
RUN npm install
CMD ["node", "server.js"]
EOF

# After (optimized):
cat > /tmp/Dockerfile.after << 'EOF'
FROM node:18-alpine AS builder
WORKDIR /app
COPY package*.json ./
RUN npm ci --production
COPY . .

FROM node:18-alpine
WORKDIR /app
RUN addgroup -S app && adduser -S app -G app
COPY --from=builder --chown=app:app /app .
USER app
EXPOSE 3000
CMD ["node", "server.js"]
EOF

# Exercise 3: Resource constraints
docker run -d --name mem-test --memory 64m --memory-swap 128m nginx
docker stats mem-test --no-stream
docker stop mem-test && docker rm mem-test

# Exercise 4: Check image layer sizes
docker image history node:18-alpine
```

#### Interview Q&A

**Q: How do you reduce Docker image size?**
A: Use smaller base images (alpine, slim, distroless, scratch), multi-stage builds, combine RUN commands, clean up in the same layer (remove cache, temp files), use .dockerignore, and avoid installing unnecessary packages.

**Q: What is BuildKit?**
A: BuildKit is Docker's next-generation build engine. It offers parallel build stages, better caching, build secrets (not stored in layers), cache mounts for package managers, and SSH forwarding. Enable it with `DOCKER_BUILDKIT=1`.

**Q: What is the difference between --memory and --memory-swap?**
A: `--memory` sets the hard memory limit. `--memory-swap` sets the total of memory + swap. If `--memory=256m` and `--memory-swap=512m`, the container can use 256m RAM + 256m swap. If `--memory-swap=-1`, swap is unlimited.

---

### 15. Docker Troubleshooting

#### Common Errors and Solutions

| Error | Cause | Solution |
|-------|-------|---------|
| `Cannot connect to the Docker daemon` | Daemon not running | `sudo systemctl start docker` |
| `port is already allocated` | Port in use on host | Use a different host port or stop the conflicting process |
| `no space left on device` | Disk full | `docker system prune -a` |
| `OOMKilled` | Container exceeded memory limit | Increase `--memory` or optimize app |
| `exec format error` | Wrong architecture | Build for correct platform |
| `COPY failed: file not found` | File outside build context | Check .dockerignore, adjust COPY paths |
| `dial tcp: lookup ... no such host` | DNS resolution failure | Check network configuration |
| `permission denied` | File permissions | Use `--chown` in COPY, or adjust USER |

#### Debugging Containers

```bash
# Check why a container exited
docker inspect <container> --format '{{.State.ExitCode}}'
docker inspect <container> --format '{{.State.OOMKilled}}'
docker inspect <container> --format '{{.State.Error}}'

# View logs
docker logs <container>
docker logs --tail 50 <container>

# Shell into a running container
docker exec -it <container> sh
docker exec -it <container> bash

# Shell into a stopped container (create new from same image)
docker commit <stopped-container> debug-image
docker run -it debug-image sh

# Override entrypoint for debugging
docker run -it --entrypoint sh myimage

# Check processes
docker top <container>

# Check resource usage
docker stats <container>

# Inspect everything
docker inspect <container>
```

#### Network Troubleshooting

```bash
# Check container IP
docker inspect <container> --format '{{.NetworkSettings.IPAddress}}'

# Check network connectivity
docker exec <container> ping <other-container>
docker exec <container> curl http://service:port

# Check DNS resolution
docker exec <container> nslookup service-name

# Install network tools in a container (if needed)
docker exec <container> apt-get update && apt-get install -y iputils-ping curl dnsutils

# Use a network debug container
docker run -it --network <target-network> nicolaka/netshoot

# Check port mappings
docker port <container>

# Inspect network
docker network inspect <network-name>
```

#### Storage Troubleshooting

```bash
# Check disk usage
docker system df
docker system df -v    # Verbose

# Clean up
docker system prune          # Remove stopped containers, unused networks, dangling images
docker system prune -a       # Also remove unused images
docker system prune --volumes  # Also remove unused volumes

# Check container filesystem changes
docker diff <container>

# Check volume usage
docker volume ls
docker volume inspect <volume>
```

#### Practical Exercises

```bash
# Exercise 1: Debug a failing container
docker run -d --name fail-test alpine sh -c "exit 1"
docker ps -a --filter name=fail-test
docker inspect fail-test --format '{{.State.ExitCode}}'
docker logs fail-test
docker rm fail-test

# Exercise 2: Debug OOM issue
docker run -d --name oom-test --memory 10m alpine sh -c \
  "dd if=/dev/zero of=/dev/null bs=1M"
sleep 3
docker inspect oom-test --format '{{.State.OOMKilled}}'
docker stop oom-test 2>/dev/null; docker rm oom-test

# Exercise 3: Storage cleanup
docker system df
docker system prune --force
docker system df

# Exercise 4: Network debugging
docker network create debug-net
docker run -d --name web --network debug-net nginx
docker run --rm --network debug-net alpine ping -c 3 web
docker stop web && docker rm web
docker network rm debug-net

# Exercise 5: Override entrypoint for debugging
docker run -it --entrypoint sh nginx -c "ls /etc/nginx && cat /etc/nginx/nginx.conf"
```

#### Interview Q&A

**Q: A container keeps restarting. How do you debug it?**
A: Check logs (`docker logs`), inspect exit code (`docker inspect --format '{{.State.ExitCode}}'`), check if OOM killed, run with `--entrypoint sh` to get a shell, check health of dependencies, and review the application configuration.

**Q: How do you clean up Docker disk space?**
A: Use `docker system prune` to remove stopped containers, unused networks, and dangling images. Add `-a` to also remove unused images, and `--volumes` to remove unused volumes. Use `docker system df` to see what is using space.

---

### 16. Docker with Kubernetes (Overview)

#### How Docker Relates to Kubernetes

Kubernetes (K8s) is a container orchestration platform. Docker was historically the default container runtime for Kubernetes, but since Kubernetes v1.24, the dockershim was removed.

```
+-----------------------------------------------+
|              KUBERNETES CLUSTER                 |
|                                                |
|  +--------+   +---------+   +---------+       |
|  | Pod    |   | Pod     |   | Pod     |       |
|  |+------+|   |+-------+|   |+-------+|       |
|  || Ctr  ||   || Ctr   ||   || Ctr   ||       |
|  |+------+|   |+-------+|   |+-------+|       |
|  +--------+   +---------+   +---------+       |
|       |             |             |            |
|  +----v-------------v-------------v----+       |
|  |        CONTAINER RUNTIME            |       |
|  |  (containerd / CRI-O / Docker)      |       |
|  +-------------------------------------+       |
|       |                                        |
|  +----v-------------------------------------+  |
|  |              LINUX KERNEL                 |  |
|  |     (namespaces, cgroups, etc.)           |  |
|  +-------------------------------------------+ |
+-----------------------------------------------+
```

#### Container Runtimes

| Runtime | Description |
|---------|-------------|
| **containerd** | Industry standard. Default for Kubernetes since Docker removal. Lightweight. |
| **CRI-O** | Built specifically for Kubernetes. OCI-compliant. Used by OpenShift. |
| **Docker** | Full platform (CLI + daemon + containerd + runc). Removed from K8s v1.24. |

#### Docker Deprecation in Kubernetes

- Kubernetes v1.20: dockershim deprecated
- Kubernetes v1.24: dockershim removed
- **Impact**: Docker images still work (they are OCI-compliant). You just cannot use Docker as the runtime in Kubernetes.
- **What changed**: Kubernetes now uses containerd or CRI-O directly, skipping the Docker daemon overhead.
- **For developers**: Nothing changes. `docker build` still works. Images are the same OCI format.

#### Interview Q&A

**Q: Is Docker dead because Kubernetes removed it?**
A: No. Docker is still widely used for building images and local development. What Kubernetes removed was the "dockershim" -- the interface between Kubernetes and the Docker daemon. Docker images (OCI format) are fully compatible with containerd and CRI-O. Docker as a developer tool remains essential.

**Q: What is the difference between containerd and Docker?**
A: containerd is a container runtime focused solely on running containers. Docker is a full platform that includes containerd plus the Docker CLI, Docker daemon, build tools, and developer experience features. Kubernetes only needs the runtime part (containerd), not the full Docker platform.

**Q: Can you still use Docker to build images for Kubernetes?**
A: Yes. Images built with `docker build` follow the OCI image specification and work with any OCI-compliant runtime (containerd, CRI-O). The build tool and the runtime are independent.

---

## PART 4: INTERVIEW PREPARATION

---

### 17. Top 100 Docker Interview Questions & Answers

#### Beginner Level (Questions 1-30)

**Q1: What is Docker?**
A: Docker is an open-source platform for developing, shipping, and running applications in containers. It packages applications with all dependencies into standardized units that run consistently across environments.

**Q2: What is a container?**
A: A container is a lightweight, standalone, executable package that includes everything needed to run an application: code, runtime, system tools, libraries, and settings. Containers share the host OS kernel and run as isolated processes.

**Q3: What is the difference between Docker and a virtual machine?**
A: Docker containers share the host kernel and run as isolated processes (lightweight, fast startup). VMs run a full guest OS on a hypervisor (heavyweight, slow startup). Containers are MBs; VMs are GBs.

**Q4: What is a Docker image?**
A: A Docker image is a read-only template used to create containers. It contains the application code, dependencies, and configuration. Images are built in layers from a Dockerfile.

**Q5: What is a Dockerfile?**
A: A Dockerfile is a text file containing instructions to build a Docker image. Each instruction (FROM, RUN, COPY, etc.) creates a layer in the image.

**Q6: What is Docker Hub?**
A: Docker Hub is the default public registry for Docker images. It hosts official images, verified publisher images, and community images. You can push and pull images to/from Docker Hub.

**Q7: What is the difference between `docker run` and `docker start`?**
A: `docker run` creates a new container from an image and starts it. `docker start` starts an existing stopped container.

**Q8: What does `docker ps` show?**
A: `docker ps` shows running containers. `docker ps -a` shows all containers including stopped ones.

**Q9: How do you remove a Docker container?**
A: `docker rm <container>` for stopped containers. `docker rm -f <container>` to force-remove running containers.

**Q10: How do you remove a Docker image?**
A: `docker rmi <image>` or `docker image rm <image>`. Use `docker image prune` to remove unused images.

**Q11: What is the purpose of the `-d` flag in `docker run`?**
A: The `-d` flag runs the container in detached mode (background). Without it, the container runs in the foreground and attaches to your terminal.

**Q12: What is the purpose of the `-p` flag in `docker run`?**
A: `-p host_port:container_port` maps a port on the host to a port in the container, enabling external access to the containerized application.

**Q13: What is the purpose of the `-v` flag in `docker run`?**
A: `-v` mounts a volume or directory. `-v name:/path` creates a named volume. `-v /host/path:/container/path` creates a bind mount.

**Q14: What is the difference between `COPY` and `ADD` in Dockerfile?**
A: Both copy files into the image. ADD can auto-extract tar archives and download URLs. COPY is simpler and preferred unless you need ADD's extra features.

**Q15: What is the difference between `CMD` and `RUN` in Dockerfile?**
A: RUN executes commands during image build (creates layers). CMD specifies the default command to run when a container starts.

**Q16: What is Docker Compose?**
A: Docker Compose is a tool for defining and running multi-container applications using a YAML file. It simplifies managing services, networks, and volumes.

**Q17: What is the command to build a Docker image?**
A: `docker build -t image_name:tag .` where `.` is the build context.

**Q18: How do you view logs of a Docker container?**
A: `docker logs <container>`. Use `-f` to follow, `--tail N` for last N lines.

**Q19: What are Docker volumes?**
A: Volumes are the preferred mechanism for persisting data generated by containers. They are managed by Docker and survive container removal.

**Q20: What is port mapping in Docker?**
A: Port mapping exposes a container's port on the host machine. Syntax: `-p 8080:80` maps host port 8080 to container port 80.

**Q21: How do you execute a command in a running container?**
A: `docker exec -it <container> <command>`. For example: `docker exec -it mycontainer bash`.

**Q22: What is the `--rm` flag in `docker run`?**
A: `--rm` automatically removes the container when it exits. Useful for one-off commands.

**Q23: How do you stop a running container?**
A: `docker stop <container>` sends SIGTERM and waits (default 10s) before SIGKILL.

**Q24: What is a Docker network?**
A: Docker networks enable containers to communicate with each other and the outside world. Docker provides bridge, host, none, overlay, and macvlan network drivers.

**Q25: What is the default network driver in Docker?**
A: The default network driver is `bridge`. It creates a private network on the host that containers connect to.

**Q26: How do you list Docker images on your system?**
A: `docker images` or `docker image ls`.

**Q27: What is the `.dockerignore` file?**
A: A file that specifies patterns of files/directories to exclude from the build context. Similar to `.gitignore`. Reduces build time and image size.

**Q28: What is the EXPOSE instruction in Dockerfile?**
A: EXPOSE documents which ports the container listens on. It does NOT publish the port -- you still need `-p` at runtime.

**Q29: What is the WORKDIR instruction in Dockerfile?**
A: WORKDIR sets the working directory for subsequent RUN, CMD, ENTRYPOINT, COPY, and ADD instructions.

**Q30: How do you check Docker version?**
A: `docker version` shows client and server versions. `docker --version` shows a brief version string.

---

#### Intermediate Level (Questions 31-65)

**Q31: What is the difference between CMD and ENTRYPOINT?**
A: CMD provides default command/arguments that can be overridden at runtime. ENTRYPOINT defines the container's main executable -- runtime arguments are appended to it. Together, ENTRYPOINT is the executable and CMD provides default arguments.

**Q32: What is a multi-stage build?**
A: A Dockerfile with multiple FROM statements. Intermediate stages contain build tools; the final stage copies only the artifacts needed. This dramatically reduces final image size.

**Q33: What is the difference between shell form and exec form?**
A: Shell form (`CMD command arg`) runs via `/bin/sh -c`, which means signals may not reach the process. Exec form (`CMD ["command", "arg"]`) runs the command directly as PID 1, enabling proper signal handling.

**Q34: What is a dangling image?**
A: An image that is not tagged and not referenced by any container. Created when rebuilding with the same tag. Clean up with `docker image prune`.

**Q35: What is the difference between a named volume and a bind mount?**
A: Named volumes are managed by Docker in its storage area (portable, Docker handles lifecycle). Bind mounts map a specific host path into the container (dependent on host filesystem).

**Q36: How does Docker layer caching work?**
A: Each Dockerfile instruction creates a layer. If the instruction and its inputs haven't changed, Docker reuses the cached layer. If any layer changes, all subsequent layers are rebuilt.

**Q37: How do you optimize Dockerfile layer caching?**
A: Order instructions from least to most frequently changing. Copy dependency files (package.json) first and install, then copy source code. This way, dependency installation is cached unless the dependency file changes.

**Q38: What is the build context?**
A: The set of files sent to the Docker daemon when building an image. Specified by the path argument in `docker build`. Use `.dockerignore` to exclude unnecessary files.

**Q39: What is the difference between `docker stop` and `docker kill`?**
A: `docker stop` sends SIGTERM, waits for graceful shutdown (default 10s), then SIGKILL. `docker kill` sends SIGKILL immediately.

**Q40: What is the difference between `docker exec` and `docker attach`?**
A: `docker exec` runs a new process inside a container. `docker attach` connects to the container's main process (PID 1). Ctrl+C on attach may stop the container.

**Q41: What is a Docker registry?**
A: A service that stores and distributes Docker images. Docker Hub is the default public registry. Private registries can be run using the `registry:2` image.

**Q42: How do containers on a custom bridge network communicate?**
A: Containers on the same custom bridge network can communicate using container names as hostnames (automatic DNS resolution). This does not work on the default bridge network.

**Q43: What is an overlay network?**
A: An overlay network spans multiple Docker hosts, enabling container communication across hosts. Used primarily in Docker Swarm for multi-host orchestration using VXLAN encapsulation.

**Q44: What is `docker compose up -d`?**
A: It starts all services defined in the compose file in detached (background) mode, creating containers, networks, and volumes as needed.

**Q45: What is `depends_on` in Docker Compose?**
A: It controls service startup order. With `condition: service_healthy`, it waits for the dependency's healthcheck to pass before starting the dependent service.

**Q46: How do you scale services in Docker Compose?**
A: `docker compose up -d --scale service_name=N` to run N replicas of a service.

**Q47: What are the restart policies in Docker?**
A: `no` (default, never restart), `always` (always restart), `unless-stopped` (restart unless manually stopped), `on-failure[:max-retries]` (restart only on non-zero exit code).

**Q48: What is Docker Content Trust?**
A: A security feature that uses digital signatures to verify image integrity and publisher authenticity. Enabled with `DOCKER_CONTENT_TRUST=1`.

**Q49: What is the HEALTHCHECK instruction?**
A: HEALTHCHECK defines a command Docker runs periodically to check if the container is healthy. It sets the container's health status (starting, healthy, unhealthy).

**Q50: How do you pass environment variables to a container?**
A: Using `-e KEY=VALUE`, `--env-file .env`, ENV in Dockerfile, or `environment:` in docker-compose.yml.

**Q51: What is the difference between `docker volume create` and a bind mount?**
A: `docker volume create` creates a named volume managed by Docker. Bind mounts use an existing host directory. Volumes are more portable and Docker manages their lifecycle.

**Q52: What is `docker system prune`?**
A: It removes stopped containers, unused networks, dangling images, and optionally volumes (`--volumes`) and all unused images (`-a`).

**Q53: What is the `docker commit` command?**
A: It creates a new image from a container's current state. Useful for debugging but NOT recommended for production (use Dockerfiles instead for reproducibility).

**Q54: What is the difference between `docker-compose.yml` and `docker-compose.override.yml`?**
A: `docker-compose.override.yml` is automatically merged with `docker-compose.yml` when running `docker compose up`. It is typically used for development overrides.

**Q55: How do you view the layers of a Docker image?**
A: `docker image history <image>` shows each layer, its size, and the instruction that created it.

**Q56: What is the USER instruction in Dockerfile?**
A: USER sets the user (and optionally group) for subsequent RUN, CMD, and ENTRYPOINT instructions. Used to run containers as non-root for security.

**Q57: What is the ARG instruction in Dockerfile?**
A: ARG defines build-time variables that can be set via `--build-arg`. They are NOT available at runtime (unlike ENV). ARG before FROM affects the FROM instruction.

**Q58: What is Docker BuildKit?**
A: BuildKit is Docker's next-gen build engine offering parallel multi-stage builds, better caching, build secrets, cache mounts, and SSH forwarding. Enable with `DOCKER_BUILDKIT=1`.

**Q59: How do you create a private Docker registry?**
A: `docker run -d -p 5000:5000 --restart always --name registry registry:2`. Push images using `localhost:5000/imagename:tag`.

**Q60: What logging drivers does Docker support?**
A: json-file (default), local, syslog, journald, fluentd, awslogs, gcplogs, splunk, and none.

**Q61: What is the difference between `-p` and `-P` flags?**
A: `-p host:container` maps specific ports. `-P` publishes all ports defined by EXPOSE to random high-numbered host ports.

**Q62: What is `docker inspect`?**
A: Returns detailed JSON information about Docker objects (containers, images, networks, volumes). Use `--format` with Go templates to extract specific fields.

**Q63: How do you limit container resources?**
A: Use `--memory` for RAM limits, `--cpus` for CPU limits, `--device-read-bps` for I/O limits, and `--pids-limit` for process count limits.

**Q64: What are Docker profiles in Compose?**
A: Profiles allow you to selectively start services. Services with profiles are only started when that profile is explicitly activated with `--profile`.

**Q65: What is `docker diff`?**
A: Shows filesystem changes in a container compared to its image. Lists added (A), changed (C), and deleted (D) files.

---

#### Advanced Level (Questions 66-100)

**Q66: What are Linux namespaces and how does Docker use them?**
A: Namespaces provide isolation for containers. Docker uses PID namespace (process isolation), NET namespace (network isolation), MNT namespace (filesystem isolation), UTS namespace (hostname isolation), IPC namespace (inter-process communication isolation), and USER namespace (user ID mapping).

**Q67: What are cgroups and how does Docker use them?**
A: Cgroups (control groups) limit and monitor resource usage per container: CPU, memory, I/O, and network. Docker uses cgroups to enforce `--memory`, `--cpus`, and other resource constraints.

**Q68: What is the Docker storage driver?**
A: The storage driver manages how image layers and container writable layers are stored on disk. Options include overlay2 (default on Linux), devicemapper, btrfs, zfs, and aufs.

**Q69: What is the union filesystem?**
A: A filesystem that layers multiple directories on top of each other, presenting a unified view. Docker uses it to stack read-only image layers with a writable container layer. overlay2 is the current default implementation.

**Q70: What is Docker Swarm?**
A: Docker's built-in orchestration tool that turns multiple Docker hosts into a cluster. It provides service discovery, load balancing, rolling updates, scaling, and fault tolerance.

**Q71: What is the difference between a Swarm service and a container?**
A: A service defines the desired state (image, replicas, ports). Swarm schedules tasks (containers) across nodes to achieve that state. If a container fails, Swarm automatically replaces it.

**Q72: What is the Raft consensus algorithm in Docker Swarm?**
A: Raft ensures all manager nodes agree on the cluster state. It requires a majority (quorum) of managers to be available. For N managers, the cluster tolerates (N-1)/2 failures.

**Q73: How many manager nodes should a Swarm have?**
A: An odd number: 3 (tolerates 1 failure), 5 (tolerates 2), or 7 (tolerates 3). More than 7 managers adds overhead without much benefit. Having 3 is standard for production.

**Q74: What is Docker-in-Docker (DinD)?**
A: Running a Docker daemon inside a Docker container. Requires `--privileged` mode. Used in CI/CD for isolated builds. Alternative: mount the host Docker socket.

**Q75: What is the difference between DinD and Docker socket mounting?**
A: DinD runs a separate Docker daemon (full isolation, needs --privileged). Socket mounting shares the host daemon (faster, but containers are siblings, not children, and can affect the host).

**Q76: What is the scratch base image?**
A: An empty image with no OS, no shell, nothing. Used for statically compiled binaries (Go, Rust). Results in the smallest possible images.

**Q77: What are distroless images?**
A: Google-maintained images that contain only the application runtime (no shell, no package manager). More secure than standard images but still include essential runtime libraries (unlike scratch).

**Q78: How do multi-platform builds work with buildx?**
A: `docker buildx` uses QEMU emulation or cross-compilation to build images for multiple architectures (amd64, arm64, etc.) in a single command. Images are stored as a multi-arch manifest.

**Q79: What is a Docker manifest?**
A: A manifest describes the layers and configuration of an image. A manifest list (fat manifest) references multiple platform-specific manifests, enabling Docker to automatically pull the right architecture.

**Q80: How do you handle secrets in Docker?**
A: In Swarm: use `docker secret` (stored encrypted, mounted as files in `/run/secrets/`). In Compose: use `secrets:` directive. At build time: use BuildKit `--secret`. Never bake secrets into images or environment variables visible in inspect.

**Q81: What is AppArmor in Docker?**
A: AppArmor (Application Armor) is a Linux security module that restricts container capabilities at the kernel level. Docker applies a default AppArmor profile to containers.

**Q82: What is Seccomp in Docker?**
A: Seccomp (Secure Computing) filters system calls a container can make. Docker's default seccomp profile blocks about 44 dangerous syscalls while allowing the ~300+ that most apps need.

**Q83: What are Linux capabilities in Docker?**
A: Capabilities divide root privileges into fine-grained units. Docker drops most capabilities by default. Use `--cap-drop ALL --cap-add <needed>` for least-privilege containers.

**Q84: What is rootless Docker?**
A: Running the Docker daemon and containers without root privileges. Improves security by preventing container breakout from gaining root on the host. Some features have limitations.

**Q85: How do you implement rolling updates in Swarm?**
A: `docker service update --image newimage --update-parallelism 2 --update-delay 10s --update-failure-action rollback servicename`. Updates 2 tasks at a time with a 10-second delay between batches, rolling back on failure.

**Q86: What is a Docker plugin?**
A: An extension that adds capabilities to Docker. Examples: volume plugins (for NFS, cloud storage), network plugins (for custom networking), and authorization plugins. Managed with `docker plugin`.

**Q87: What is the Docker daemon configuration file?**
A: `/etc/docker/daemon.json` on Linux. Configures storage driver, logging defaults, registry mirrors, DNS, and other daemon-level settings.

**Q88: How do you debug a container that crashes on startup?**
A: Check logs (`docker logs`), inspect exit code and OOM status, run with `--entrypoint sh` to get a shell, check dependencies, remove healthcheck temporarily, and use `docker events` to monitor.

**Q89: What is `docker events`?**
A: Streams real-time events from the Docker daemon: container starts/stops, image pulls, network connections, volume operations. Useful for debugging and monitoring.

**Q90: How do you implement a Docker CI/CD pipeline?**
A: Build the image in CI (GitHub Actions, Jenkins, GitLab CI), run tests inside the container, push to a registry with a versioned tag, deploy by pulling and running the new image (or updating a Swarm/K8s service).

**Q91: What is the `.docker/config.json` file?**
A: Stores Docker client configuration: registry credentials, default output format, CLI plugins, and credential helpers. Located in the user's home directory.

**Q92: How does Docker networking work internally?**
A: Docker creates a virtual bridge (docker0) on the host. Each container gets a virtual ethernet interface (veth pair) connected to the bridge. iptables rules handle port mapping and network isolation.

**Q93: What is Docker networking in host mode?**
A: The container shares the host's network namespace directly. No network isolation, no port mapping needed. The container sees all host network interfaces and ports. Linux only.

**Q94: What is a macvlan network?**
A: Macvlan assigns a real MAC address to each container, making it appear as a physical device on the network. Used for legacy applications that expect to be directly on the LAN.

**Q95: How do you monitor Docker containers in production?**
A: Use docker stats for basic monitoring. For production: cAdvisor (container metrics), Prometheus (metrics collection), Grafana (dashboards), ELK/EFK stack (log aggregation), and alerting tools.

**Q96: What is the `docker system df` command?**
A: Shows Docker disk usage: images, containers, volumes, and build cache, with total and reclaimable space for each.

**Q97: How do you do blue-green deployments with Docker?**
A: Run two identical environments (blue and green). Deploy the new version to the inactive environment, test it, then switch traffic (update reverse proxy/load balancer). The old environment remains as a quick rollback option.

**Q98: How do you design a microservices architecture with Docker?**
A: One service per container, communicate via APIs (REST/gRPC) over custom Docker networks, use Docker Compose or Swarm/K8s for orchestration, implement service discovery, centralized logging, health checks, and circuit breakers.

**Q99: What is container orchestration and why is it needed?**
A: Container orchestration automates deployment, scaling, networking, and management of containerized applications across a cluster. It is needed because production apps run hundreds of containers across multiple hosts -- manual management is impractical.

**Q100: What happens when you run `docker run hello-world`?**
A: Docker client sends the command to the daemon. The daemon checks for the image locally; if not found, pulls it from Docker Hub. It creates a new container from the image, allocates a read-write filesystem, creates a network interface, starts the container, executes the hello-world binary, and the container exits after printing its message.

---

### 18. Docker Cheat Sheet

#### Image Commands

| Command | Description |
|---------|-------------|
| `docker pull image:tag` | Pull an image |
| `docker images` | List local images |
| `docker rmi image` | Remove an image |
| `docker image prune` | Remove dangling images |
| `docker image prune -a` | Remove all unused images |
| `docker build -t name:tag .` | Build an image |
| `docker tag source target` | Tag an image |
| `docker push image:tag` | Push to registry |
| `docker save -o file.tar image` | Save image to file |
| `docker load -i file.tar` | Load image from file |
| `docker image inspect image` | Inspect image details |
| `docker image history image` | Show image layers |
| `docker search term` | Search Docker Hub |

#### Container Commands

| Command | Description |
|---------|-------------|
| `docker run -d -p 80:80 --name web nginx` | Run container |
| `docker ps` | List running containers |
| `docker ps -a` | List all containers |
| `docker stop container` | Stop container (graceful) |
| `docker start container` | Start stopped container |
| `docker restart container` | Restart container |
| `docker kill container` | Kill container (immediate) |
| `docker rm container` | Remove container |
| `docker rm -f container` | Force remove container |
| `docker exec -it container bash` | Shell into container |
| `docker logs -f container` | Follow container logs |
| `docker stats` | Live resource usage |
| `docker top container` | Container processes |
| `docker inspect container` | Container details |
| `docker cp src container:dst` | Copy files to container |
| `docker cp container:src dst` | Copy files from container |
| `docker diff container` | Filesystem changes |
| `docker commit container image` | Create image from container |
| `docker container prune` | Remove stopped containers |

#### Volume Commands

| Command | Description |
|---------|-------------|
| `docker volume create name` | Create a volume |
| `docker volume ls` | List volumes |
| `docker volume inspect name` | Inspect a volume |
| `docker volume rm name` | Remove a volume |
| `docker volume prune` | Remove unused volumes |
| `-v name:/path` | Named volume mount |
| `-v /host:/container` | Bind mount |
| `-v /host:/container:ro` | Read-only bind mount |
| `--tmpfs /path` | tmpfs mount |

#### Network Commands

| Command | Description |
|---------|-------------|
| `docker network create name` | Create a network |
| `docker network ls` | List networks |
| `docker network inspect name` | Inspect a network |
| `docker network rm name` | Remove a network |
| `docker network connect net ctr` | Connect container to network |
| `docker network disconnect net ctr` | Disconnect from network |
| `docker network prune` | Remove unused networks |

#### Compose Commands

| Command | Description |
|---------|-------------|
| `docker compose up -d` | Start all services |
| `docker compose down` | Stop and remove all |
| `docker compose down -v` | Also remove volumes |
| `docker compose ps` | List services |
| `docker compose logs -f` | Follow all logs |
| `docker compose logs service` | Service-specific logs |
| `docker compose exec service cmd` | Execute in service |
| `docker compose build` | Build images |
| `docker compose pull` | Pull images |
| `docker compose restart` | Restart services |
| `docker compose stop` | Stop services |
| `docker compose config` | Validate and view config |

#### System Commands

| Command | Description |
|---------|-------------|
| `docker system df` | Show disk usage |
| `docker system prune` | Remove unused data |
| `docker system prune -a --volumes` | Remove everything unused |
| `docker info` | System-wide info |
| `docker version` | Version info |
| `docker events` | Real-time events |

#### Common docker run Flags

| Flag | Description |
|------|-------------|
| `-d` | Detached mode (background) |
| `-it` | Interactive terminal |
| `-p 8080:80` | Port mapping |
| `-v data:/app` | Volume mount |
| `-e KEY=VAL` | Environment variable |
| `--env-file .env` | Load env from file |
| `--name myapp` | Container name |
| `--rm` | Auto-remove on exit |
| `--network mynet` | Connect to network |
| `--restart always` | Restart policy |
| `--memory 512m` | Memory limit |
| `--cpus 1.5` | CPU limit |
| `-w /app` | Working directory |
| `--user 1000:1000` | Run as user |
| `--read-only` | Read-only filesystem |
| `--hostname myhost` | Set hostname |
| `--cap-drop ALL` | Drop all capabilities |
| `--cap-add NET_BIND_SERVICE` | Add specific capability |

---

**End of Guide**

This guide covers Docker from the ground up through advanced topics. Practice each section's exercises in order, and you will be well-prepared for any Docker-related interview or real-world challenge.

Node app.

# Set a variable holding the full folder path inside your TEMP directory
$dir = "$env:TEMP\docker-node-app"
# Create that folder; -Force stops errors if it already exists; Out-Null hides output
New-Item -ItemType Directory -Force -Path $dir | Out-Null
# Move into the newly created folder so all files are written there
Set-Location $dir

# --- Write the Node.js web server source file (server.js) ---
@'
const http = require('http');
const server = http.createServer((req, res) => {
  res.writeHead(200, { 'Content-Type': 'text/plain' });
  res.end('Hello from Docker!\n');
});
server.listen(3000, () => console.log('Server running on port 3000'));
'@ | Set-Content -Path server.js    # Save the above text into server.js

# --- Write the Node project manifest (package.json) ---
@'
{
  "name": "docker-demo",
  "version": "1.0.0",
  "main": "server.js",
  "scripts": { "start": "node server.js" }
}
'@ | Set-Content -Path package.json    # Save the above text into package.json

# --- Write the Dockerfile (the image build recipe) ---
@'
FROM node:18-alpine
WORKDIR /app
COPY package.json ./
RUN npm install --production
COPY server.js ./
EXPOSE 3000
USER node
CMD ["node", "server.js"]
'@ | Set-Content -Path Dockerfile    # Save the above text into Dockerfile

# Build a Docker image from the Dockerfile and tag (name) it "node-demo"
docker build -t node-demo .
# Run the image as a background container, mapping host port 3000 -> container 3000
docker run -d -p 3000:3000 --name node-app node-demo
# Send an HTTP request to the running container to confirm it responds
curl.exe http://localhost:3000
# Stop the running container
docker stop node-app
# Delete the stopped container so the name "node-app" is free again
docker rm node-app


__________________________________________________________________________________________
Flask App




# Set a variable holding the full folder path inside your TEMP directory
$dir = "$env:TEMP\docker-python-app"
# Create that folder; -Force avoids errors if it exists; Out-Null hides output
New-Item -ItemType Directory -Force -Path $dir | Out-Null
# Move into that folder so files are written there
Set-Location $dir

# --- Write the Flask application source file (app.py) ---
@'
from flask import Flask
app = Flask(__name__)
@app.route('/')
def hello():
    return 'Hello from Docker Flask App!'
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
'@ | Set-Content -Path app.py    # Save the above text into app.py

# --- Write the Python dependency list (requirements.txt) ---
@'
flask==3.0.0
'@ | Set-Content -Path requirements.txt    # Save the above text into requirements.txt

# --- Write the Dockerfile (the image build recipe) ---
@'
FROM python:3.11-slim
WORKDIR /app
COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt
COPY app.py ./
EXPOSE 5000
RUN useradd -r appuser && chown -R appuser /app
USER appuser
CMD ["python", "app.py"]
'@ | Set-Content -Path Dockerfile    # Save the above text into Dockerfile

# Build the image from the Dockerfile and tag it "flask-demo"
docker build -t flask-demo .
# Run the image in the background, mapping host port 5000 -> container 5000
docker run -d -p 5000:5000 --name flask-app flask-demo
# Send an HTTP request to confirm the Flask app responds
curl.exe http://localhost:5000
# Stop the running container
docker stop flask-app
# Delete the stopped container to free the name "flask-app"
docker rm flask-app

_________________________________________________________________________________________________________


Multi Stage


# Set a variable holding the full folder path inside your TEMP directory
$dir = "$env:TEMP\docker-multistage"
# Create that folder; -Force avoids errors if it exists; Out-Null hides output
New-Item -ItemType Directory -Force -Path $dir | Out-Null
# Move into that folder so the Dockerfile is written there
Set-Location $dir

# --- Write the multi-stage Dockerfile ---
# (Stage 1 builds the file using a big node image; Stage 2 copies only the result
#  into a tiny nginx image, so the final image stays small)
@'
# Stage 1: Build
FROM node:18 AS builder
WORKDIR /app
RUN echo '<h1>Built with Multi-Stage Docker</h1>' > index.html
# Stage 2: Production
FROM nginx:alpine
COPY --from=builder /app/index.html /usr/share/nginx/html/
EXPOSE 80
'@ | Set-Content -Path Dockerfile    # Save the above text into Dockerfile

# Build the image from the Dockerfile and tag it "multistage-demo"
docker build -t multistage-demo .
# Show the image's size to confirm the multi-stage build kept it small
docker images multistage-demo
# Run the image in the background, mapping host port 8080 -> container port 80
docker run -d -p 8080:80 --name ms-app multistage-demo
# Send an HTTP request to confirm nginx serves the built page
curl.exe http://localhost:8080
# Stop the running container
docker stop ms-app
# Delete the stopped container to free the name "ms-app"
docker rm ms-app




