#!/bin/bash
# set my resolution
# still need to test

# if [ "`/usr/bin/id -u`" != "0" ]
# then
#     echo you must be root!!
#     exit 1
# fi

xrandr --newmode "1440x900_60.00"  106.50  1440 1528 1672 1904  900 903 909 934 -hsync +vsync
xrandr --addmode VGA-1 "1440x900_60.00"
xrandr --output VGA-1 --mode 1440x900_60.00

exit 0
