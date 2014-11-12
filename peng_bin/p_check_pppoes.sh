#!/bin/bash

if [ "`/usr/bin/id -u`" != "0" ]
then
    echo "you must be root;"
    exit 1
fi

tcpdump -n -i eth0 pppoes

exit 0
