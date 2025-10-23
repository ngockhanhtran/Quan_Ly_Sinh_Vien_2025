#pragma once
#include "Account.h"
#include <vector>
#include <string>
using namespace std;

class AccountManager {
private:
    vector<Account> accounts;
    const string recoveryCode = "CNTT1-K65-UTC"; // mã khôi phục admin cung cấp

public:
    void loadFromFile(const string& filename);
    void saveToFile(const string& filename);

    Account* login(const string& username, const string& password);
    bool registerStudent(const string& studentID, const string& phone);
    bool changePassword(Account& account, const string& oldPass, const string& newPass);
    bool resetPassword(const string& studentID, const string& newPass = "12345@");
    void forgotPassword(); // xử lý quên mật khẩu (dùng mã khôi phục)

    vector<Account>& getAccounts() { return accounts; }

    void showMenu();
};