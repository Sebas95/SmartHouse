#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pinDriver.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


//This function itializates the required pins using exportPin
void init(){
	exportPin(2);
	exportPin(3);
	exportPin(4);

	setPin(2,'o');
	setPin(3,'o');
	setPin(4,'o');

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
