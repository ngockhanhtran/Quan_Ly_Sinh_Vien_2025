#include "StudentManager.h"
#include "AccountManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

StudentManager::~StudentManager() {
    for (auto s : students) delete s;
}

// ------------------ UTIL ------------------

static inline string trim(const string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

// ===============================
//  ĐỌC FILE CSV
// ===============================

void StudentManager::loadFromFile(const string& filename) {
    for (auto p : students) delete p;
    students.clear();

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "ERROR: Khong the mo file " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // bỏ dòng tiêu đề

    while (getline(file, line)) {
        if (trim(line).empty()) continue;
        stringstream ss(line);

        string id, name, gender, birthYearStr, faculty;
        string s1s, s2s, s3s;
        string parentName, parentPhone, email;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, gender, ',');
        getline(ss, birthYearStr, ',');
        getline(ss, faculty, ',');
        getline(ss, s1s, ',');
        getline(ss, s2s, ',');
        getline(ss, s3s, ',');
        getline(ss, parentName, ',');
        getline(ss, parentPhone, ',');
        getline(ss, email, ',');

        id = trim(id);
        name = trim(name);
        gender = trim(gender);
        faculty = trim(faculty);
        parentName = trim(parentName);
        parentPhone = trim(parentPhone);
        email = trim(email);

        int birthYear = 0;
        double s1 = 0, s2 = 0, s3 = 0;
        try { birthYear = stoi(birthYearStr); } catch (...) {}
        try { s1 = stod(s1s); } catch (...) {}
        try { s2 = stod(s2s); } catch (...) {}
        try { s3 = stod(s3s); } catch (...) {}

        Student* st = nullptr;

        if (faculty == "CNTT") {
            auto* it = new ITStudent();
            it->setBasein4(id, name, gender, birthYear, parentName, parentPhone, email);
            it->setScores(s1, s2, s3);
            st = it;
        } else if (faculty == "Logistics") {
            auto* lg = new LogisticsStudent();
            lg->setBasein4(id, name, gender, birthYear, parentName, parentPhone, email);
            lg->setScores(s1, s2, s3);
            st = lg;
        } else if (faculty == "English") {
            auto* en = new EnglishStudent();
            en->setBasein4(id, name, gender, birthYear, parentName, parentPhone, email);
            en->setScores(s1, s2, s3);
            st = en;
        }

        if (st) students.push_back(st);
    }

    file.close();
    cout << "Da nap " << students.size() << " sinh vien tu file " << filename << endl;
}

// ===============================
//  GHI FILE CSV
// ===============================
void StudentManager::saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "ERROR: Khong the ghi file " << filename << endl;
        return;
    }

    file << "id,name,gender,birthYear,faculty,score1,score2,score3,parentName,parentPhone,email\n";

    for (auto* s : students) {
        // ta chỉ lưu GPA tổng hợp, hoặc có thể bổ sung getter điểm riêng từng khoa
        file << s->getID() << ","
             << s->getName() << ","
             << "N/A" << "," << 0 << ","
             << s->getFaculty() << ","
             << 0 << "," << 0 << "," << 0 << ","
             << s->getParentName() << ","
             << s->getParentPhone() << ","
             << s->getEmail() << "\n";
    }
    file.close();
    cout << "Da luu du lieu ra file " << filename << endl;
}

// ===============================
//  XUẤT FILE RIÊNG TỪNG KHOA
// ===============================
void StudentManager::exportFacultyFiles() {
    ofstream it("students_CNTT.csv");
    ofstream lg("students_Logistics.csv");
    ofstream en("students_English.csv");

    it << "id,name,faculty,GPA,parentName,parentPhone,email\n";
    lg << "id,name,faculty,GPA,parentName,parentPhone,email\n";
    en << "id,name,faculty,GPA,parentName,parentPhone,email\n";

    for (auto* s : students) {
        double gpa = s->calcGPA();
        string f = s->getFaculty();
        if (f == "CNTT")
            it << s->getID() << "," << s->getName() << "," << f << "," << fixed << setprecision(2) << gpa << ","
               << s->getParentName() << "," << s->getParentPhone() << "," << s->getEmail() << "\n";
        else if (f == "Logistics")
            lg << s->getID() << "," << s->getName() << "," << f << "," << fixed << setprecision(2) << gpa << ","
               << s->getParentName() << "," << s->getParentPhone() << "," << s->getEmail() << "\n";
        else if (f == "English")
            en << s->getID() << "," << s->getName() << "," << f << "," << fixed << setprecision(2) << gpa << ","
               << s->getParentName() << "," << s->getParentPhone() << "," << s->getEmail() << "\n";
    }

    it.close(); lg.close(); en.close();
    cout << "Da xuat file students_CNTT.csv, students_Logistics.csv, students_English.csv\n";
}

