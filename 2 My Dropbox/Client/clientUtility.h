/**
 * @file
 * This file contains read/write function in different formats for client class
 *
 */

#ifndef CLIENT_UTILITY_H
#define CLIENT_UTILITY_H

#include <string>
#include "structures.h"
#include "MyDefines.h"
#include "File.h"

using namespace std;

void error(const char*);

fileData* copyMessageToBuffer(clientToServerMessage);
fileData* writeLoginDetails(string, string);
fileData* writeRegisterDetails(string, string, string);
fileData* writeSharingDetails(string, string);

//file details functions
fileData* getFileDetails(File*);

#endif
