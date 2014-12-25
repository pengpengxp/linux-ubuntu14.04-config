# p_switch_key.sh --- 
# 
# Filename: p_switch_key.sh
# Description: switch the layout of my keyboard
# Author: pengpengxp
# Email: pengpengxppri@gmail.com
# Created: 四 12月 25 20:26:30 2014 (+0800)
# Version: 
# Last-Updated: 
# 
# 

# TODO: how to switch back to the default?

# Code:


#!/bin/bash
# !Swap life control and left alt
# !!only switch on one level is enough 
xmodmap -e "remove mod1 = Alt_L"
xmodmap -e "remove control = Control_L"
xmodmap -e "keycode 37 = Alt_L"
xmodmap -e "keycode 64 = Control_L"
xmodmap -e "keycode 135 = Control_L"
xmodmap -e "add control = Control_L"
xmodmap -e "add mod1 = Alt_L"



# !another method which can also work->change the other level.word flawlessly
xmodmap -e "clear lock"
xmodmap -e "add lock = Insert"

# !change the caps_lock to control->IMPORTANT:I clear the lock befor
# !!the same name of control can work,BUT i don't know why
xmodmap -e "keycode 66 = Control_L"
xmodmap -e "add control = Control_L"




# p_switch_key.sh ends here
