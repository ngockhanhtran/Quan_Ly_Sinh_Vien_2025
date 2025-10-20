#include "Account.h"
#include <stdexcept>
using namespace std;

Account :: Account(): username(""),password(""),type(AccountType::STUDENT), linkedpersonID("") {}
Account :: Account(const string& username, const string& password, AccountType type, const string& linkedpersonID, const string& phoneNumber)
        : username(username), password(password), type(type), linkedpersonID(linkedpersonID), phoneNumber(phoneNumber){}
string Account :: getUsername() const {return username;}
string Account :: getPassword() const {return password;}
AccountType Account :: getType() const{return type;}
string Account :: getID() const {return linkedpersonID;}
string Account :: getPhoneNumber() const{return phoneNumber;}

void Account :: setPassword(const string& newPass){
    password = newPass;
}

void Account :: setPhoneNumber(const string& phone){
    phoneNumber = phone;
}

bool Account :: authenticate(const string& inputUsername, const string& inputPassword){
    return username == inputUsername && password == inputPassword;
}

bool Account ::changePass(const string& oldPass, const string& newPass){
    if(password == oldPass){
        password = newPass;
        return true;
    }
    return false;
}

string Account :: AccounttoString(AccountType type){
    switch(type){
        case AccountType::STUDENT: return "STUDENT";
        case AccountType::ADMIN: return "ADMIN";
        case AccountType::MANAGER: return "MANAGER";
        default: return "UNKNOWN";
    }
}

AccountType Account :: stringToAccountType(const string& str){
    if(str == "STUDENT") return AccountType::STUDENT;
    if(str == "ADMIN") return AccountType::ADMIN;
    if(str == "MANAGER") return AccountType::MANAGER;
    return AccountType::STUDENT;
}