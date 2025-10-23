#include "AccountManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// =================== ĐỌC FILE ===================
void AccountManager::loadFromFile(const string& filename) {
    accounts.clear();
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << " Khong the mo file " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Bỏ qua dòng tiêu đề
    while (getline(file, line)) {
        stringstream ss(line);
        string username, password, typeStr, linkedID, phone;
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, typeStr, ',');
        getline(ss, linkedID, ',');
        getline(ss, phone, ',');

        AccountType type = Account::stringToAccountType(typeStr);
        accounts.emplace_back(username, password, type, linkedID, phone);
    }
    file.close();
}

// =================== GHI FILE ===================
void AccountManager::saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << " Khong the ghi file " << filename << endl;
        return;
    }

    file << "username,password,type,linkedPersonID,phoneNumber\n";
    for (const auto& acc : accounts) {
        file << acc.getUsername() << ","
             << acc.getPassword() << ","
             << Account::AccounttoString(acc.getType()) << ","
             << acc.getID() << ","
             << acc.getPhoneNumber() << "\n";
    }
    file.close();
}

// =================== ĐĂNG NHẬP ===================
Account* AccountManager::login(const string& username, const string& password) {
    for (auto& acc : accounts) {
        if (acc.authenticate(username, password)) {
            return &acc;
        }
    }
    return nullptr;
}

// =================== ĐĂNG KÝ SINH VIÊN MỚI ===================
bool AccountManager::registerStudent(const string& studentID, const string& phone) {
    for (const auto& acc : accounts) {
        if (acc.getUsername() == studentID)
            return false; // trùng tài khoản
    }
    accounts.emplace_back(studentID, "12345@", AccountType::STUDENT, studentID, phone);
    return true;
}

// =================== ĐỔI MẬT KHẨU ===================
bool AccountManager::changePassword(Account& account, const string& oldPass, const string& newPass) {
    return account.changePass(oldPass, newPass);
}

// =================== RESET MẬT KHẨU (ADMIN) ===================
bool AccountManager::resetPassword(const string& studentID, const string& newPass) {
    for (auto& acc : accounts) {
        if (acc.getUsername() == studentID) {
            acc.setPassword(newPass);
            saveToFile("accounts.csv");
            return true;
        }
    }
    return false;
}

// =================== QUÊN MẬT KHẨU ===================
void AccountManager::forgotPassword() {
    string username;
    cout << "\n===== QUEN MAT KHAU =====\n";
    cout << "Nhap username: ";
    getline(cin, username);

    for (auto& acc : accounts) {
        if (acc.getUsername() == username) {
            cout << "Vui long lien he admin qua email: abcd@edu.vn hoac hotline: 0123456JQK de nhan ma khoi phuc....\n";
            cout << "Hoac soan cu phap RESET PASS gui 9000 de cap lai mat khau\n";
            cout << "Nhap ma khoi phuc: ";
            string code;
            getline(cin, code);

            if (code == recoveryCode) {
                cout << "Nhap mat khau moi: ";
                string newPass;
                getline(cin, newPass);
                acc.setPassword(newPass);
                cout << "Dat lai mat khau thanh cong!\n";
                saveToFile("accounts.csv");
            } else {
                cout << "Ma khoi phuc khong dung!\n";
            }
            return;
        }
    }
    cout << "ERROR: Khong tim thay tai khoan!\n";
}

// =================== MENU CHÍNH ===================
void AccountManager::showMenu() {
    const string filename = "accounts.csv";
    loadFromFile(filename);

    while (true) {
        cout << "\n========== MENU TAI KHOAN ==========\n";
        cout << "1. Dang nhap\n";
        cout << "2. Dang ky (sinh vien moi)\n";
        cout << "3. Quen mat khau\n";
        cout << "4. Thoat\n";
        cout << "===================================\n";
        cout << "Chon: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string user, pass;
            cin.ignore();
            cout << "Nhap username: ";
            getline(cin, user);
            cout << "Nhap password: ";
            getline(cin, pass);

            Account* acc = login(user, pass);
            if (acc) {
                cout << "Dang nhap thanh cong voi quyen: "
                     << Account::AccounttoString(acc->getType()) << endl;

                if (acc->getType() == AccountType::STUDENT) {
                    cout << "Xin chao sinh vien " << acc->getUsername() << endl;
                    cout << "Ban co muon doi mat khau khong? (y/n): ";
                    char c;
                    cin >> c;
                    if (c == 'y' || c == 'Y') {
                        cin.ignore();
                        string oldP, newP;
                        cout << "Nhap mat khau cu: ";
                        getline(cin, oldP);
                        cout << "Nhap mat khau moi: ";
                        getline(cin, newP);
                        if (changePassword(*acc, oldP, newP)) {
                            cout << "Doi mat khau thanh cong!\n";
                        } else {
                            cout << "Mat khau cu khong dung!\n";
                        }
                    }
                } else if (acc->getType() == AccountType::ADMIN) {
                    cout << "Xin chao ADMIN!\n";
                    cout << "Nhap ma sinh vien can reset mat khau: ";
                    string id;
                    cin >> id;
                    if (resetPassword(id)) {
                        cout << "Reset mat khau ve mac dinh (12345@) thanh cong!\n";
                    } else {
                        cout << "Khong tim thay sinh vien!\n";
                    }
                } else {
                    cout << "Dang nhap voi quyen quan ly (Manager)...\n";
                }

                saveToFile(filename);
            } else {
                cout << "ERROR: Dang nhap that bai!\n";
            }
        }
        else if (choice == 2) {
            string id, phone;
            cin.ignore();
            cout << "Nhap ma sinh vien moi: ";
            getline(cin, id);
            cout << "Nhap so dien thoai: ";
            getline(cin, phone);

            if (registerStudent(id, phone)) {
                cout << "Dang ky thanh cong! Mat khau mac dinh: 12345@\n";
                saveToFile(filename);
            } else {
                cout << "ERROR: Ma sinh vien da ton tai!\n";
            }
        }
        else if (choice == 3) {
            forgotPassword();
        }
        else if (choice == 4) {
            cout << " Tam biet!\n";
            break;
        }
        else {
            cout << "ERROR: Lua chon khong hop le!\n";
        }
    }
}