#include "LogStudent.h"
#include <iostream>
using namespace std;

LogisticsStudent::LogisticsStudent()
    : Student(), micro(0), macro(0), logistics(0), tc1(3), tc2(3), tc3(2) {}

void LogisticsStudent::input() {
    Student::input();
    cout << "Nhap diem Kinh te vi mo: "; cin >> micro;
    cout << "Nhap diem Kinh te vi mo: "; cin >> macro;
    cout << "Nhap diem Quan ly Logistics: "; cin >> logistics;
    cin.ignore();
}

void LogisticsStudent::display() const {
    Student::display();
    cout << " | Khoa: Logistics"
         << " | GPA: " << calcGPA();
}

double LogisticsStudent::calcGPA() const {
    return (micro * tc1 + macro * tc2 + logistics * tc3) / (tc1 + tc2 + tc3);
}

void LogisticsStudent::setScores(double micro, double macro, double logistics) {
    this->micro = micro;
    this->macro = macro;
    this->logistics = logistics;
}