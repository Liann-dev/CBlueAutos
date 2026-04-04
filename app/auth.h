#ifndef AUTH_H
#define AUTH_H

#include <string>

struct User {
    int id;
    std::string username;
    std::string password;
    std::string role;
};

void registerUser();
bool loginUser(User &userTerdaftar);
std::string inputPassword(); // Fungsi baru untuk sensor

#endif