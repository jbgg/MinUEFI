
PROG=bootx64.efi

OBJ= main.o

# PE+ cross compiler
CROSS=x86_64-w64-mingw32-

S=.

INC=$(S)/include

CC=$(CROSS)gcc
CFLAGS= -O2
CFLAGS+= -Wall -Wextra #-Werror
CFLAGS+= -fno-stack-protector
CFLAGS+= -ffreestanding
CFLAGS+= -no-pie
CFLAGS+= -I$(INC)

ASFLAGS=

LD=$(CROSS)ld
LDFLAGS=-nostdlib -shared
LDFLAGS+=--subsystem 10
LDFLAGS+= -e efi_main

all : $(PROG)

$(PROG) : $(OBJ)
	$(LD) $(LDFLAGS) -o $(PROG) $(OBJ)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

%.o : %.S
	$(CC) $(ASFLAGS) -c -o $@ $^

clean: umount
	rm -rf $(PROG) $(OBJ)
	@rm -rf *~ .*~
	@cd include && rm -rf *~ .*~ && cd ..

# add next rule to /etc/fstab in order to avoid root
# `pwd`/hdd.img		`pwd`/mnt	vfat	noauto,loop,offset=17408,uid=`id -u`,gid=`id -g`,nosuid,user	0 	0

copy: $(PROG)
	mount mnt
	cp $(PROG) mnt/efi/boot
	umount mnt

umount: 
	umount mnt || (echo 'already umount'; exit 0)

# OVMF-pure-efi.fd is necessary, get it from edk2 project of tianocore

qemu: copy
	qemu-system-x86_64 -m 512 -enable-kvm \
		-bios OVMF-pure-efi.fd \
		-drive file=hdd.img,index=0,format=raw,media=disk \
		-monitor telnet:127.0.0.1:5575,server,nowait \
		-curses

debug: copy
	qemu-system-x86_64 -m 512 -enable-kvm \
		-bios OVMF-pure-efi.fd \
		-drive file=hdd.img,index=0,format=raw,media=disk \
		-monitor telnet:127.0.0.1:5575,server,nowait \
		-curses \
		-S -s

