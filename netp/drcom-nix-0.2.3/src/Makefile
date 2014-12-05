all:drcom-nix

drcom-nix:main.c global.h getpasswd.o drcom.o md5.o
	gcc -o drcom-nix main.c getpasswd.o drcom.o md5.o

drcom.o:drcom.h drcom.c global.h md5.h
	gcc -c drcom.c

md5.o:md5.c md5.h global.h
	gcc -c md5.c
	
getpasswd.o:getpasswd.c getpasswd.h
	gcc -c getpasswd.c


	
clean:
	rm *.o drcom-nix -f

install:
	rm /usr/bin/drcom-nix -f
	cp drcom-nix /usr/bin
	chmod +x /usr/bin/drcom-nix