// ===============================
//  THÊM    /   SỬA     /   XÓA
// ===============================

void StudentManager::addStudent() {
    cout << "Chon khoa:\n1. CNTT\n2. Logistics\n3. English\n=> ";
    int ch; cin >> ch; cin.ignore();

    Student* s = nullptr;
    if (ch == 1) s = new ITStudent();
    else if (ch == 2) s = new LogisticsStudent();
    else if (ch == 3) s = new EnglishStudent();
    else { cout << "Lua chon khong hop le!\n"; return; }

    s->input();
    students.push_back(s);
    cout << "Them sinh vien thanh cong!\n";
}

void StudentManager::editStudent(const string& id) {
    for (auto* s : students) {
        if (s->getID() == id) {
            cout << "Nhap lai thong tin moi cho " << id << ":\n";
            s->input();
            cout << "Cap nhat thanh cong!\n";
            return;
        }
    }
    cout << "ERROR: Khong tim thay sinh vien co ma: " << id << endl;
}

void StudentManager::removeStudent(const string& id) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if ((*it)->getID() == id) {
            delete *it;
            students.erase(it);
            cout << "Da xoa sinh vien " << id << endl;
            return;
        }
    }
    cout << "ERROR: Khong tim thay sinh vien " << id << endl;
}

// ===============================
//  DANH SÁCH / TÌM KIẾM / THỐNG KÊ
// ===============================
void StudentManager::listAllStudents() const {
    cout << left << setw(10) << "MaSV" << setw(20) << "Ho ten"
         << setw(12) << "Khoa" << setw(8) << "GPA"
         << setw(20) << "Phu huynh" << setw(12) << "SDT" << endl;
    cout << string(80, '-') << endl;
    for (auto* s : students) {
        cout << left << setw(10) << s->getID()
             << setw(20) << s->getName()
             << setw(12) << s->getFaculty()
             << setw(8) << fixed << setprecision(2) << s->calcGPA()
             << setw(20) << s->getParentName()
             << setw(12) << s->getParentPhone() << endl;
    }
}

void StudentManager::viewStudentByID(const string& id) const {
    for (auto* s : students) {
        if (s->getID() == id) {
            s->display();
            cout << " | GPA: " << fixed << setprecision(2) << s->calcGPA() << endl;
            return;
        }
    }
    cout << "ERROR: Khong tim thay sinh vien co ma: " << id << endl;
}

void StudentManager::statistics() const {
    struct Stats { int count=0; double total=0; };
    Stats cntt, log, eng;

    for (auto* s : students) {
        double gpa = s->calcGPA();
        if (s->getFaculty() == "CNTT") { cntt.count++; cntt.total += gpa; }
        else if (s->getFaculty() == "Logistics") { log.count++; log.total += gpa; }
        else if (s->getFaculty() == "English") { eng.count++; eng.total += gpa; }
    }

    cout << "\n===== Thong ke GPA trung binh =====\n";
    cout << "CNTT: " << (cntt.count ? cntt.total / cntt.count : 0) << endl;
    cout << "Logistics: " << (log.count ? log.total / log.count : 0) << endl;
    cout << "English: " << (eng.count ? eng.total / eng.count : 0) << endl;
}

// ===============================
//  MENU CÁC QUYỀN
// ===============================

