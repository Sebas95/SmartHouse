

LIB = EmbeddedServer
OBJ = $(LIB).o 
#CC = arm-poky-linux-gnueabi-gcc -march=armv7ve -marm -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/poky/2.3/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi

CFLAGS = -c -Wall
#Estática
libembeddedserver.a : $(OBJ)
		$(CC) $(CFLAGS) EmbeddedServer.c ServerUtils.c pinDriver.c -I ./ 
		ar rv libEmbeddedServer.a $(OBJ)
		ranlib libEmbeddedServer.a
		nm -s libEmbeddedServer.a

clean:
		rm *.a *.o
