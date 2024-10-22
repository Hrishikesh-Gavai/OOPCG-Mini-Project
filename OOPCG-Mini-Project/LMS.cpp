#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

class Book {
    char bno[6]; // Book No.
    char bname[50]; // Book Name
    char aname[20]; // Author Name

public:
    void createBook() {
        cout << "\nNEW BOOK ENTRY...\n";
        cout << "\nENTER BOOK NO.: ";
        cin >> bno;
        cin.ignore(); // Ignore leftover newline
        cout << "\nENTER BOOK NAME: ";
        cin.getline(bname, 50);
        cout << "\nENTER AUTHOR NAME: ";
        cin.getline(aname, 20);
        cout << "\n\nBook Created..";
    }

    void showBook() const {
        cout << "\nBook Number: " << bno;
        cout << "\nBook Name: " << bname;
        cout << "\nBook Author Name: " << aname;
    }

    void modifyBook() {
        cout << "\nBook Number: " << bno;
        cout << "\nModify Book Name: ";
        cin.ignore();
        cin.getline(bname, 50);
        cout << "\nModify Author's Name: ";
        cin.getline(aname, 20);
    }

    const char* retBNo() const {
        return bno;
    }

    void report() const {
        cout << bno << setw(30) << bname << setw(30) << aname << endl;
    }
};

class Student {
    char admno[6]; // Admission No.
    char name[20];
    char stbno[6]; // Student Book No.
    int token; // Total Books Issued

public:
    void createStudent() {
        cout << "\nNEW STUDENT ENTRY...\n";
        cout << "\nEnter The Admission No.: ";
        cin >> admno;
        cin.ignore(); // Ignore leftover newline
        cout << "Enter The Student Name: ";
        cin.getline(name, 20);
        token = 0;
        stbno[0] = '\0';
        cout << "\nStudent Record Created...";
    }

    void showStudent() const {
        cout << "\nAdmission Number: " << admno;
        cout << "\nStudent Name: " << name;
        cout << "\nNo of Books Issued: " << token;
        if (token == 1) {
            cout << "\nBook Number: " << stbno;
        }
    }

    void modifyStudent() {
        cout << "\nAdmission No.: " << admno;
        cout << "\nModify Student Name: ";
        cin.ignore();
        cin.getline(name, 20);
    }

    const char* retAdmNo() const {
        return admno;
    }

    const char* retStBNo() const {
        return stbno;
    }

    int retToken() const {
        return token;
    }

    void addToken() {
        token = 1;
    }

    void resetToken() {
        token = 0;
    }

    void getStBNo(const char t[]) {
        strcpy(stbno, t);
    }

    void report() const {
        cout << "\t" << admno << setw(20) << name << setw(10) << token << endl;
    }
};

fstream fp, fp1; // File stream objects
Book bk; // Book class object
Student st; // Student class object

void writeBook() {
    char ch;
    fp.open("book.dat", ios::out | ios::app);
    do {
        bk.createBook();
        fp.write(reinterpret_cast<char*>(&bk), sizeof(Book));
        cout << "\n\nDo you want to add more records... (y/n)? ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void writeStudent() {
    char ch;
    fp.open("student.dat", ios::out | ios::app);
    do {
        st.createStudent();
        fp.write(reinterpret_cast<char*>(&st), sizeof(Student));
        cout << "\n\nDo you want to add more records... (y/n)? ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void displayBook(const char n[]) {
    cout << "\nBOOK DETAILS\n";
    bool found = false;
    fp.open("book.dat", ios::in);
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(Book))) {
        if (strcmp(bk.retBNo(), n) == 0) {
            bk.showBook();
            found = true;
        }
    }
    fp.close();
    if (!found) {
        cout << "\n\nBook does not exist";
    }
}

void displayStudent(const char n[]) {
    cout << "\nSTUDENT DETAILS\n";
    bool found = false;
    fp.open("student.dat", ios::in);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        if (strcmp(st.retAdmNo(), n) == 0) {
            st.showStudent();
            found = true;
        }
    }
    fp.close();
    if (!found) {
        cout << "\n\nStudent does not exist";
    }
}

