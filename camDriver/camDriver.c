#include <stdlib.h>
#include <stdio.h>
//#include <string.h>
#include "camDriver.h"
#include <unistd.h>

int main(){
	takePicture();
}

void takePicture(){
	system(TAKE_PICTURE_DEFAULT);
}
