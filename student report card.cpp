#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;

class Student {
    int rollno;
    string name;
    int p_marks, c_marks, m_marks, e_marks, cs_marks;
    float per;
    char grade;

    void calculate() {
        per = (p_marks + c_marks + m_marks + e_marks + cs_marks) / 5.0f;
        if (per >= 60)
            grade = 'A';
        else if (per >= 50)
            grade = 'B';
        else if (per >= 33)
            grade = 'C';
        else
            grade = 'F';
    }

public:
    void getdata() {
        cout << "\nEnter The roll number of student: ";
        cin >> rollno;
        cin.ignore();
        cout << "Enter The Name of student: ";
        getline(cin, name);
        cout << "Enter The marks in physics out of 100: ";
        cin >> p_marks;
        cout << "Enter The marks in chemistry out of 100: ";
        cin >> c_marks;
        cout << "Enter The marks in maths out of 100: ";
        cin >> m_marks;
        cout << "Enter The marks in english out of 100: ";
        cin >> e_marks;
        cout << "Enter The marks in computer science out of 100: ";
        cin >> cs_marks;
        calculate();
    }

    void showdata() const {
        cout << "\nRoll number of student: " << rollno;
        cout << "\nName of student: " << name;
        cout << "\nMarks in Physics: " << p_marks;
        cout << "\nMarks in Chemistry: " << c_marks;
        cout << "\nMarks in Maths: " << m_marks;
        cout << "\nMarks in English: " << e_marks;
        cout << "\nMarks in Computer Science: " << cs_marks;
        cout << fixed << setprecision(2);
        cout << "\nPercentage of student is: " << per;
        cout << "\nGrade of student is: " << grade << endl;
    }

    void show_tabular() const {
        cout << left << setw(8) << rollno
             << setw(20) << name
             << setw(8) << p_marks
             << setw(8) << c_marks
             << setw(8) << m_marks
             << setw(8) << e_marks
             << setw(8) << cs_marks
             << setw(8) << setprecision(2) << per
             << setw(4) << grade << endl;
    }

    int retrollno() const { return rollno; }
};

void write_student() {
    Student st;
    ofstream outFile("student.dat", ios::binary | ios::app);
    st.getdata();
    outFile.write(reinterpret_cast<char*>(&st), sizeof(Student));
    outFile.close();
    cout << "\n\nStudent record has been created.\n";
    system("pause");
}

void display_all() {
    Student st;
    ifstream inFile("student.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open! Press any Key...";
        system("pause");
        return;
    }
    cout << "\n\n\n\t\tDISPLAY ALL RECORDS\n\n";
    while (inFile.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        st.showdata();
        cout << "\n====================================\n";
    }
    inFile.close();
    system("pause");
}

void display_sp(int n) {
    Student st;
    ifstream inFile("student.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open! Press any Key...";
        system("pause");
        return;
    }
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        if (st.retrollno() == n) {
            st.showdata();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found)
        cout << "\n\nRecord not found";
    system("pause");
}

void modify_student() {
    int no;
    bool found = false;
    cout << "\n\n\tTo Modify";
    cout << "\n\n\tPlease Enter The roll number of student: ";
    cin >> no;
    fstream File("student.dat", ios::binary | ios::in | ios::out);
    Student st;
    while (!File.eof() && !found) {
        streampos pos = File.tellg();
        if (File.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
            if (st.retrollno() == no) {
                st.showdata();
                cout << "\nPlease Enter The New Details of student" << endl;
                st.getdata();
                File.seekp(pos);
                File.write(reinterpret_cast<char*>(&st), sizeof(Student));
                cout << "\n\n\t Record Updated";
                found = true;
            }
        }
    }
    File.close();
    if (!found)
        cout << "\n\n Record Not Found ";
    system("pause");
}

void delete_student() {
    int no;
    cout << "\n\n\n\tDelete Record";
    cout << "\n\nPlease Enter The roll number of student You Want To Delete: ";
    cin >> no;
    ifstream inFile("student.dat", ios::binary);
    ofstream outFile("Temp.dat", ios::binary);
    Student st;
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        if (st.retrollno() != no)
            outFile.write(reinterpret_cast<char*>(&st), sizeof(Student));
        else
            found = true;
    }
    inFile.close();
    outFile.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    if (found)
        cout << "\n\n\tRecord Deleted ..";
    else
        cout << "\n\n\tRecord Not Found ..";
    system("pause");
}

void class_result() {
    Student st;
    ifstream inFile("student.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open! Press any Key...";
        system("pause");
        return;
    }
    cout << "\n\n\t\tALL STUDENTS RESULT \n\n";
    cout << "====================================================================\n";
    cout << left << setw(8) << "RollNo"
         << setw(20) << "Name"
         << setw(8) << "P"
         << setw(8) << "C"
         << setw(8) << "M"
         << setw(8) << "E"
         << setw(8) << "CS"
         << setw(8) << "%age"
         << setw(4) << "Grade" << endl;
    cout << "====================================================================\n";
    while (inFile.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        st.show_tabular();
    }
    inFile.close();
    system("pause");
}

void result() {
    int ans, rno;
    do {
        cout << "\n\n\nRESULT MENU";
        cout << "\n1. Class Result";
        cout << "\n2. Student Report Card";
        cout << "\n3. Back to Main Menu";
        cout << "\n\nEnter Choice (1/2/3): ";
        cin >> ans;
        switch (ans) {
            case 1:
                class_result();
                break;
            case 2:
                cout << "\n\nEnter Roll Number Of Student: ";
                cin >> rno;
                display_sp(rno);
                break;
            case 3:
                break;
            default:
                cout << "\a";
        }
    } while (ans != 3);
}

void entry_menu() {
    int ch2;
    do {
        cout << "\n\n\n\tENTRY MENU";
        cout << "\n1. CREATE STUDENT RECORD";
        cout << "\n2. DISPLAY ALL STUDENTS RECORDS";
        cout << "\n3. SEARCH STUDENT RECORD";
        cout << "\n4. MODIFY STUDENT RECORD";
        cout << "\n5. DELETE STUDENT RECORD";
        cout << "\n6. BACK TO MAIN MENU";
        cout << "\n\nPlease Enter Your Choice (1-6): ";
        cin >> ch2;
        switch (ch2) {
            case 1:
                write_student();
                break;
            case 2:
                display_all();
                break;
            case 3: {
                int num;
                cout << "\n\n\tPlease Enter The roll number: ";
                cin >> num;
                display_sp(num);
                break;
            }
            case 4:
                modify_student();
                break;
            case 5:
                delete_student();
                break;
            case 6:
                break;
            default:
                cout << "\a";
        }
    } while (ch2 != 6);
}

void intro() {
    cout << "\n\n\n\t\tSTUDENT";
    cout << "\n\t\tREPORT CARD";
    cout << "\n\t\tPROJECT";
    cout << "\n\nMADE BY : YOUR NAME";
    cout << "\nSCHOOL : YOUR SCHOOL";
    system("pause");
}

int main() {
    char ch;
    intro();
    do {
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n1. RESULT MENU";
        cout << "\n2. ENTRY/EDIT MENU";
        cout << "\n3. EXIT";
        cout << "\n\nPlease Select Your Option (1-3): ";
        cin >> ch;
        switch (ch) {
            case '1':
                result();
                break;
            case '2':
                entry_menu();
                break;
            case '3':
                exit(0);
            default:
                cout << "\a";
        }
    } while (ch != '3');
    return 0;
}