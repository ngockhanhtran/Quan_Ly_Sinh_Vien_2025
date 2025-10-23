#pragma once
#include "Student.h"
/*
📝 SINH VIÊN CÔNG NGHỆ THÔNG TIN (CNTT)
---------------------------------------
- Gồm 3 môn: OOP, DSA, TRR
- Mỗi môn có điểm & tín chỉ
*/
class ITStudent : public Student {
private: 
    double oop, dsa, trr;
    int tc1, tc2 ,tc3;
public: 
    ITStudent();

    void input();
    void display() const;
    double calcGPA() const;
    string getFaculty() const override { return "CNTT"; }

    // Dùng khi đọc dữ liệu từ file
    void setScores(double oop, double ds, double trr);
};