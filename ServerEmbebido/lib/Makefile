

LIB = pinDriver
OBJ = $(LIB).o 
#CC = arm-poky-linux-gnueabi-gcc -march=armv7ve -marm -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/poky/2.3/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi

CFLAGS = -c -Wall
#Dinamica
libpinDriver.so: 
		$(CC) $(CFLAGS) pinDriver.c -I ../include -fPIC
		$(LD) -o libpinDriver.so $(OBJ) -shared

clean:
		rm *.o *.so
