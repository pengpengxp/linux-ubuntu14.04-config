# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

# If not running interactively, don't do anything
[ -z "$PS1" ] && return

# don't put duplicate lines or lines starting with space in the history.
# See bash(1) for more options
HISTCONTROL=ignoreboth

# append to the history file, don't overwrite it
shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# If set, the pattern "**" used in a pathname expansion context will
# match all files and zero or more directories and subdirectories.
#shopt -s globstar

# make less more friendly for non-text input files, see lesspipe(1)
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "$debian_chroot" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, unless we know we "want" color)
case "$TERM" in
    xterm-color) color_prompt=yes;;
esac

# uncomment for a colored prompt, if the terminal has the capability; turned
# off by default to not distract the user: the focus in a terminal window
# should be on the output of commands, not on the prompt
#force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	# We have color support; assume it's compliant with Ecma-48
	# (ISO/IEC-6429). (Lack of such support is extremely rare, and such
	# a case would tend to support setf rather than setaf.)
	color_prompt=yes
    else
	color_prompt=
    fi
fi

if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

# If this is an xterm set the title to user@host:dir
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac

# enable color support of ls and also add handy aliases
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'

    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

# some more ls aliases
alias ll='ls -alFh'
alias la='ls -A'
alias l='ls -CF'
alias lm='ls -al |more'

alias bohao="sudo /home/netp/open_keeper/peng"
alias bohao_wireless="sudo /home/netp/open_keeper/peng_wireless"
alias duankai="sudo poff -a"

alias baidu="w3m www.baidu.com"
alias 163="w3m mirrors.163.com"
alias qinghua="w3m mirrors.tuna.tsinghua.edu.cn"
alias shangjiao="w3m ftp.sjtu.edu.cn"

alias bianyi="gcc -g"
alias niujing="sdcv -u niujing"
alias hanying="sdcv -u hanying"
alias hanyu="sdcv -u hanyu"
alias run="make clean;make;./a.out"
alias ei="emacsclient -nw"
alias emacsstart="emacs-24.3 --daemon"
alias emacsstop="emacsclient -e '(kill-emacs)'"
alias emacsrestart="emacsstop ; emacsstart"
alias p_date='date +%y-%m-%d\ %H:%M:%S'
alias p_cc='xclip -selection clipboard'
alias p_pp='xclip -selection clipboard -o'


alias rm='rm -i'
# Add an "alert" alias for long running commands.  Use like so:
#   sleep 10; alert
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'

# Alias definitions.
# You may want to put all your additions into a separate file like
# ~/.bash_aliases, instead of adding them here directly.
# See /usr/share/doc/bash-doc/examples in the bash-doc package.

if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
if [ -f /etc/bash_completion ] && ! shopt -oq posix; then
    . /etc/bash_completion
fi


##to change my key binding
key_result=`xmodmap | grep lock |awk '{x = $3;print x}'`
if [ $key_result != "(0x76)" ]
then
   xmodmap /home/pengpengxp/change_key_binding/Xpeng.kmap
fi
###ifconfig
export PATH="$PATH":/sbin/;

###for the texlive
PATH=/usr/local/texlive/2013/bin/i386-linux:$PATH; 
export PATH
MANPATH=/usr/local/texlive/2013/texmf-dist/doc/man:$MANPATH; 
export MANPATH
INFOPATH=/usr/local/texlive/2013/texmf-dist/doc/info:$INFOPATH; 
export INFOPATH

###I don't want garbage
alias em="emacs24-x"
alias virtualbox="virtualbox > /dev/null 2>&1 &"
alias thunderbird="/usr/local/pengpengxp_sw/thunderbird/thunderbird-bin > /dev/null 2>&1 &"
alias vmplayer="vmplayer > /dev/null 2>&1 &"
alias firefox="firefox > /dev/null 2>&1 &"
alias chrome="google-chrome > /dev/null 2>&1 &"
alias stardict="stardict > /dev/null 2>&1 &"
alias protect_eye="protect_eye.sh > /dev/null 2>&1 &"
alias clean='rm -rvf *~'

###for the emacs in terminal
export TERM=xterm-256color




export PATH=/usr/sbin/:$PATH

WORKDIR=/home/pengpengxp/xiepeng_learn/thesis/src/cpu_search

##use fcitx
##export XMODIFIERS="@im=fcitx"
##export GTK_IM_MODULE=fcitx
##export QT_IM_MODULE=fcitx

# pengpengxp's scripts
export PATH=/home/pengpengxp/peng_bin/:$PATH


export DBUS_SESSION_BUS_ADDRESS

#for java
export PATH=/usr/local/jre1.7.0_67/bin/:usr/local/jdk1.8.0_05/bin:$PATH

export JAVA_HOME=/usr/local/jdk1.8.0_05
export JRE_HOME=/usr/local/jre1.7.0_67/
export CLASSPATH=./:/usr/local/jre1.7.0_67/lib:/usr/local/jdk1.8.0_05/lib

#for android
export PATH=/usr/local/android-sdk-linux/platform-tools:/usr/local/android-sdk-linux/tools/:$PATH
export ANDROID_SDK_HOME=/usr/local/android-sdk-linux


#start after login in
if [ "`xrandr|grep "1440 x 900"`" == "" ]
then
    /home/pengpengxp/peng_bin/p_set_resolution.sh
fi

# use kindlegen and texi2mobi
export PATH=$PATH:/usr/local/kindlegen_linux_2.6_i386_v2_9/:/usr/local/texi2mobi/

################################################################
# 使用percol配置成文件管理器。可以剪切复制这些。网上找的。
[ $(uname -s | grep -c CYGWIN) -eq 1 ] && OS_NAME="CYGWIN" || OS_NAME=`uname -s`
function pclip() {
    if [ $OS_NAME == CYGWIN ]; then
        putclip $@;
    elif [ $OS_NAME == Darwin ]; then
        pbcopy $@;
    else
        if [ -x /usr/bin/xsel ]; then
            xsel -ib $@;
        else
            if [ -x /usr/bin/xclip ]; then
                xclip -selection c $@;
            else
                echo "Neither xsel or xclip is installed!"
            fi
        fi
    fi
}

function ff()
{
    local fullpath=$*
    local filename=${fullpath##*/} # remove "/" from the beginning
    filename=${filename##*./} # remove  ".../" from the beginning
    echo file=$filename
    #  only the filename without path is needed
    # filename should be reasonable
    local cli=`find $PWD -not -iwholename '*/target/*' -not -iwholename '*.svn*' -not -iwholename '*.git*' -not -iwholename '*.sass-cache*' -not -iwholename '*.hg*' -type f -iwholename '*'${filename}'*' -print 2>/dev/null | percol `
    echo ${cli}
    echo -n ${cli} |pclip;
}
################################################################

################################################################
# using git conveniently
################################################################
alias gst='git status'
alias gl='git log'
alias ga='git add'
alias gc='git commit'
################################################################
