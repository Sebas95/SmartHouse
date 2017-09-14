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


char mesg[99999], datos[99999], *reqline[3], data_to_send[BYTES], path[99999];
int rcvd, fd, bytes_read;
char Puertas[10];
char luces[10] ;  


//start server
void startServer(char *port, int *listenfd)
{
	init(); //init pins
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
        if (strncmp(reqline[1], "/interfaz/\0", 2)==0)
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
short retStateShort(char c)
{
	if(c=='0')
		return 0;
	else 
		return 1;
}
void put_verb(int n)

{
	if(checkBadRequest(n))
    {                          
        if ( strncmp(reqline[1], "/luces/\0", 2)==0 )
        {
        	char* string =  get_luces(datos);
        	printf("\ndatos: %c\n %c\n", string[26], string[37]);

        	
        	writePin(2,retStateShort(string[37]));
        	writePin(3,retStateShort(string[37]));
        	writePin(4,retStateShort(string[37]));

           	send(clients[n], "HTTP/1.0 200 OK\nAccess-Control-Allow-Origin:http://localhost:8383\nAccess-Control-Allow-Headers:Content-Type\nAccess-Control-Allow-Methods:GET,PUT,POST,OPTIONS\ncharset=UTF-8\n\n", 173, 0);
        }         
        else    write(clients[n], "HTTP/1.0 404 Not Found\n", 23); //FILE NOT FOUND
    }
}

const char* retState(char c)
{
	if(c=='0')
		return "1";
	else
		return "0";
}



void get_verb(int n)
{

	if(checkBadRequest(n))
    {         
        if ( strncmp(reqline[1], "/doors/\0", 2)==0 )
        {
             send(clients[n], SUCCESS_HEADER , strlen(SUCCESS_HEADER), 0);
             printf("%s\n","holis");
             char jsonDoors[1000] = "";

             strcat(jsonDoors , "[");     
             strcat(jsonDoors ,"{\"numero\":");
             strcat(jsonDoors , retState(Puertas[0])); 
             strcat(jsonDoors , ",\"estado\":");
             strcat(jsonDoors , retState(Puertas[0])); 
             strcat(jsonDoors , "},");
             strcat(jsonDoors ,"{\"numero\":");
             strcat(jsonDoors , retState(Puertas[0])); 
             strcat(jsonDoors , ",\"estado\":");
             strcat(jsonDoors , retState(Puertas[0])); 
             strcat(jsonDoors , "},");
             strcat(jsonDoors ,"{\"numero\":");
             strcat(jsonDoors , retState(Puertas[0])); 
             strcat(jsonDoors , ",\"estado\":");
             strcat(jsonDoors , retState(Puertas[0])); 
             strcat(jsonDoors , "},");
             strcat(jsonDoors ,"{\"numero\":");
             strcat(jsonDoors , retState(Puertas[0])); 
             strcat(jsonDoors , ",\"estado\":");
             strcat(jsonDoors , retState(Puertas[0])); 
             strcat(jsonDoors , "},");
             strcat(jsonDoors ,"{\"numero\":");
             strcat(jsonDoors , retState(Puertas[0])); 
             strcat(jsonDoors , ",\"estado\":");
             strcat(jsonDoors , retState(Puertas[0])); 
             strcat(jsonDoors , "}");
             strcat(jsonDoors ,"]"); 
             printf("%s\n",jsonDoors);
           
             write (clients[n], jsonDoors, strlen(jsonDoors));
        	 
        }
        else if ( strncmp(reqline[1], "/login/\0", 2)==0 )
        {
            reqline[1] = "/user.json";       
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
	                send(clients[n], SUCCESS_HEADER , strlen(SUCCESS_HEADER), 0);
	            }
	            else
	            {
	                printf("La validacion es incorrecta\n");
	                send(clients[n], SUCCESS_HEADER , strlen(SUCCESS_HEADER), 0);
	            }
	            while ( (bytes_read=read(fd, data_to_send, BYTES))>0 )
	                write (clients[n], data_to_send, bytes_read);
	        }
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
            if ( strncmp(reqline[1], "/users/\0", 2)==0 )
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
