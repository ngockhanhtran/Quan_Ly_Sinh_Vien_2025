#pragma once
#include "Student.h"
#include "ITStudent.h"
#include "LogStudent.h"
#include "EStudent.h"
#include "Account.h"
#include "AccountManager.h"
#include <vector>
#include <string>
using namespace std;

/*
📝 QUẢN LÝ SINH VIÊN
--------------------
- Đọc / ghi danh sách sinh viên từ file CSV
- Chỉ MANAGER được thêm/sửa/xóa
- ADMIN xem thống kê GPA
- STUDENT chỉ xem thông tin cá nhân
*/

class StudentManager {
private:
    vector<Student*> students;

public:
    ~StudentManager();

    void loadFromFile(const string& filename);
    void saveToFile(const string& filename);
    void exportFacultyFiles(); // Xuất 3 file theo khoa

    void addStudent();
    void editStudent(const string& id);
    void removeStudent(const string& id);
    void listAllStudents() const;
    void viewStudentByID(const string& id) const;
    void statistics() const;

    void managerMenu();
    void studentMenu(string id);

    void adminMenu();
    void adminMenu(AccountManager& accountManager);
    void removeStudentAndAccount(AccountManager& accountManager, const string& studentID);
};
