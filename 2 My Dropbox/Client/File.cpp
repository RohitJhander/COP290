#include "File.h"

File::File(){
    this->path = "";
    this->time_format = "yyyy-MM-dd hh:mm:ss";
}

string File::getPath(){
    return this->path;
}

void File::setPath(string p){
    this->path = p;
}

string File::getFileName(){
   return this->fileName;
}

void File::setFileName(string filename){
    this->fileName = filename;
}

int File::getSize(){
    return this->size;
}

void File::setSize(int s){
    this->size = s;
}

QDateTime File::getTime(){
    return this->time;
}

void File::setTime(QDateTime t){
    this->time=t;
}

QString File::getTimeFormat(){
    return this->time_format;
}

void File::setTimeFormat(QString format){
    this->time_format = format;
}

fileData* File::getFileContent(){
    return this->fileContent;
}

void File::setFileContent(fileData* data){
    this->fileContent = data;
}
