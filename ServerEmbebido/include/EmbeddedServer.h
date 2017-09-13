#ifndef _EMBEDDEDSERVER_H
#define _EMBEDDEDSERVER_H


void startServer(char *,int *);
void respond(int);
void receive(int);
void error(char*);

#endif
