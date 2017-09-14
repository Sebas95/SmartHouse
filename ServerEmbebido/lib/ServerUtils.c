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
    	//printf("el malo\n");
       printf("el archivo no fue abierto\n"); //
    }

	char caracter;				
	//for (int i = 0; i < 1024; ++i){
	while((caracter = fgetc(archivo)) != EOF){
		//printf("el caracter es: %c\n",caracter);
		if (caracter=='['){
			vacio =false;
			buffer[0]= '[';
			
			//printf("entro vacio false\n");
			break;
		}else{
			vacio = true;
			//printf("entro vacio true\n");
			break;
		}
	}
	fclose(archivo);
	archivo = fopen(path, "r+");
	while (feof(archivo) == 0 && !vacio){
		fgets(buffer,sizeof(buffer),archivo);
	}
	//printf("el archivo cargado es : %s\n", buffer);
	for (int i = 0; i < 1024; ++i){
		if(vacio){
			//printf("esta dentro de vacio true\n");
			if (ban){
				//printf("esta dentro de ban true\n");
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
				//printf("esta dentro de [\n");
				buffer[i] = '[';//+'\n' + datos + '\n'+ ']';
				buffer[i+1]=' ';
				i=i+1;
				ban=true;
			}
		}else{
			if (ban){
				buffer[i] = datos[k];
				//printf("esta dentro del segundo a formar\n");
				if (datos[k]=='}'){
					printf("esta por terminar\n");
					buffer[i+1]=' ';
					buffer[i+2]=']';
					ban =false;
					break;
				}
				k=k+1;
			}else if(buffer[i]== ']'){
				//printf("esta dentro de la coma\n");
				buffer[i] = ',';//+'\n' + datos + '\n'+ ']';
				buffer[i+1]=' ';
				i=i+1;
				ban=true;
			}
		}
	}
	printf("el json: %s\n", buffer);
	fseek (archivo, 0 , SEEK_SET);
	////fprintf(archivo, buffer);
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
			//printf("el caracter final es %c\n", buffer[i]);
			printf("datos_base: %s\n", datos_base);
			contador = 0;
			
			for (int i = 0; i < 1024; ++i)
			{
				if (datos_entrantes[i] == datos_base[i])
				{
					//printf("CORRECTO/n" );
					retorna = 'C';
					termino = true;
					if (datos_base[i]=='}')
					{
						break;
					}
				}else{
					//printf("INCORRECTO****");
					retorna = 'I';
					termino = false;
					break;
				}
			}
			/*if (datos_entrantes == datos_base)
			{
				printf("CORRECTO\n" );
				retorna = 'C';
				break;
			}	
			else{
				printf("INCORRECTO\n");
				retorna = 'I';
			}*/
		}else if (termino){
			validacion = retorna;
			break;
		}
		else if (buffer[i] == '{' || inicia_leer){
			datos_base[contador] = buffer[i];
			//printf("el caracter es %c\n", buffer[i]);
			inicia_leer = true;
			contador= contador+1;
		}
		else if (buffer[i]==']')
		{
			//printf("\nESTOY EN EL RETURN\n");
			//printf("retorna %c\n", retorna);
			validacion = retorna;
		}
		
	}
	if (termino)
	{
		validacion = retorna;
	}

	
	//printf("el buffer: %s\n", buffer);

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
