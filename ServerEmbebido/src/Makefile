

all: WebServer
 
APP = WebServer
SRC = $(APP).c
#CC = arm-poky-linux-gnueabi-gcc -march=armv7ve -marm -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/poky/2.3/#sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi

CFLAGS = -c
#Estática
WebServer: $(SRC)
#-I es para el .h  y -L donde está el .a o el .so
		$(CC) -L ../lib -I ../include -o ../bin/$(APP) $(SRC) -lEmbeddedServer

clean: 
		rm  ../bin/$(APP)
		
