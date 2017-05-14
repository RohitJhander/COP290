#ifndef SERVER_H
#define SERVER_H

#include "MyDefines.h"
#include "structures.h"
#include "client.h"

void error(const char*);
int createNewConnection(char*);
int acceptConnection(int);
void handleClient(Client*);

#endif
