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
#include "ServerUtils.c"
#include "pinDriver.c"
#include "../include/EmbeddedServer.h"

#define CODIGO_TODAS_PUERTAS 6

char mesg[99999], datos[99999], *reqline[3], data_to_send[BYTES], path[99999];
int rcvd, fd, bytes_read;
short Puertas[4];
  


//start server
void startServer(char *port, int *listenfd)
{
	//init(); //init pins
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
void respond(int n,char* ROOT)
{
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
        if ( strncmp(reqline[0], "GET\0", 4)==0 )              get_verb(n);
        else if ( strncmp(reqline[0], "OPTIONS\0", 4)==0)      options_verb(n);
        else  if ( strncmp(reqline[0], "POST\0", 4)==0 )       post_verb(n);
        else  if ( strncmp(reqline[0], "PUT\0", 4)==0 )        put_verb(n);
    }
    //Closing SOCKET
    shutdown (clients[n], SHUT_RDWR);         //All further send and recieve operations are DISABLED...
    close(clients[n]);
    clients[n]=-1;
}

void options_verb(int n)
{
	if(checkBadRequest(n))
    {	
        if (strncmp(reqline[1], "/interfaz/\0", 10)==0)
        {
            		send(clients[n], "HTTP/1.0 200 OK\nAccess-Control-Allow-Origin:http://localhost:8383\nAccess-Control-Allow-Headers:Content-Type\nAccess-Control-Allow-Methods:GET,PUT,POST,OPTIONS\ncharset=UTF-8\n\n", 173, 0);
        }
        else if ( strncmp(reqline[1], "/users/\0", 2)==0 || strncmp(reqline[1], "/login/\0", 2)==0)
        {           
	        send(clients[n], SUCCESS_HEADER , strlen(SUCCESS_HEADER), 0);          
        }
        else    write(clients[n], "HTTP/1.0 404 Not Found\n", 23); //FILE NOT FOUND
    }
}

void put_verb(int n)
{
	if(checkBadRequest(n))
    {         
    	if (strncmp(reqline[1], "/login/\0", 7)==0 )
        {
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
        else if (strncmp(reqline[1], "/luces/\0", 7)==0)
        {
        	//obtiene el json
        	char* string =  get_luces(datos);

        	short numero_luz = lightPinMapper(string[26]);
        	short estado_luz =  retStateShort(string[37]);
            if(numero_luz == CODIGO_TODAS_PUERTAS)
        	{
        		writePin(lightPinMapper('1') ,estado_luz ); 
        		writePin(lightPinMapper('2') ,estado_luz ); 
        		writePin(lightPinMapper('3') ,estado_luz ); 
        		writePin(lightPinMapper('4') ,estado_luz ); 
        		writePin(lightPinMapper('5') ,estado_luz ); 
        	}
        	else
        	{
        		//escribe en el bombillo que necesite, el estado (prendido o apagado)
        		writePin(numero_luz ,estado_luz );
        	}
           	send(clients[n], "HTTP/1.0 200 OK\nAccess-Control-Allow-Origin:http://localhost:8383\nAccess-Control-Allow-Headers:Content-Type\nAccess-Control-Allow-Methods:GET,PUT,POST,OPTIONS\ncharset=UTF-8\n\n", 173, 0);
        } 
                 


        else    write(clients[n], "HTTP/1.0 404 Not Found\n", 23); //FILE NOT FOUND
    }
}





void get_verb(int n)
{

	if(checkBadRequest(n))
    {         
        if ( strncmp(reqline[1], "/doors/\0", 7)==0)
        {
            send(clients[n], SUCCESS_HEADER , strlen(SUCCESS_HEADER), 0);
             
            short x ;
            for(x=0; x< 4 ;x++) 
            {
             	Puertas[x] =  readPin(doorPinMapper(x+1));
             	printf("%d shrt:\n",Puertas[x]);
             }
             char jsonDoors[1000] = "";

             strcat(jsonDoors , "[");     
             strcat(jsonDoors ,"{\"numero\":1");
             strcat(jsonDoors , ",\"estado\":");
             strcat(jsonDoors , retState(Puertas[0])); 
             strcat(jsonDoors , "},");
             strcat(jsonDoors ,"{\"numero\":2"); 
             strcat(jsonDoors , ",\"estado\":");
             strcat(jsonDoors , retState(Puertas[1])); 
             strcat(jsonDoors , "},");
             strcat(jsonDoors ,"{\"numero\":3"); 
             strcat(jsonDoors , ",\"estado\":");
             strcat(jsonDoors , retState(Puertas[2])); 
             strcat(jsonDoors , "},");
             strcat(jsonDoors ,"{\"numero\":4"); 
             strcat(jsonDoors , ",\"estado\":");
             strcat(jsonDoors , retState(Puertas[3])); 
             strcat(jsonDoors , "}");
             strcat(jsonDoors ,"]"); 
             
           
             write (clients[n], jsonDoors, strlen(jsonDoors));
        	 
        }

        if ( strncmp(reqline[1], "/imagen/\0", 8)==0)
        {
        	strcpy(path, ROOT);
            strcpy(&path[strlen(ROOT)], "/patito.jpg");
            printf("file: %s\n", path);

            if ( (fd=open(path, O_RDONLY))!=-1 )    //FILE FOUND
            {
                
                send(clients[n], HEADER_IMG , strlen(HEADER_IMG), 0);    
                while ( (bytes_read=read(fd, data_to_send, BYTES))>0 )
                    write (clients[n], data_to_send, bytes_read);

            }
            else    write(clients[n], "HTTP/1.0 404 Not Found\n", 23); //FILE NOT FOUND 
        }
        
        else    write(clients[n], "HTTP/1.0 404 Not Found\n", 23); //FILE NOT FOUND
    }
}

void post_verb(int n)
{
	if(checkBadRequest(n))
    {   
        	if ( strncmp(reqline[1], "/\0", 2)==0 )
            	reqline[1] = "/index.html";       
            if ( strncmp(reqline[1], "/users/\0", 7)==0 )
                reqline[1] = "/user.json";       
            strcpy(path, ROOT);
            strcpy(&path[strlen(ROOT)], reqline[1]);
            printf("file: %s\n", path);

            if ( (fd=open(path, O_RDONLY))!=-1 )    //FILE FOUND
            {
                guarda_Archivo(datos,path);
                send(clients[n], SUCCESS_HEADER , strlen(SUCCESS_HEADER), 0);    
                    while ( (bytes_read=read(fd, data_to_send, BYTES))>0 )
                        write (clients[n], data_to_send, bytes_read);

            }
            else    write(clients[n], "HTTP/1.0 404 Not Found\n", 23); //FILE NOT FOUND
    }
}


bool checkBadRequest(int n)

{
	reqline[1] = strtok (NULL, " \t");
    reqline[2] = strtok (NULL, " \t\n");
    if ( strncmp( reqline[2], "HTTP/1.0", 8)!=0 && strncmp( reqline[2], "HTTP/1.1", 8)!=0 )
    {
        write(clients[n], BAD_REQUEST_HEADER, strlen(BAD_REQUEST_HEADER));
        return false;
    }
    return true;
}
