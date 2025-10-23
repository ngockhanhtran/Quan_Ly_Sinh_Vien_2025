#pragma once
#include "Student.h"

/*
📝 SINH VIÊN KHOA TIẾNG ANH
---------------------------
- Gồm 3 môn: Phonetics, Semantics, Grammar
*/

class EnglishStudent:public Student{
private:
    double phonetics, semantics, grammar;
    int tc1, tc2, tc3;
public:
    EnglishStudent();

    void input();
    void display() const;
    double calcGPA() const;
    string getFaculty() const { return "English"; }

    void setScores(double phonetics, double semantics, double grammar);
};