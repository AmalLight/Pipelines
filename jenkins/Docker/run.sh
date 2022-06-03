#!/bin/bash

docker run -it \
           \
           --rm \
           \
           -u root \
           \
           -p 8080:8080 \
           \
           -v /home/kaumi/Documents/Jenkins/Docker/share:/var/jenkins_home \
           -v /var/run/docker.sock:/var/run/docker.sock \
           \
           --name tmp_jenkins \
           \
           my_jenkins_pipeline:latest