void StudentManager::managerMenu() {
    const string filename = "students.csv";
    loadFromFile(filename);

    while (true) {
        cout << "\n===== MENU QUAN LY (MANAGER) =====\n";
        cout << "1. Them sinh vien\n2. Sua sinh vien\n3. Xoa sinh vien\n";
        cout << "4. Danh sach sinh vien\n5. Thong ke\n6. Xuat file theo khoa\n7. Luu file\n0. Thoat\n";
        cout << "==================================\nChon: ";
        int ch; cin >> ch; cin.ignore();

        if (ch == 1) addStudent();
        else if (ch == 2) { string id; cout << "Nhap ma SV: "; getline(cin, id); editStudent(id); }
        else if (ch == 3) { string id; cout << "Nhap ma SV: "; getline(cin, id); removeStudent(id); }
        else if (ch == 4) listAllStudents();
        else if (ch == 5) statistics();
        else if (ch == 6) exportFacultyFiles();
        else if (ch == 7) saveToFile(filename);
        else if (ch == 0) { saveToFile(filename); cout << "Thoat menu quan ly.\n"; break; }
        else cout << "Lua chon khong hop le!\n";
    }
}

void StudentManager::studentMenu(string id) {
    loadFromFile("students.csv");
    cout << "\n===== THONG TIN SINH VIEN =====\n";
    viewStudentByID(id);
}

// ===============================
//  MENU ADMIN
// ===============================
void StudentManager::adminMenu(AccountManager& accountManager) {
    const string studentFile = "students.csv";
    const string accountFile = "accounts.csv";

    loadFromFile(studentFile);
    accountManager.loadFromFile(accountFile);

    while (true) {
        cout << "\n===== MENU ADMIN =====\n";
        cout << "1. Xem danh sach sinh vien\n";
        cout << "2. Xoa tai khoan + sinh vien\n";
        cout << "3. Reset mat khau sinh vien\n";
        cout << "4. Thong ke tong hop\n";
        cout << "0. Quay lai\n";
        cout << "=======================\n";
        cout << "Chon: ";
        int choice; 
        cin >> choice; 
        cin.ignore();

        if (choice == 0) {
            cout << "Thoat menu admin.\n";
            saveToFile(studentFile);
            accountManager.saveToFile(accountFile);
            break;
        }

        switch (choice) {
            case 1:
                listAllStudents();
                break;

            case 2: {
                string id;
                cout << "Nhap ma sinh vien can xoa: ";
                getline(cin, id);
                removeStudentAndAccount(accountManager, id);
                // Lưu lại ngay sau khi xóa
                saveToFile(studentFile);
                accountManager.saveToFile(accountFile);
                break;
            }

            case 3: {
                string id;
                cout << "Nhap ma sinh vien can reset mat khau: ";
                getline(cin, id);
                if (accountManager.resetPassword(id, "12345@")) {
                    cout << "Dat lai mat khau thanh cong!\n";
                    accountManager.saveToFile(accountFile);
                } else {
                    cout << "ERROR: Khong tim thay tai khoan!\n";
                }
                break;
            }

            case 4:
                statistics();
                break;

            default:
                cout << "Lua chon khong hop le!\n";
        }
    }
}

// ===============================
//  XÓA SONG SONG ACCOUNT + STUDENT
// ===============================
void StudentManager::removeStudentAndAccount(AccountManager& accountManager, const string& studentID) {
    bool studentFound = false;

    // Xóa trong danh sách sinh viên
    for (auto it = students.begin(); it != students.end(); ++it) {
        if ((*it)->getID() == studentID) {
            delete *it;
            students.erase(it);
            studentFound = true;
            break;
        }
    }

    if (!studentFound) {
        cout << "ERROR: Khong tim thay sinh vien co ma: " << studentID << endl;
        return;
    }

    // Xóa trong danh sách tài khoản
    bool accountFound = false;
    auto& accs = accountManager.getAccounts();
    for (auto it = accs.begin(); it != accs.end(); ++it) {
        if (it->getUsername() == studentID) {
            accs.erase(it);
            accountFound = true;
            break;
        }
    }

    if (accountFound)
        cout << "Da xoa sinh vien va tai khoan tuong ung: " << studentID << endl;
    else
        cout << "CAUTION: Da xoa sinh vien nhung khong tim thay tai khoan tuong ung.\n";
}
