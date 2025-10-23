#pragma once
#include<iostream>
#include<string>
using namespace std;

class Student{
protected:
    string id;
    string name;
    string gender;
    int birthYear;

    // thông tin liên hệ
    string parentName;
    string parentPhone;
    string email;
public:
    Student();
    Student(string id, string name, string gender, int birthYear,
            string parentName = "", string parentPhone = "", string email = "");

    // nhập - xuất thông tin
    virtual void input();
    virtual void display() const;

    // hàm ảo thuần túy - mỗi khoa tự định nghĩa cách tính GPA
    virtual double calcGPA() const = 0;
    virtual string getFaculty() const = 0;

    // dùng cho StudentManager khi đọc file csv
    void setBasein4(string id, string name, string gender, int birthYear,
                     string parentName = "", string parentPhone = "", string email = "");
    string getID() const { return id; }
    string getName() const { return name; }
    string getParentName() const { return parentName; }
    string getParentPhone() const { return parentPhone; }
    string getEmail() const { return email; } // email sinh viên
};