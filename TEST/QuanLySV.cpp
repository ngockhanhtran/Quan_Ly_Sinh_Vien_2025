#include "QuanLySV.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

void QuanLySV::themSV() {
    SinhVien sv;
    sv.nhap();
    ds.push_back(sv);
}

void QuanLySV::hienThi() const {
    if (ds.empty()) {
        cout << "Danh sach sinh vien trong!\n";
        return;
    }

    cout << left << setw(10) << "MaSV"
         << setw(25) << "Ho ten"
         << setw(10) << "Lop"
         << setw(8) << "Diem"
         << "Xep loai" << endl;
    cout << string(60, '-') << endl;

    for (const auto &sv : ds)
        sv.xuat();
}

void QuanLySV::xoaSV(string ma) {
    for (auto it = ds.begin(); it != ds.end(); ++it) {
        if (it->getMaSV() == ma) {
            ds.erase(it);
            cout << "Da xoa sinh vien " << ma << endl;
            return;
        }
    }
    cout << "Khong tim thay ma SV!\n";
}

void QuanLySV::suaSV(string ma) {
    for (auto &sv : ds) {
        if (sv.getMaSV() == ma) {
            cout << "Nhap lai thong tin moi:\n";
            sv.nhap();
            return;
        }
    }
    cout << "Khong tim thay ma SV!\n";
}

void QuanLySV::timKiem(string ma) const {
    for (const auto &sv : ds)
        if (sv.getMaSV() == ma) {
            sv.xuat();
            return;
        }
    cout << "Khong tim thay sinh vien!\n";
}

void QuanLySV::sapXepTheoDiem() {
    sort(ds.begin(), ds.end(), [](const SinhVien &a, const SinhVien &b) {
        return a.getDiem() > b.getDiem();
    });
    cout << "Da sap xep theo diem giam dan!\n";
}

void QuanLySV::thongKe() const {
    int tong = ds.size();
    if (tong == 0) {
        cout << "Danh sach rong, khong co du lieu thong ke!\n";
        return;
    }

    int gioi = 0, kha = 0, tb = 0;
    for (const auto &sv : ds) {
        string xl = sv.XepLoai();
        if (xl == "Gioi") gioi++;
        else if (xl == "Kha") kha++;
        else tb++;
    }

    cout << "\n===== THONG KE XEP LOAI =====\n";
    cout << "Tong SV: " << tong << "\n";
    cout << "Gioi: " << gioi << " (" << gioi * 100.0 / tong << "%)\n";
    cout << "Kha: " << kha << " (" << kha * 100.0 / tong << "%)\n";
    cout << "Trung binh: " << tb << " (" << tb * 100.0 / tong << "%)\n";
}

void QuanLySV::docFile(const string &tenFile) {
    ifstream fin(tenFile);
    if (!fin.is_open()) {
        cout << "Khong mo duoc file '" << tenFile << "'!\n";
        return;
    }

    ds.clear();
    while (true) {
        SinhVien sv;
        sv.docFile(fin);
        if (fin.eof()) break;
        ds.push_back(sv);
    }
    fin.close();
    cout << "Da doc " << ds.size() << " sinh vien tu file.\n";
}

void QuanLySV::ghiFile(const string &tenFile) const {
    ofstream fout(tenFile);
    for (const auto &sv : ds)
        sv.ghiFile(fout);
    fout.close();
}

void QuanLySV::ghiBaoCao(const string &tenFile) const {
    ofstream fout(tenFile);
    if (!fout.is_open()) {
        cout << "Khong mo duoc file bao cao!\n";
        return;
    }

    fout << left << setw(10) << "MaSV"
         << setw(25) << "Ho ten"
         << setw(10) << "Lop"
         << setw(8) << "Diem"
         << "Xep loai\n";
    fout << string(60, '-') << "\n";

    for (const auto &sv : ds) {
        fout << left << setw(10) << sv.getMaSV()
             << setw(25) << sv.getHoTen()
             << setw(10) << sv.getLop()
             << setw(8) << fixed << setprecision(2) << sv.getDiem()
             << sv.XepLoai() << "\n";
    }

    int tong = ds.size(), gioi = 0, kha = 0, tb = 0;
    for (const auto &sv : ds) {
        string xl = sv.XepLoai();
        if (xl == "Gioi") gioi++;
        else if (xl == "Kha") kha++;
        else tb++;
    }

    fout << "\n===== THONG KE XEP LOAI =====\n";
    fout << "Tong SV: " << tong << "\n";
    fout << "Gioi: " << gioi << " (" << gioi * 100.0 / tong << "%)\n";
    fout << "Kha: " << kha << " (" << kha * 100.0 / tong << "%)\n";
    fout << "Trung binh: " << tb << " (" << tb * 100.0 / tong << "%)\n";

    fout.close();
    cout << "Da ghi bao cao vao file '" << tenFile << "' thanh cong!\n";
}
