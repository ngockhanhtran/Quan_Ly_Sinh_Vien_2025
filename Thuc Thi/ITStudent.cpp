#include "ITStudent.h"
#include <iostream>
using namespace std;

ITStudent::ITStudent():Student(), oop(0), dsa(0), trr(0), tc1(3), tc2(3), tc3(2) {}

void ITStudent::input(){
    Student::input();
    cout << "Nhap diem OOP: "; cin >> oop;
    cout << "Nhap diem Cau truc du lieu: "; cin >> dsa;
    cout << "Nhap diem He dieu hanh: "; cin >> trr;
    cin.ignore();
}

void ITStudent::display() const{
    Student::display();
    cout << " | Khoa: CNTT"
         << " | GPA: " << calcGPA();
}

double ITStudent::calcGPA() const{
    return (oop * tc1 + dsa * tc2 + trr * tc3) / (tc1 + tc2 + tc3);
}

void ITStudent::setScores(double oop, double dsa, double trr){
    this->oop = oop;
    this->dsa = dsa;
    this->trr = trr;
}