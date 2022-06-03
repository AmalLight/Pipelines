#!/bin/bash

rm -rf my_jenkins_"$1".tar

sync

docker save my_jenkins_"$1" > my_jenkins_"$1".tar

sync
