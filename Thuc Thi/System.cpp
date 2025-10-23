#include "System.h"
#include <iostream>
#include <limits>
using namespace std;

SystemManager::SystemManager() {
    loadAll();
}

// =======================
//  LOAD & SAVE DỮ LIỆU
// =======================
void SystemManager::loadAll() {
    accountManager.loadFromFile(accountsFile);
    studentManager.loadFromFile(studentsFile);
}

void SystemManager::saveAll() {
    accountManager.saveToFile(accountsFile);
    studentManager.saveToFile(studentsFile);
}

// =======================
//  MENU CHÍNH
// =======================
void SystemManager::showMainMenu() {
    while (true) {
        cout << "\n=====================================\n";
        cout << "      HE THONG QUAN LY SINH VIEN\n";
        cout << "=====================================\n";
        cout << "1. Dang nhap\n";
        cout << "2. Dang ky (sinh vien moi)\n";
        cout << "3. Quen mat khau\n";
        cout << "0. Thoat\n";
        cout << "-------------------------------------\n";
        cout << "Chon: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Lua chon khong hop le.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 0:
                cout << "Thoat chuong trinh. Tam biet!\n";
                saveAll();
                return;

            case 1:
                handleLogin();
                break;

            case 2: {
                string studentID, phone;
                cout << "Nhap ma sinh vien moi: ";
                getline(cin, studentID);
                cout << "Nhap so dien thoai: ";
                getline(cin, phone);

                if (accountManager.registerStudent(studentID, phone)) {
                    accountManager.saveToFile(accountsFile);
                    cout << "Dang ky thanh cong! Mat khau mac dinh: 12345@\n";
                } else {
                    cout << "ERROR: Ma sinh vien da ton tai!\n";
                }
                break;
            }

            case 3:
                accountManager.forgotPassword();
                accountManager.saveToFile(accountsFile);
                break;

            default:
                cout << "Lua chon khong hop le.\n";
                break;
        }
    }
}

// =======================
//  ĐĂNG NHẬP
// =======================
void SystemManager::handleLogin() {
    string username, password;
    cout << "\n===== DANG NHAP =====\n";
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);

    accountManager.loadFromFile(accountsFile);
    studentManager.loadFromFile(studentsFile); // đảm bảo dữ liệu mới nhất

    Account* user = accountManager.login(username, password);
    if (!user) {
        cout << "ERROR: Sai tai khoan hoac mat khau.\n";
        return;
    }

    cout << "Dang nhap thanh cong voi quyen: "
         << Account::AccounttoString(user->getType()) << endl;

    switch (user->getType()) {
        case AccountType::MANAGER:
            studentManager.managerMenu();
            studentManager.saveToFile(studentsFile);
            break;

        case AccountType::ADMIN:

            studentManager.adminMenu(accountManager);
            studentManager.saveToFile(studentsFile);
            accountManager.saveToFile(accountsFile);
            break;

        case AccountType::STUDENT:
            cout << "Xin chao sinh vien " << user->getUsername() << "!\n";
            studentManager.studentMenu(user->getID());
            break;

        default:
            cout << "ERROR: Quyen khong hop le.\n";
    }
}
