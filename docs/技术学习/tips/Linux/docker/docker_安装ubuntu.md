# Docker install Ubuntu

## 可以查看可用的ubuntu版本
访问Ubuntu[镜像库地址](https://hub.docker.com/_/ubuntu?tab=tags&page=1)

## 获取最新的Ubuntu镜像
```shell
docker pull ubuntu
或者
docker pull ubuntu:latest
```

## 查看本地镜像
```
docker images
```
## 运行Ubuntu容器，并且可以通过exec命令进入ubuntu容器
```
运行
docker run -itd --name ubuntu-test ubuntu

进入
docker exec -it ubuntu-test /bin/bash
```
