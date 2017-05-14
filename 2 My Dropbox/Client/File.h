#ifndef FILE_H
#define FILE_H
#include "MyDefines.h"
#include "structures.h"
#include  <string>
#include <QDateTime>
using namespace std;

class File{
    private:
        string path;
        string fileName;
        fileData* fileContent;
        QDateTime time;
        QString time_format;
        int size;
    public:
        File();
        string getPath();
        void setPath(string);
        string getFileName();
        void setFileName(string);
        int getSize();
        void setSize(int);
        void setTime(QDateTime);
        QDateTime getTime();
        void setTimeFormat(QString);
        QString getTimeFormat();
        fileData* getFileContent();
        void setFileContent(fileData*);
};

#endif // FILE_H
