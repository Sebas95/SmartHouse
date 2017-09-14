#ifndef _EMBEDDEDSERVER_H
#define _EMBEDDEDSERVER_H


#include <stdbool.h>


#define SUCCESS_HEADER "HTTP/1.0 200 OK\nAccess-Control-Allow-Origin:http://localhost:8383\nAccess-Control-Allow-Headers:Content-Type\nAccess-Control-Allow-Methods:GET,PUT,POST,OPTIONS\nContent-Type:application/json;charset=UTF-8\n\n"
#define CONNMAX 1000
#define BYTES 1024
#define BAD_REQUEST_HEADER "HTTP/1.0 400 Bad Request\n"

char *ROOT;
int listenfd; 
int clients[CONNMAX];

void startServer(char *,int *);
void respond(int,char*);
void receive(int);
void error(char*);
void options_verb(int n);
void put_verb(int n);
void post_verb(int n);
bool checkBadRequest(int n);
void get_verb(int n);

#endif
