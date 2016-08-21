#!/bin/bash

sudo rmmod mod_dev
sudo insmod mod_dev.ko

sudo rm /dev/hello_device
sudo mknod -m0666 /dev/hello_device c 244 0
