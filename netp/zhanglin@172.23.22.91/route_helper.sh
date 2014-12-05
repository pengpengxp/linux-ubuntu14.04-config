#!/bin/bash
interface=eth0
INTERGATEWAY="172.23.22.1"

if [ "`/usr/bin/id -u`" != "0" ]
then
    echo you must be root!!
    exit 1
fi

echo "add the shangjiao to the route path"
##add ftp://ftp.sjtu.edu.cn to the route path
##shangjiao
route add -net 202.38.97.0 netmask 255.255.255.0 dev $interface gw $INTERGATEWAY
echo "add the beijiao to the route path"
##beijiaotong
route add -net 202.112.154.0 netmask 255.255.255.0 dev $interface gw $INTERGATEWAY
echo "add the qinghua to the route path"
##qinghua
route add -net 166.111.8.0 netmask 255.255.255.0 dev $interface gw $INTERGATEWAY
echo "add the cqupt to the route path"
##cqupt
route add -net 202.202.43.0 netmask 255.255.255.0 dev $interface gw $INTERGATEWAY
route add -net 202.202.32.0 netmask 255.255.255.0 dev $interface gw $INTERGATEWAY
route add -net 172.16.0.0 netmask 255.240.0.0 dev $interface gw $INTERGATEWAY
echo "add the 163 to the route path"
##163
route add -net 123.58.173.0 netmask 255.255.255.0 dev $interface gw $INTERGATEWAY


exit 0
