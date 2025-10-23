#pragma once
#include "Student.h"

/*
📝 SINH VIÊN KHOA LOGISTICS
---------------------------
- Gồm 3 môn: Kinh tế vi mô, Kinh tế vĩ mô, Quản lý Logistics
*/

class LogisticsStudent : public Student {
private:
    double micro, macro, logistics;
    int tc1, tc2, tc3;

public:
    LogisticsStudent();

    void input();
    void display() const;
    double calcGPA() const;
    string getFaculty() const { return "Logistics"; }

    void setScores(double micro, double macro, double logistics);
};
