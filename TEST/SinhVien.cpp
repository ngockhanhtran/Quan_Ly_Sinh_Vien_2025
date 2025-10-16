#include "SinhVien.h"

SinhVien::SinhVien() : maSV(""), hoTen(""), lop(""), diemTB(0) {}

SinhVien::SinhVien(string ma, string ten, string lop, double diem)
    : maSV(ma), hoTen(ten), lop(lop), diemTB(diem) {}

void SinhVien::nhap() {
    cout << "Nhap ma sinh vien: ";
    cin >> maSV;
    cin.ignore(); 
    cout << "Nhap ho ten sinh vien: ";
    getline(cin, hoTen);

    cout << "Nhap lop: ";
    getline(cin, lop);

    cout << "Nhap diem trung binh: ";
    cin >> diemTB;
}

void SinhVien::xuat() const {
    cout << left << setw(10) << maSV
         << setw(25) << hoTen
         << setw(10) << lop
         << setw(8) << fixed << setprecision(2) << diemTB
         << XepLoai() << endl;
}

string SinhVien::getMaSV() const { return maSV; }
string SinhVien::getHoTen() const { return hoTen; }
string SinhVien::getLop() const { return lop; }
double SinhVien::getDiem() const { return diemTB; }

string SinhVien::XepLoai() const {
    if (diemTB >= 8) return "Gioi";
    else if (diemTB >= 6.5) return "Kha";
    else return "Trung binh";
}

void SinhVien::ghiFile(ofstream &fout) const {
    fout << maSV << "|" << hoTen << "|" << lop << "|" << diemTB << "\n";
}

void SinhVien::docFile(ifstream &fin) {
    string dong;
    getline(fin, dong);
    if (dong.empty()) return;

    size_t a1 = dong.find('|');
    size_t a2 = dong.find('|', a1 + 1);
    size_t a3 = dong.find('|', a2 + 1);

    maSV = dong.substr(0, a1);
    hoTen = dong.substr(a1 + 1, a2 - a1 - 1);
    lop = dong.substr(a2 + 1, a3 - a2 - 1);
    diemTB = stod(dong.substr(a3 + 1));
}
