#include "commonUtility.h"
#include <fstream>
#include <iostream>
using namespace std;

int getInt(fileData* data){
    if(data->size != 4){
        cout << "Error: size of data not equal to 4 bytes" << endl;
        exit(0);
    }
    return getInt(data->buffer);
}

int getInt(char* buffer){
    if(buffer == NULL){
        cout << "Error: buffer is Null" << endl;
        exit(0);
    }
    int a;
    memcpy(&a,buffer,4);
    return a;
}

string getString(char* buffer,int size){
    string a;
    a.assign(buffer,buffer+size);
    return a;
}

void printData(fileData* data){
    for(int i=0 ; i<data->size ; i++){
        cout<<data->buffer[i];
    }
    cout<<endl;
}

fileData* readFromFile(const char* fileName){
    unsigned long long fileSize = getFileSize(fileName);
    ifstream fin(fileName,ios::in | ios::binary | ios::ate);
    if(!fin.is_open()){
        cout<<"Error: can not open "<<fileName<<"\n";
        exit(0);
    }

    int totalSize = 4 + fileSize;

    fileData *toReturn = new fileData;
    toReturn->size = totalSize;

    if(toReturn->size > MAX_FILE_SIZE){
        cout<<"File too big to send: Maximum size of file = "<<MAX_FILE_SIZE<<endl;
        exit(0);
    }

    toReturn->buffer = new char[totalSize];	//	create new buffer
    memcpy(toReturn->buffer,&totalSize,4);
    fin.seekg(0,ios::beg);							//	move to beginning of file
    fin.read(toReturn->buffer+4,fileSize);
    fin.close();
    return toReturn;
}

unsigned long long getFileSize(const char* fileName){
    ifstream fin(fileName,ios::in | ios::binary | ios::ate);
    if(!fin.is_open()){
        cout<<"Error: can not open "<<fileName<<"\n";
        exit(0);
    }
    unsigned long long size = fin.tellg();
    fin.close();
    return size;
}

void writeToFile(const char* filename, fileData* data){
    fstream fout(filename, ios::out | ios::binary | ios::trunc);
    fout.close();
    fout.open(filename, ios::out | ios::binary | ios::trunc);
    if(!fout.is_open()){
        cout<<"Error: can not open "<<filename<<"\n";
        exit(0);
    }
    fout.write(data->buffer,data->size);
}


File* createFileObject(fileData* data){
    cout<<"----------createFileObject()--------"<<endl;
    File* file = new File();

    int path_size = getInt(data->buffer);
    file->setPath(getString(data->buffer+4,path_size));

    cout<<"path_size: "<<path_size<<endl;

    data->buffer += (4 + path_size);

    int time_size = getInt(data->buffer);
    string time_str = getString(data->buffer+4,time_size);
    cout<<"time_str: "<<time_str<<endl;

    QDateTime datetime = convertStringToQDateTime(time_str);
    cout<<"time_str: "<<convertQDateTimeToQString(datetime).toStdString()<<endl;

    file->setTime(datetime);
    cout<<"----------Exit createFileObject()--------"<<endl;
    return file;
}

QString convertQDateTimeToQString(QDateTime qdt){
    return qdt.toString(FORMAT);
}

QDateTime convertStringToQDateTime(string time_str){
    //format = "yyyy-MM-dd hh:mm:ss"
    QDateTime datetime;

    QDate date;
    date.setDate(std::stoi(time_str.substr(0,4)),std::stoi(time_str.substr(5,7)),std::stoi(time_str.substr(8,10)));
    datetime.setDate(date);

    QTime time;
    time.setHMS(std::stoi(time_str.substr(11,13)),std::stoi(time_str.substr(14,16)),std::stoi(time_str.substr(17,19)));
    datetime.setTime(time);

    return datetime;
}
