#ifndef COMMONUTILITY_H
#define COMMONUTILITY_H

#include "structures.h"
#include "File.h"

#include <QString>
#include <QDateTime>
#include <string>
using namespace std;

int getInt(fileData*);
int getInt(char*);
string getString(char*,int);

void printData(fileData*);

fileData* readFromFile(const char*);
unsigned long long getFileSize(const char*);
void writeToFile(const char*, fileData*);

File* createFileObject(fileData*);

QString convertQDateTimeToQString(QDateTime);
QDateTime convertStringToQDateTime(string);

#endif // COMMONUTILITY_H