void modifyBook() {
    char n[6];
    cout << "\n\nMODIFY BOOK RECORD...";
    cout << "\n\nEnter the book no.: ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    bool found = false;
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(Book)) && !found) {
        if (strcmp(bk.retBNo(), n) == 0) {
            bk.showBook();
            cout << "\nEnter the new details for the book";
            bk.modifyBook();
            int pos = -1 * sizeof(bk);
            fp.seekp(pos, ios::cur);
            fp.write(reinterpret_cast<char*>(&bk), sizeof(Book));
            cout << "\n\nRecord Updated";
            found = true;
        }
    }
    fp.close();
    if (!found) {
        cout << "\n\nRecord Not Found";
    }
}

void modifyStudent() {
    char n[6];
    cout << "\n\nMODIFY STUDENT RECORD...";
    cout << "\n\nEnter the Admission no.: ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    bool found = false;
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student)) && !found) {
        if (strcmp(st.retAdmNo(), n) == 0) {
            st.showStudent();
            cout << "\nEnter the new details for the student";
            st.modifyStudent();
            int pos = -1 * sizeof(st);
            fp.seekp(pos, ios::cur);
            fp.write(reinterpret_cast<char*>(&st), sizeof(Student));
            cout << "\n\nRecord Updated";
            found = true;
        }
    }
    fp.close();
    if (!found) {
        cout << "\n\nRecord Not Found";
    }
}

void deleteStudent() {
    char n[6];
    cout << "\n\nDELETE STUDENT...";
    cout << "\n\nEnter the Admission no.: ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    fstream tempFile("temp.dat", ios::out);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        if (strcmp(st.retAdmNo(), n) != 0) {
            tempFile.write(reinterpret_cast<char*>(&st), sizeof(Student));
        }
    }
    tempFile.close();
    fp.close();
    remove("student.dat");
    rename("temp.dat", "student.dat");
    cout << "\n\nRecord Deleted.";
}

void deleteBook() {
    char n[6];
    cout << "\n\nDELETE BOOK...";
    cout << "\n\nEnter the Book no.: ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    fstream tempFile("temp.dat", ios::out);
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(Book))) {
        if (strcmp(bk.retBNo(), n) != 0) {
            tempFile.write(reinterpret_cast<char*>(&bk), sizeof(Book));
        }
    }
    tempFile.close();
    fp.close();
    remove("book.dat");
    rename("temp.dat", "book.dat");
    cout << "\n\nRecord Deleted.";
}

void displayAllStudents() {
    fp.open("student.dat", ios::in);
    if (!fp) {
        cout << "File Could Not Be Open";
        return;
    }
    cout << "\n\n\t\tStudent List\n\n";
    cout << "========================================================================\n";
    cout << "\tAdmission No." << setw(10) << "Name" << setw(20) << "Books Issued\n";
    cout << "========================================================================\n";
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student))) {
        st.report();
    }
    fp.close();
}

void displayAllBooks() {
    fp.open("book.dat", ios::in);
    if (!fp) {
        cout << "File Could Not Be Open";
        return;
    }
    cout << "\n\n\t\tBook List\n\n";
    cout << "=========================================================================\n";
    cout << "\tBook No." << setw(20) << "Book Name" << setw(25) << "Book Author\n";
    cout << "=========================================================================\n";
    while (fp.read(reinterpret_cast<char*>(&bk), sizeof(Book))) {
        bk.report();
    }
    fp.close();
}

void bookIssue() {
    char sn[6], bn[6];
    bool found = false, flag = false;
    cout << "\n\nBOOK ISSUE...";
    cout << "\n\n\tEnter Admission no.: ";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student)) && !found) {
        if (strcmp(st.retAdmNo(), sn) == 0) {
            found = true;
            if (st.retToken() == 0) {
                cout << "\n\n\tEnter The Book No.: ";
                cin >> bn;
                while (fp1.read(reinterpret_cast<char*>(&bk), sizeof(Book)) && !flag) {
                    if (strcmp(bk.retBNo(), bn) == 0) {
                        flag = true;
                        st.addToken();
                        st.getStBNo(bk.retBNo());
                        int pos = -1 * sizeof(st);
                        fp.seekp(pos, ios::cur);
                        fp.write(reinterpret_cast<char*>(&st), sizeof(Student));
                        cout << "\n\n\tBook Issued Successfully\nPlease Note The Book Issue Date On The Backside Of Your Book And Return Book Within 15 Days, Otherwise Fine Of 1 Rs. Per Day Will Be Added.";
                    }
                }
                if (!flag) {
                    cout << "Book No. Does Not Exist";
                }
            } else {
                cout << "You Have Not Returned The Last Book";
            }
        }
    }
    if (!found) {
        cout << "Student Record Does Not Exist...";
    }
    fp.close();
    fp1.close();
}

