#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
    private:
        string username;
        string password;
        string email;

    public:
        User();

        string getUsername();
        void setUsername(string);

        string getEmail();
        void setEmail(string);

        string getPassword();
        void setPassword(string);
};

#endif //USER_H
