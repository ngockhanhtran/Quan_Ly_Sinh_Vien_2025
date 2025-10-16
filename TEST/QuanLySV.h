#ifndef QUANLYSV_H
#define QUANLYSV_H

#include "SinhVien.h"
#include <vector>
using namespace std;

class QuanLySV {
private:
    vector<SinhVien> ds;
public:
    void themSV();
    void hienThi() const;
    void xoaSV(string ma);
    void suaSV(string ma);
    void timKiem(string ma) const;
    void sapXepTheoDiem();
    void thongKe() const;

    void docFile(const string &tenFile);
    void ghiFile(const string &tenFile) const;
    void ghiBaoCao(const string &tenFile) const;
};

#endif