#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pinDriver.h"
#include <unistd.h>


int main(){
	//printf("asd\"\"\n");
	//short systemReturnValue = 0;
	//int fd = sizeof("void setPin(char pinNumber,char state){");
	//printf("%d\n",fd);
	//char* gpioNumber = malloc(sizeof(1));
	//*gpioNumber = '1';
	//char* nuevoString = malloc(sizeof(40));
	//nuevoString = ECHO_EXPORT_1;
	//printf("Nuevo String %s\n",nuevoString);
	//strcat(nuevoString, gpioNumber);
	//printf("EXPORT 1 : %s\n",ECHO_EXPORT_1);
	//printf("EXPORT 2 : %s\n",ECHO_EXPORT_2);
	//printf("Prueba concatenacion: %s\n", nuevoString);
	/*char test[47] = ECHO;
	strcat(test, "\"out\"");
	strcat(test, MORE_THAN);
	strcat(test, ECHO_DIRECTION_1);
	strcat(test, "4");
	strcat(test, ECHO_DIRECTION_2);
	printf("%s\n",test);
	int size = sizeof(test);
	printf("Tamanio: %d\n",size);*/
	/*if(systemReturnValue != )
	system("echo \"4\" > /sys/class/gpio/export");
	system("echo \"out\" > /sys/class/gpio/gpio4/direction");
	system("echo \"1\" > /sys/class/gpio/gpio4/value");

	int fd;
	char buf[100]; 
	//int gpio = XX;

	fd = open("/sys/class/gpio/export", O_RRONLY);

	//sprintf(buf, "%d", gpio); 

	read(fd, buf, strlen(buf));
	printf("%s\n",buf);
	close(fd);*/
	//init();
	//setPin(3,'o');
	
    init();	
	setPin(3,'o');
	writePin(3,0);
	usleep(1000000);
	writePin(3,1);

}

void init(){
	//char* test = malloc(sizeof())
	system("echo \"2\" > /sys/class/gpio/export");
	system("echo \"3\" > /sys/class/gpio/export");
	system("echo \"4\" > /sys/class/gpio/export");
}

void writePin(short pinNumber, short value){
	if(value != 0 && value != 1){
		printf("Wrong value, only accepted: 0 or 1\n");
	}

	else{
		char finalCall[47] = ECHO;
		char pinNumberAux[2] = "";
		sprintf(pinNumberAux, "\"%d\"", value);
		strcat(finalCall, pinNumberAux);
		strcat(finalCall, MORE_THAN);
		strcat(finalCall, PATH);
		sprintf(pinNumberAux, "%d", pinNumber);
		strcat(finalCall, pinNumberAux);
		strcat(finalCall, VALUE);
		printf("%s\n",finalCall);
		//system(finalCall);
	}
}



void setPin(short pinNumber,char state){ //0 for in, 1 for out
	char stateAux[3] = "";
	char pinNumberAux[2] = "";
	sprintf(pinNumberAux, "%d", pinNumber);
	if(state == 'o'){
		strcat(stateAux,"\"out\"");
	}
	else{ 
		if(state == 'i'){
			strcat(stateAux,"\"in\"");
		}
		else{
			printf("Wrong arguments can be 'i' or 'o'");
		}
	}
	char finalCall[47] = ECHO;
	strcat(finalCall, stateAux);
	strcat(finalCall, MORE_THAN);
	strcat(finalCall, PATH);
	strcat(finalCall, pinNumberAux);
	strcat(finalCall, DIRECTION);
	//system(finalCall);
	printf("%s\n",finalCall);

	//system("echo \"out\" > /sys/class/gpio/gpio4/direction");

}
