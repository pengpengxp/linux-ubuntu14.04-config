#!/bin/bash
# change the IP to 192 and 172 to connect the internet

if [ `id -u` != 0 ]
then
    echo "you must be root";
    exit 1;
fi

ifconfig eth0 down;
ifconfig eth0 up;
ifconfig eth0 172.23.22.107 netmask 255.255.255.0;
route add default gw 172.23.22.1

exit 0;
