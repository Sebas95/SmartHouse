#ifndef _EMBEDDEDSERVER_H
#define _EMBEDDEDSERVER_H


#include <stdbool.h>


#define SUCCESS_HEADER "HTTP/1.0 200 OK\nAccess-Control-Allow-Origin:http://localhost:8383\nAccess-Control-Allow-Headers:Content-Type\nAccess-Control-Allow-Methods:GET,PUT,POST,OPTIONS\nContent-Type:application/json;charset=UTF-8\n\n"
#define HEADER_IMG "HTTP/1.0 200 OK\nAccess-Control-Allow-Origin:http://localhost:8383\nAccess-Control-Allow-Headers:Content-Type\nAccess-Control-Allow-Methods:GET,PUT,POST,OPTIONS\nContent-Type:image/jpeg\n\n"
#define CONNMAX 1000
#define BYTES 1024
#define BAD_REQUEST_HEADER "HTTP/1.0 400 Bad Request\n"
#define NOT_FOUND_HEADER "HTTP/1.0 404 Not Found\n"
#define INTERNAL_SERVER_ERROR_HEADER "HTTP/1.0 500 NO\nAccess-Control-Allow-Origin:http://localhost:8383\nAccess-Control-Allow-Headers:Content-Type\nAccess-Control-Allow-Methods:GET,PUT,POST,OPTIONS\nContent-Type:application/json;charset=UTF-8\n\n"
#define CODIGO_TODAS_LUCES 6
#define CANTIDAD_PUERTAS 4


char *ROOT;
int listenfd; 
int clients[CONNMAX];

char mesg[99999]; 
char datos[99999]; 
char *reqline[3]; 
char data_to_send[BYTES]; 
char path[99999];
int rcvd, fd, bytes_read;
short Puertas[CANTIDAD_PUERTAS];


void startServer(char *port, int *listenfd);
void sendNotFound(int n);
void respond(int n,char* ROOT);
void options_verb(int n);
void put_verb(int n);
void put_user(int n);
void put_lights(int n);
void get_photo(int n);
void get_doors(int n);
void get_verb(int n);
void post_verb(int n);
bool checkBadRequest(int n);
void error(char*);

#endif
