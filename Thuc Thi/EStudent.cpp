#include "EStudent.h"
#include <iostream>
using namespace std;

EnglishStudent::EnglishStudent()
    : Student(), phonetics(0), semantics(0), grammar(0), tc1(3), tc2(3), tc3(3) {}

void EnglishStudent::input() {
    Student::input();
    cout << "Nhap diem phonetics: "; cin >> phonetics;
    cout << "Nhap diem semantics: "; cin >> semantics;
    cout << "Nhap diem grammar: "; cin >> grammar;
    cin.ignore();
}

void EnglishStudent::display() const {
    Student::display();
    cout << " | Khoa: English"
         << " | GPA: " << calcGPA();
}

double EnglishStudent::calcGPA() const {
    return (phonetics * tc1 + semantics * tc2 + grammar * tc3) / (tc1 + tc2 + tc3);
}

void EnglishStudent::setScores(double phonetics, double semantics, double grammar) {
    this->phonetics = phonetics;
    this->semantics = semantics;
    this->grammar = grammar;
}
