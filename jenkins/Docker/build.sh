#!/bin/bash

docker build .

docker image tag jenkins/jenkins:latest my_jenkins:latest
