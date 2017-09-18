#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <fcntl.h>
#include <stdbool.h>


char validacion;

void guarda_Archivo(char datos[99999], char path [99999]){
	FILE *archivo;
	char buffer[1024];
	bool vacio = true;
	bool ban=false;
	int k =0;


    archivo = fopen(path, "r+");


    printf("los datos son%s\n", datos);
    if(archivo){
    	printf("el archivo fue abierto correctamente\n");
    }else{
       printf("el archivo no fue abierto\n"); //
    }

	char caracter;				

	while((caracter = fgetc(archivo)) != EOF){
		if (caracter=='['){
			vacio =false;
			buffer[0]= '[';
			
			break;
		}else{
			vacio = true;
			break;
		}
	}
	fclose(archivo);
	archivo = fopen(path, "r+");
	while (feof(archivo) == 0 && !vacio){
		fgets(buffer,sizeof(buffer),archivo);
	}
	for (int i = 0; i < 1024; ++i){
		if(vacio){
			if (ban){
				buffer[i] = datos[k];
				if (datos[k]=='}'){
					
					buffer[i+1]=' ';
					buffer[i+2]=']';
					ban =false;
					break;
				}
				k=k+1;
			}
			else{
				buffer[i] = '[';
				buffer[i+1]=' ';
				i=i+1;
				ban=true;
			}
		}else{
			if (ban){
				buffer[i] = datos[k];
				if (datos[k]=='}'){
					printf("esta por terminar\n");
					buffer[i+1]=' ';
					buffer[i+2]=']';
					ban =false;
					break;
				}
				k=k+1;
			}else if(buffer[i]== ']'){
				buffer[i] = ',';
				buffer[i+1]=' ';
				i=i+1;
				ban=true;
			}
		}
	}
	printf("el json: %s\n", buffer);
	fseek (archivo, 0 , SEEK_SET);
	fputs( buffer,archivo);
	fclose(archivo);
}

void validar_cuenta(char datos[99999], char path [99999]){
	FILE *archivo;
	char datos_entrantes[1024];
	char datos_base[1024];
	char buffer[1024];
	bool inicia_leer=false;
	bool lee_entrante=false;
	bool termino=false;
	char retorna;
	int contador =0;

	archivo = fopen(path, "r+");
	while (feof(archivo) == 0){
		fgets(buffer,sizeof(buffer),archivo);
	}
	printf("el archivo cargado es : %s\n", buffer);
	
	for (int i = 0; i < 1024; ++i)
	{
		if (datos[i] == '{' || lee_entrante)
		{
			datos_entrantes[i] = datos[i];
			lee_entrante = true;
		}
		else if (datos[i] == '}')
		{
			datos_entrantes[i] = datos[i];
			lee_entrante = false;
		}
	}

	printf("datos_entrantes: %s\n", datos_entrantes);


	for (int i = 0; i < 1024; ++i){
		
		if (buffer[i]=='}'){
			inicia_leer =false;
			datos_base[contador] = buffer[i];
			printf("datos_base: %s\n", datos_base);
			contador = 0;
			
			for (int i = 0; i < 1024; ++i)
			{
				if (datos_entrantes[i] == datos_base[i])
				{
					
					retorna = 'C';
					termino = true;
					if (datos_base[i]=='}')
					{
						break;
					}
				}else{
					
					retorna = 'I';
					termino = false;
					break;
				}
			}
			
		}else if (termino){
			validacion = retorna;
			break;
		}
		else if (buffer[i] == '{' || inicia_leer){
			datos_base[contador] = buffer[i];
			inicia_leer = true;
			contador= contador+1;
		}
		else if (buffer[i]==']')
		{
			validacion = retorna;
		}
		
	}
	if (termino)
	{
		validacion = retorna;
	}
	fclose(archivo);
}


char* get_luces(char datos[99999])
{
	char* datos_entrantes= (char*)calloc(100,sizeof(char));
	bool lee_entrante=false;
	int i; 
	for (i = 0; i < 1024; ++i)
	{
		if (datos[i] == '{' || lee_entrante)
		{
			datos_entrantes[i] = datos[i];
			lee_entrante = true;
		}
		else if (datos[i] == '}')
		{
			datos_entrantes[i] = datos[i];
			lee_entrante = false;
		}
	}

	return datos_entrantes;

}

short retStateShort(char c)
{
	if(c=='0')
		return 0;
	else
		return 1;
}


const char* retState(short c)
{
	if(c==0)
		return "0";
	else
		return "1";
}