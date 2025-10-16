#ifndef SINHVIEN_H
#define SINHVIEN_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class SinhVien{
private:
    string maSV, hoTen, lop;
    double diemTB;
public:
    SinhVien();
    SinhVien(string ma, string ten, string lop, double diem);

    void nhap();
    void xuat() const;

    string getMaSV() const;
    string getHoTen() const;
    string getLop() const;
    double getDiem() const;

    string XepLoai() const;
    
    void ghiFile(ofstream &fout) const;
    void docFile(ifstream &fin);
};

#endif