#ifndef LOGDATA_H
#define LOGDATA_H
#include "File.h"
#include <QDateTime>

void connectToLogdata(string);
void createLogFilesTable(string);
int  getLogFilesCount(string);
void removeFileFromLogTable(string,string);
File* removeFirstEntryFromTable(string);
bool checkFileInLogTable(File*,string);
void insertFileIntoLogTable(File*,string);
void insertUserIntoTable(string);
bool checkUserInUserTable(string);

//QDateTime and QString interconversion
QString convertQDateTimeToQString(QDateTime);
QDateTime convertStringToQDateTime(string);


#endif // LOGDATA_H
