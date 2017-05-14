#include "user.h"
using namespace std;

User::User() {
    username = "NONAME";
    password = "nothing";
    email = "noname@noname.com";
}

string User::getUsername() {
    return this->username;
}

void User::setUsername(string username) {
    this->username = username;
}

string User::getEmail() {
    return this->email;
}

void User::setEmail(string email) {
    this->email = email;
}

string User::getPassword() {
    return password;
}

void User::setPassword(string password) {
    this->password = password;
}
