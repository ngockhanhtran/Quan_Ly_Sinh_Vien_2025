#include "AccountManager.h"
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

void AccountManager ::loadFromFile(const string& filename){
    accounts.clear();
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Khong the mo file " << filename << endl;
        return;
    }
    
    string line;
    getline(file, line); // bỏ qua dòng đầu trong csv
    while(getline(file, line)){
        stringstream ss(line);
        string username, password, type, linkedpersonID;
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, type, ',');
        getline(ss, linkedpersonID, ',');

        if(username.empty()) continue;

        AccountType type = Account :: stringToAccountType(type);
        accounts.emplace_back(username, password, type, linkedpersonID);
    }
    file.close();
}

void AccountManager ::saveToFile(const string& filename){
    ofstream file(filename);
    if(!file.is_open()){    
        cerr << "Khong the ghi file" << filename << endl;
    }

    file << "username, password, type, linkedpersonID\n";
    for(const auto& acc: accounts){
        file << acc.getUsername() << "," << acc.getPassword() << "," 
            << Account ::AccounttoString(acc.getType()) << ","
            <<acc.getID() << "\n";
    }
    file.close();
}

Account* AccountManager ::login(const string& username, const string& password){
    for(auto& acc:accounts){
        if(acc.authenticate(username, password)){
            return &acc;
        }
    }
    return nullptr;
}

bool AccountManager ::registerStudent(const string& studentID){
    for(const auto& acc : accounts){
        if(acc.getUsername() == studentID){
            return false;
        }
        accounts.emplace_back(studentID, "12345@", AccountType::STUDENT, studentID);
        return true;
    }
}

bool AccountManager ::changePassword(Account& account, const string& oldPass, const string& newPass){
    return account.changePass(oldPass, newPass);
}
// reset password
bool AccountManager ::resetPassword(const string& studentID, const string& newPass = "12345@"){
    for (auto& acc : accounts){
        if (acc.getUsername() == studentID && acc.getType() == AccountType::STUDENT){
            acc.setPassword(newPass);
            return true;
        }
    }
    return false;
}

void AccountManager ::showMenu(){
    const string filename = "accounts.csv";
    loadFromFile(filename);

    while(true){
        cout << "\n====== MENU TAI KHOAN ======\n";
        cout << "1. Dang Nhap\n";
        cout << "2. Dang ky\n";
        cout << "3. Thoat\n";
        cout << "============================\n";
        cout << "Chon: ";
        int choice; cin >> choice;
        cin.ignore();
        
    }
}