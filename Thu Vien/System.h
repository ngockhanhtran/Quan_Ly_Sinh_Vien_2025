#pragma once
#include "AccountManager.h"
#include "StudentManager.h"
#include <string>
using namespace std;

class SystemManager {
private:
    AccountManager accountManager;
    StudentManager studentManager;

    const string accountsFile = "accounts.csv";
    const string studentsFile = "students.csv";

public:
    SystemManager();

    void loadAll();
    void saveAll();

    void showMainMenu();  // menu chính
    void handleLogin();   // xử lý đăng nhập
};