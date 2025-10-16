#pragma once
#include "Account.h"
#include <vector>
using namespace std;

class AccountManager{
private:
    vector<Account> accounts;

public:
    void loadFromFile(const string& filename);
    void saveToFile(const string& filename);

    Account* login(const string& username, const string& password);
    bool registerStudent(const string& studentID); // mặc định password
    bool changePassword(Account& account, const string& oldPass, const string& newPass);
    bool resetPassword(const std::string& studentID, const std::string& newPass = "12345@"); // only admin use

    void showMenu();
};