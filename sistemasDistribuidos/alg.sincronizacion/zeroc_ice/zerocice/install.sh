#!/bin/bash

sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv B6391CB2CFBA643D
sudo apt-add-repository -s "deb http://zeroc.com/download/Ice/3.7/ubuntu`lsb_release -rs` stable main"

sudo apt-get update
sudo apt-get install -y zeroc-ice-all-runtime zeroc-ice-all-dev

apt-get source zero-ice

sudo apt autoclean
apt clean
sudo apt update