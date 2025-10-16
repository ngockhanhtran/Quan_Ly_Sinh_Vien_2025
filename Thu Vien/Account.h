#pragma once
#include <string>
using namespace std;

enum class AccountType{
    STUDENT,
    MANAGER,
    ADMIN
};

class Account{
private: 
    string username;
    string password;
    AccountType type;
    string linkedpersonID;
public:
    Account(){}
    Account(const string& username, const string& password, AccountType type, const string& linkedpersonID){}

    // getter
    string getUsername()const {}
    string getPassword() const {}
    AccountType getType() const{}
    string getID () const {}

    // setter
    void setPassword(const string& newPass){}

    // logic
    bool authenticate(const string& inputUsername, const string& inputPassword){}
    bool changePass(const string& oldPass, const string& newPass){}

    // static
    static string AccounttoString(AccountType type){}
    static AccountType stringToAccountType(const string& str){}
};