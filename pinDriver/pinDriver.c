#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pinDriver.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


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
	
	/*int fd = open("/sys/class/gpio/gpio3/value",(O_RDWR|O_SYNC));

	char data[128];
 
    if(read(fd, data, 128) < 0)
     	write(2, "An error occurred in the read.\n", 31);
 
 	printf("%s\n",data);
    exit(0);*/

    //exportPin(4);

	//Test used to write to the pins
	/*
    init();	
	setPin(2,'i');
	setPin(3,'i');
	setPin(4,'i');	
	writePin(2,0);
	writePin(3,1);
	writePin(4,1);
	*/
	
	//Test used for test the read of the pins

    init();	
	setPin(2,'i');
	setPin(3,'i');
	setPin(4,'i');	

	while(1){
		printf("---------------------------------------\n");
		usleep(1000000);
		printf("Valor del pin 2: %d\n",readPin(2));
		printf("Valor del pin 3: %d\n",readPin(3));
		printf("Valor del pin 4: %d\n",readPin(4));
	}

}
//This function itializates the required pins using exportPin
void init(){
	exportPin(2);
	exportPin(3);
	exportPin(4);

	//system("echo \"3\" > /sys/class/gpio/export");
	//system("echo \"4\" > /sys/class/gpio/export");
}

/**
** pinNumber is the number of GPIO to export
** This is the functions that allows to export a pin named un pinNumber
**/


void exportPin(short pinNumber){
	char openCall[47] = PATH;
	char pinNumberAux[2] = "";
	char finalCall[47] = ECHO;

	sprintf(pinNumberAux, "%d", pinNumber);

	strcat(openCall, pinNumberAux);	
	strcat(openCall, "/value");	
	//printf("Call para el valor: %s\n",openCall);
	//-------------------Check if pin is exported
	int fd = open(openCall,(O_RDWR|O_SYNC));

	char data[128];
 
    if(read(fd, data, 128) < 0){
    	sprintf(pinNumberAux, "\"%d\"", pinNumber);
		strcat(finalCall, pinNumberAux);
		strcat(finalCall, MORE_THAN);
		strcat(finalCall, PATH_EXPORT);
 		printf("Export pin: %s\n",pinNumberAux);
 		system(finalCall);
 		//printf("%s\n",data);
     	
     }
 	else{
		printf("Pin %s already exported.\n",pinNumberAux);
 	}

}

/**	pinNumber is the number of GPIO to write
**  value is te value to write in the pin
** This functions write to a specified pinNumber the value 
**/

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
		printf("Writting %d in pin: %s\n",value,pinNumberAux);
		system(finalCall);
	}
}


/**
** pinNumber is the number of the GPIO to set
** state is the state of which will be the GPIO out or in
** This function allow to set a pin as in or out
**/
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
	printf("Setting pin %s to: %s\n",pinNumberAux,stateAux);
	system(finalCall);

	//system("echo \"out\" > /sys/class/gpio/gpio4/direction");
}

/*
** The parameter pinNumber is used to specified the pin to read
** This function is used to read from the pins
*/

short readPin(short pinNumber){
	char openCall[47] = PATH;
	char pinNumberAux[2] = "";
	sprintf(pinNumberAux, "%d", pinNumber);
	strcat(openCall, pinNumberAux);	
	strcat(openCall, "/value");	
	//printf("Call para el valor: %s\n",openCall);
	//-------------------Check if pin is exported
	int fd = open(openCall,(O_RDWR|O_SYNC));
	char* data = malloc(sizeof(char));
    if(read(fd, data, 1) < 0){
 		printf("The pin %d is not configured\n",pinNumber);
     	return -1;
     }
 	else{
		//printf("The value of pin %d is: %s\n",pinNumber,data);
		short* returnValue = malloc(sizeof(short));
		*returnValue = atoi(data);
		return *returnValue;
 	}
}
