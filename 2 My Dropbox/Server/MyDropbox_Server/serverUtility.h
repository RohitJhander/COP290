#ifndef SERVER_UTILITY_H
#define SERVER_UTILITY_H

#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSql>

#include "structures.h"
#include "MyDefines.h"
#include "user.h"
#include <string>
using namespace std;

void error(const char*);
string getOutputFileName(fileData*);
void writeToFile(const char*, fileData*);
void printData(fileData*);
fileData* copyMessageToBuffer(serverToClientMessage);
User readLoginDetails(fileData*);
User readRegisterDetails(fileData*);
void connectDatabase(string path);
int getInt(fileData*);
int getInt(char*);
string getString(char*,int);

#endif
