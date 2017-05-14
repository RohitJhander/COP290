#include "clientUtility.h"
#include "MyDefines.h"
#include "logData.h"

#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

void error(const char *msg){
    perror(msg);
    exit(1);
}

//copy clientToServerMessage into fileData
fileData* copyMessageToBuffer(clientToServerMessage msg){
    fileData *toReturn = new fileData;
    toReturn->size = sizeof(msg);
    toReturn->buffer = new char[toReturn->size];	//	create new buffer
    memcpy(toReturn->buffer,&msg,sizeof(msg));
    return toReturn;
}

fileData* writeLoginDetails(string username, string password){
    fileData *toReturn = new fileData;

    int username_length = username.size();
    int password_length = password.size();

    toReturn->size = username_length + password_length + 12;

    toReturn->buffer = new char[toReturn->size];

    memcpy(toReturn->buffer,&toReturn->size,4);

    memcpy(toReturn->buffer+4,&username_length,4);
    memcpy(toReturn->buffer+8,username.c_str(),username_length);

    memcpy(toReturn->buffer+8+username_length,&password_length,4);
    memcpy(toReturn->buffer+8+username_length+4,password.c_str(),password_length);

    //printData(toReturn);
    return toReturn;
}

fileData* writeRegisterDetails(string username, string password, string email){
    fileData *toReturn = new fileData;

    int username_length = username.size();
    int password_length = password.size();
    int email_length = email.size();

    toReturn->size = username_length + password_length + email_length + 16;

    toReturn->buffer = new char[toReturn->size];

    memcpy(toReturn->buffer,&toReturn->size,4);

    memcpy(toReturn->buffer+4,&username_length,4);
    memcpy(toReturn->buffer+8,username.c_str(),username_length);

    memcpy(toReturn->buffer+8+username_length,&password_length,4);
    memcpy(toReturn->buffer+8+username_length+4,password.c_str(),password_length);

    memcpy(toReturn->buffer+8+username_length+4+password_length,&email_length,4);
    memcpy(toReturn->buffer+8+username_length+4+password_length+4,email.c_str(),email_length);

    //printData(toReturn);
    return toReturn;
}

fileData* getFileDetails(File* file){
    cout<<"----getFileDetails()----"<<endl;
    string path = file->getPath();
    int path_size = path.size();
    string time_str = convertQDateTimeToQString(file->getTime()).toStdString();
    int time_size = time_str.size();

    cout<<"path_size: "<<path_size<<endl;
    cout<<"path: "<<path<<endl;
    cout<<"time_size: "<<time_size<<endl;
    cout<<"time_str: "<<time_str<<endl;

    fileData* data = new fileData;
    int totalSize = 12 + path_size + time_size;

    data->buffer = new char[totalSize];
    data->size = totalSize;

    memcpy(data->buffer,&totalSize,4);
    memcpy(data->buffer+4,&path_size,4);
    memcpy(data->buffer+8,path.c_str(),path_size);
    memcpy(data->buffer+8+path_size,&time_size,4);
    memcpy(data->buffer+8+path_size+4,time_str.c_str(),time_size);

    cout<<"----Exit getFileDetails()----"<<endl;
    return data;
}

fileData* writeSharingDetails(string filepath, string username) {
    cout<<"---------writing sharing details---------";

    fileData *toReturn = new fileData;

    int username_length = username.size();
    int filepath_length = filepath.size();

    toReturn->size = username_length + filepath_length + 12;

    toReturn->buffer = new char[toReturn->size];

    memcpy(toReturn->buffer,&toReturn->size,4);

    memcpy(toReturn->buffer+4,&username_length,4);
    memcpy(toReturn->buffer+8,username.c_str(),username_length);

    memcpy(toReturn->buffer+8+username_length,&filepath_length,4);
    memcpy(toReturn->buffer+8+username_length+4,filepath.c_str(),filepath_length);

    //printData(toReturn);
    return toReturn;
}