void bookDeposit() {
    char sn[6], bn[6];
    bool found = false, flag = false;
    int day, fine;
    cout << "\n\nBOOK DEPOSIT...";
    cout << "\n\n\tEnter Admission no. of Student: ";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read(reinterpret_cast<char*>(&st), sizeof(Student)) && !found) {
        if (strcmp(st.retAdmNo(), sn) == 0) {
            found = true;
            if (st.retToken() == 1) {
                while (fp1.read(reinterpret_cast<char*>(&bk), sizeof(Book)) && !flag) {
                    if (strcmp(bk.retBNo(), st.retStBNo()) == 0) {
                        flag = true;
                        bk.showBook();
                        cout << "\n\nBook Deposited In No. Of Days: ";
                        cin >> day;
                        if (day > 15) {
                            fine = (day - 15) * 1;
                            cout << "\n\nFine = " << fine;
                        }
                        st.resetToken();
                        int pos = -1 * sizeof(st);
                        fp.seekp(pos, ios::cur);
                        fp.write(reinterpret_cast<char*>(&st), sizeof(Student));
                        cout << "\n\n\tBook Deposited Successfully";
                    }
                }
                if (!flag) {
                    cout << "Book No. Does Not Exist";
                }
            } else {
                cout << "No Book Issued";
            }
        }
    }
    if (!found) {
        cout << "Student Record Does Not Exist...";
    }
    fp.close();
    fp1.close();
}

void start() {
    cout << "\n\tLIBRARY\n\tMANAGEMENT\n\tSYSTEM";
}

void adminMenu() {
    int ch2;
    cout << "\n\n\n\tADMINISTRATOR MENU";
    cout << "\n\n\n\t1.CREATE STUDENT RECORD";
    cout << "\n\n\n\t2.DISPLAY ALL STUDENT RECORDS";
    cout << "\n\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD";
    cout << "\n\n\n\t4.MODIFY STUDENT RECORD";
    cout << "\n\n\n\t5.DELETE STUDENT RECORD";
    cout << "\n\n\n\t6.CREATE BOOK RECORD";
    cout << "\n\n\n\t7.DISPLAY ALL BOOKS";
    cout << "\n\n\n\t8.DISPLAY SPECIFIC BOOK";
    cout << "\n\n\n\t9.MODIFY BOOK RECORD";
    cout << "\n\n\n\t10.DELETE BOOK RECORD";
    cout << "\n\n\n\t11.BACK TO MAIN MENU";
    cout << "\n\n\n\tPLEASE ENTER YOUR CHOICE (1-11): ";
    cin >> ch2;
    switch (ch2) {
        case 1: writeStudent(); break;
        case 2: displayAllStudents(); break;
        case 3: {
            char num[6];
            cout << "\n\n\t Please enter admission no.: ";
            cin >> num;
            displayStudent(num);
            break;
        }
        case 4: modifyStudent(); break;
        case 5: deleteStudent(); break;
        case 6: writeBook(); break;
        case 7: displayAllBooks(); break;
        case 8: {
            char num[6];
            cout << "\n\n\tPlease enter book no.: ";
            cin >> num;
            displayBook(num);
            break;
        }
        case 9: modifyBook(); break;
        case 10: deleteBook(); break;
        case 11: return;
        default: cout << "Invalid choice";
    }
    adminMenu();
}

int main() {
    char ch;
    start();
    do {
        cout << "\n\n\n\t MAIN MENU";
        cout << "\n\n\n\t1. BOOK ISSUE";
        cout << "\n\n\n\t2. BOOK DEPOSIT";
        cout << "\n\n\n\t3. ADMINISTRATOR MENU";
        cout << "\n\n\n\t4. EXIT";
        cout << "\n\n\n\t PLEASE SELECT YOUR OPTION (1-4): ";
        cin >> ch;
        switch (ch) {
            case '1': bookIssue(); break;
            case '2': bookDeposit(); break;
            case '3': adminMenu(); break;
            case '4': exit(0); break;
            default: cout << "INVALID CHOICE";
        }
    } while (ch != '4');

    return 0;
}