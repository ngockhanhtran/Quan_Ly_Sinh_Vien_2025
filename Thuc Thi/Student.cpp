#include "Student.h"
using namespace std;

Student::Student()
    : id(""), name(""), gender(""), birthYear(0),
      parentName(""), parentPhone(""), email("") {}

Student::Student(string id, string name, string gender, int birthYear,
                 string parentName, string parentPhone, string email)
    : id(id), name(name), gender(gender), birthYear(birthYear),
      parentName(parentName), parentPhone(parentPhone), email(email) {}

void Student::input() {
    cout << "Nhap ma SV: "; getline(cin, id);
    cout << "Nhap ho ten: "; getline(cin, name);
    cout << "Nhap gioi tinh: "; getline(cin, gender);
    cout << "Nhap nam sinh: "; cin >> birthYear; cin.ignore();

    cout << "Nhap ho ten phu huynh: "; getline(cin, parentName);
    cout << "Nhap so dien thoai phu huynh: "; getline(cin, parentPhone);
    cout << "Nhap email lien he: "; getline(cin, email);
}

void Student::display() const {
    cout << "Ma SV: " << id
         << " | Ho ten: " << name
         << " | Gioi tinh: " << gender
         << " | Nam sinh: " << birthYear
         << " | Phu huynh: " << parentName
         << " | SDT PH: " << parentPhone
         << " | Email: " << email;
}

void Student::setBasein4(string id, string name, string gender, int birthYear,
                          string parentName, string parentPhone, string email) {
    this->id = id;
    this->name = name;
    this->gender = gender;
    this->birthYear = birthYear;
    this->parentName = parentName;
    this->parentPhone = parentPhone;
    this->email = email;
}
