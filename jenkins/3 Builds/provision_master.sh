#!/bin/bash

# Install Java

sudo apt-get update

sudo apt install -y openjdk-14-jdk openjdk-14-jre

java -version

# Install Jenkins

wget -q -O - https://pkg.jenkins.io/debian-stable/jenkins.io.key | sudo apt-key add -

sudo sh -c 'echo deb https://pkg.jenkins.io/debian-stable binary/ > \
            /etc/apt/sources.list.d/jenkins.list'

sudo apt-get update

sudo apt-get install jenkins
