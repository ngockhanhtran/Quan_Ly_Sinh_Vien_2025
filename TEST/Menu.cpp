#include "Menu.h"
#include <iostream>
#include <limits> 

void Menu::khoidong() {
    ql.docFile("sinhvien.txt");

    int chon;
    do {
        cout << "\n========== MENU QUAN LY SINH VIEN ==========\n";
        cout << "1. Them sinh vien\n";
        cout << "2. Hien thi danh sach\n";
        cout << "3. Xoa sinh vien\n";
        cout << "4. Sua thong tin\n";
        cout << "5. Tim kiem sinh vien\n";
        cout << "6. Sap xep theo diem trung binh\n";
        cout << "7. Thong ke xep loai\n";
        cout << "8. Luu file (sinhvien.txt)\n";
        cout << "9. Xuat bao cao (baocao.txt)\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "===========================================\n";
        cout << "Nhap lua chon: ";

        cin >> chon;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Lua chon khong hop le! Vui long nhap so tu 0 den 9.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        switch (chon) {
            case 1:
                ql.themSV();
                break;
            case 2:
                ql.hienThi();
                break;
            case 3: {
                string ma;
                cout << "Nhap ma sinh vien can xoa: ";
                getline(cin, ma);
                ql.xoaSV(ma);
                break;
            }
            case 4: {
                string ma;
                cout << "Nhap ma sinh vien can sua: ";
                getline(cin, ma);
                ql.suaSV(ma);
                break;
            }
            case 5: {
                string ma;
                cout << "Nhap ma sinh vien can tim: ";
                getline(cin, ma);
                ql.timKiem(ma);
                break;
            }
            case 6:
                ql.sapXepTheoDiem();
                break;
            case 7:
                ql.thongKe();
                break;
            case 8:
                ql.ghiFile("sinhvien.txt");
                cout << "Da luu danh sach vao sinhvien.txt\n";
                break;
            case 9:
                ql.ghiBaoCao("baocao.txt");
                cout << "Da xuat bao cao vao baocao.txt\n";
                break;
            case 0:
                cout << "Dang thoat chuong trinh...\n";
                break;
            default:
                cout << "Lua chon khong hop le, vui long nhap lai!\n";
                break;
        }
    } while (chon != 0);
}
