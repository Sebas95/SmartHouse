#ifndef _EMBEDDEDSERVER_H
#define _EMBEDDEDSERVER_H

#define CONNMAX 1000
#define CONNMAX 1000
#define BYTES 1024

char *ROOT;
int listenfd; 
int clients[CONNMAX];

void startServer(char *,int *);
void respond(int,char*);
void receive(int);
void error(char*);

#endif
