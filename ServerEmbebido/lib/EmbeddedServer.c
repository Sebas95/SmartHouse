/*
AUTHOR: Abhijeet Rastogi (http://www.google.com/profiles/abhijeet.1989)

http://blog.abhijeetr.com/2010/04/very-simple-http-server-writen-in-c.html

This is a very simple HTTP server. Default port is 10000 and ROOT for the server is your current working directory..

You can provide command line arguments like:- $./a.out -p [port] -r [path]

for ex. 
$./server -p 1000 -r /home/sebastian95/Documents/GitHub/SmartHouse/ServerEmbebido
to start a server at port 50000 with root directory as "/home"

$./server

*/

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

#define CONNMAX 1000
#define BYTES 1024

char *ROOT;
int listenfd, clients[CONNMAX];
char validacion;


//start server
void startServer(char *port, int *listenfd)
{
    struct addrinfo hints, *res, *p;

    // getaddrinfo for host
    memset (&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if (getaddrinfo( NULL, port, &hints, &res) != 0)
    {
        perror ("getaddrinfo() error");
        exit(1);
    }
    // socket and bind
    for (p = res; p!=NULL; p=p->ai_next)
    {
        *listenfd = socket (p->ai_family, p->ai_socktype, 0);
        if (*listenfd == -1) continue;
        if (bind(*listenfd, p->ai_addr, p->ai_addrlen) == 0) break;
    }
    if (p==NULL)
    {
        perror ("socket() or bind()");
        exit(1);
    }

    freeaddrinfo(res);

    // listen for incoming connections
    if ( listen (*listenfd, 1000000) != 0 )
    {
        perror("listen() error");
        exit(1);
    }
}

//client connection
void respond(int n)
{
    char mesg[99999], datos[99999], *reqline[3], data_to_send[BYTES], path[99999];
    int rcvd, fd, bytes_read;

    memset( (void*)mesg, (int)'\0', 99999 );

    rcvd=recv(clients[n], mesg, 99999	, 0);

    if (rcvd<0)    // receive error
        fprintf(stderr,("recv() error\n"));
    else if (rcvd==0)    // receive socket closed
        fprintf(stderr,"Client disconnected upexpectedly.\n");
    else    // message received
    {
        printf("%s", mesg);
        int j=0;
        bool bandera = false;
        for (int i = 0; i < 99999; i++)
        {
        	if (mesg[i]=='{' || bandera == true)
        	{
        		datos[j] = mesg[i];
        		bandera = true;
        		j=j+1;
        	}

        }
        reqline[0] = strtok (mesg, " \t\n");
        //aqui se iniciA el get
        if ( strncmp(reqline[0], "GET\0", 4)==0 )
        {
            reqline[1] = strtok (NULL, " \t");
            reqline[2] = strtok (NULL, " \t\n");
            if ( strncmp( reqline[2], "HTTP/1.0", 8)!=0 && strncmp( reqline[2], "HTTP/1.1", 8)!=0 )
            {
                write(clients[n], "HTTP/1.0 400 Bad Request\n", 25);
            }
            else
            {	
                if ( strncmp(reqline[1], "/\0", 2)==0 )
                    reqline[1] = "/index.html";        //Because if no file is specified, index.html will be opened by default (like it happens in APACHE...

                if ( strncmp(reqline[1], "/lights/\0", 2)==0 )
                    reqline[1] = "/lights.json";        //Because if no file is specified, index.html will be opened by default (like it happens in APACHE...

                strcpy(path, ROOT);
                strcpy(&path[strlen(ROOT)], reqline[1]);
                printf("file: %s\n", path);

                if ( (fd=open(path, O_RDONLY))!=-1 )    //FILE FOUND
                {
                    send(clients[n], "HTTP/1.0 200 OK\nAccess-Control-Allow-Origin:http://localhost:8383\nAccess-Control-Allow-Headers:Content-Type\nAccess-Control-Allow-Methods:GET,PUT,POST,OPTIONS\nContent-Type:application/json;charset=UTF-8\n\n", 203, 0);
                    //send(clients[n], "HTTP/1.0 200 OK\nAccess-Control-Allow-Origin:*\nAccess-Control-Allow-Headers:Content-Type\n\n", 89, 0);
                    while ( (bytes_read=read(fd, data_to_send, BYTES))>0 )
                        write (clients[n], data_to_send, bytes_read);
                }
                else    write(clients[n], "HTTP/1.0 404 Not Found\n", 23); //FILE NOT FOUND
            }
        }

        //Aqui se realiza el options
        else if ( strncmp(reqline[0], "OPTIONS\0", 4)==0 )
        {
            reqline[1] = strtok (NULL, " \t");
            reqline[2] = strtok (NULL, " \t\n");
            if ( strncmp( reqline[2], "HTTP/1.0", 8)!=0 && strncmp( reqline[2], "HTTP/1.1", 8)!=0 )
            {
                write(clients[n], "HTTP/1.0 400 Bad Request\n", 25);
            }
            else
            {	
            	if (strncmp(reqline[1], "/interfaz/\0", 2)==0)
            	{
            		send(clients[n], "HTTP/1.0 200 OK\nAccess-Control-Allow-Origin:http://localhost:8383\nAccess-Control-Allow-Headers:Content-Type\nAccess-Control-Allow-Methods:GET,PUT,POST,OPTIONS\ncharset=UTF-8\n\n", 173, 0);
            	}
                if ( strncmp(reqline[1], "/users/\0", 2)==0 || strncmp(reqline[1], "/login/\0", 2)==0){
                    reqline[1] = "/user.json";        //Because if no file is specified, index.html will be opened by default (like it happens in APACHE...
                

	                strcpy(path, ROOT);
	                strcpy(&path[strlen(ROOT)], reqline[1]);
	                printf("file: %s\n", path);

	                if ( (fd=open(path, O_RDONLY))!=-1 )    //FILE FOUND
	                {
	                    send(clients[n], "HTTP/1.0 200 OK\nAccess-Control-Allow-Origin:http://localhost:8383\nAccess-Control-Allow-Headers:Content-Type\nAccess-Control-Allow-Methods:GET,PUT,POST,OPTIONS\nContent-Type:application/json;charset=UTF-8\n\n", 203, 0);
	                    //send(clients[n], "HTTP/1.0 200 OK\nAccess-Control-Allow-Origin:*\nAccess-Control-Allow-Headers:Content-Type\n\n", 89, 0);
	                    //while ( (bytes_read=read(fd, data_to_send, BYTES))>0 )
	                        //write (clients[n], data_to_send, bytes_read);
	                }
            	}
                else    write(clients[n], "HTTP/1.0 404 Not Found\n", 23); //FILE NOT FOUND
            }
        }


        //aqui inicia el post
        else  if ( strncmp(reqline[0], "POST\0", 4)==0 )
        {
            reqline[1] = strtok (NULL, " \t");
            reqline[2] = strtok (NULL, " \t\n");
            if ( strncmp( reqline[2], "HTTP/1.0", 8)!=0 && strncmp( reqline[2], "HTTP/1.1", 8)!=0 )
            {
                write(clients[n], "HTTP/1.0 400 Bad Request\n", 25);
            }
            else
            {   
                if ( strncmp(reqline[1], "/\0", 2)==0 )
                    reqline[1] = "/index.html";        //Because if no file is specified, index.html will be opened by default (like it happens in APACHE...

                if ( strncmp(reqline[1], "/users/\0", 2)==0 )
                    reqline[1] = "/user.json";        //Because if no file is specified, index.html will be opened by default (like it happens in APACHE...

                strcpy(path, ROOT);
                strcpy(&path[strlen(ROOT)], reqline[1]);
                printf("file: %s\n", path);

                if ( (fd=open(path, O_RDONLY))!=-1 )    //FILE FOUND
                {
                	guarda_Archivo(datos,path);
                    send(clients[n], "HTTP/1.0 200 OK\nAccess-Control-Allow-Origin:http://localhost:8383\nAccess-Control-Allow-Headers:Content-Type\nAccess-Control-Allow-Methods:GET,PUT,POST,OPTIONS\nContent-Type:application/json;charset=UTF-8\n\n", 203, 0);
                    
                    while ( (bytes_read=read(fd, data_to_send, BYTES))>0 )
                        write (clients[n], data_to_send, bytes_read);

                }
                else    write(clients[n], "HTTP/1.0 404 Not Found\n", 23); //FILE NOT FOUND
            }
        }

        else  if ( strncmp(reqline[0], "PUT\0", 4)==0 )
        {
            reqline[1] = strtok (NULL, " \t");
            reqline[2] = strtok (NULL, " \t\n");
            if ( strncmp( reqline[2], "HTTP/1.0", 8)!=0 && strncmp( reqline[2], "HTTP/1.1", 8)!=0 )
            {
                write(clients[n], "HTTP/1.0 400 Bad Request\n", 25);
            }
            else
            {   
                if ( strncmp(reqline[1], "/\0", 2)==0 )
                    reqline[1] = "/index.html";        //Because if no file is specified, index.html will be opened by default (like it happens in APACHE...
                
                if ( strncmp(reqline[1], "/interfaz/\0", 2)==0 ){
                	printf("\nsi esta entrando\n");
                	printf("\nesto es una prueba\n");
                	send(clients[n], "HTTP/1.0 200 OK\nAccess-Control-Allow-Origin:http://localhost:8383\nAccess-Control-Allow-Headers:Content-Type\nAccess-Control-Allow-Methods:GET,PUT,POST,OPTIONS\ncharset=UTF-8\n\n", 173, 0);
                }
                
                if ( strncmp(reqline[1], "/login/\0", 2)==0 ){
                    reqline[1] = "/user.json";        //Because if no file is specified, index.html will be opened by default (like it happens in APACHE...
                
	                strcpy(path, ROOT);
	                strcpy(&path[strlen(ROOT)], reqline[1]);
	                printf("file: %s\n", path);

	                if ( (fd=open(path, O_RDONLY))!=-1 )    //FILE FOUND
	                {
	                	validar_cuenta(datos,path);
	                	printf("EL CaRACTER RETORNADO: %c\n",validacion);
	                    if (validacion=='C')
	                    {
	                        printf("La validacion es correcta\n");
	                    	send(clients[n], "HTTP/1.0 200 OK\nAccess-Control-Allow-Origin:http://localhost:8383\nAccess-Control-Allow-Headers:Content-Type\nAccess-Control-Allow-Methods:GET,PUT,POST,OPTIONS\nContent-Type:application/json;charset=UTF-8\n\n", 203, 0);
	                    }
	                    else
	                    {
	                        printf("La validacion es incorrecta\n");
	                    	send(clients[n], "HTTP/1.0 500 NO\nAccess-Control-Allow-Origin:http://localhost:8383\nAccess-Control-Allow-Headers:Content-Type\nAccess-Control-Allow-Methods:GET,PUT,POST,OPTIONS\nContent-Type:application/json;charset=UTF-8\n\n", 203, 0);
	                    }
	                    
	                    
	                    while ( (bytes_read=read(fd, data_to_send, BYTES))>0 )
	                        write (clients[n], data_to_send, bytes_read);

	                }
                }
                
                else    write(clients[n], "HTTP/1.0 404 Not Found\n", 23); //FILE NOT FOUND
            }
        }
    }

    //Closing SOCKET
    shutdown (clients[n], SHUT_RDWR);         //All further send and recieve operations are DISABLED...
    close(clients[n]);
    clients[n]=-1;
}


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