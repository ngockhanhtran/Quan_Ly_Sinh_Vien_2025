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
}