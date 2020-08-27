#include <iostream>
#include <sqlite3.h>
#include "sqlutils.h"

using namespace std;

void createtables(sqlite3 *db)
{
    /* Create SQL statement */
    const char *student = "CREATE TABLE student("
                          "id      INTEGER PRIMARY KEY   AUTOINCREMENT NOT NULL,"
                          "roll_no CHAR(10)     NOT NULL,"
                          "name    CHAR(100)    NOT NULL);";

    const char *subject = "CREATE TABLE subject("
                          "id        INTEGER PRIMARY KEY   AUTOINCREMENT NOT NULL,"
                          "name      CHAR(100) NOT NULL,"
                          "min_pass  INT       NOT NULL,"
                          "max_mark  INT       NOT NULL);";

    const char *marks = "CREATE TABLE marks("
                        "id         INTEGER PRIMARY KEY  AUTOINCREMENT NOT NULL,"
                        "student_id INT  NOT NULL,"
                        "subject_id INT  NOT NULL,"
                        "mark       INT  NOT NULL);";

    const char *subjectinsert = "INSERT INTO subject (name, min_pass, max_mark) VALUES "
                                "('REG_LANG',35,100),"
                                "('ENGLISH',35,100),"
                                "('MATHS',35,100),"
                                "('SCIENCE',35,100),"
                                "('SOCIAL' ,35,100);";

    cout << "This will overwrite existing tables and data if any. Continue Y/N?";
    char ans = 'N';
    cin >> ans;

    if (!(ans == 'Y' || ans == 'y'))
        return;
    /* Dropping exising tables */
    runsql(db, "DROP TABLE marks;");
    runsql(db, "DROP TABLE student;");
    runsql(db, "DROP TABLE subject;");

    /* creating new tables */
    runsql(db, student);
    runsql(db, subject);
    runsql(db, marks);
    runsql(db, subjectinsert);
    cout << "Successfully generated tables and subjects inserted. Ready to go!" << endl;
    return;
}

void showstudent(sqlite3 *db)
{
    const char *sql = "SELECT * FROM student;";
    runsql(db, sql);
    return;
}

void showstudentmarks(sqlite3 *db)
{
    const char *sql = "SELECT s.name as name, sj.name as subject_name, m.mark  as mark FROM marks m "
                      "LEFT JOIN student s ON s.id = m.student_id "
                      "LEFT JOIN subject sj ON sj.id = m.subject_id;";
    runsql(db, sql);
    return;
}

void addstudent(sqlite3 *db)
{
    string name;
    string rollno;
    cout << "Enter Name > ";
    cin.ignore();
    getline(cin, name, '\n');
    cout << "Enter Roll Number > ";
    cin.ignore();
    getline(cin, rollno, '\n');
    const string stmnt = "INSERT INTO student (name, roll_no) VALUES ('" + name + "','" + rollno + "');";
    runsql(db, stmnt.c_str());
    return;
}

void addmarks(sqlite3 *db)
{
    string rollnumber;
    string marks;
    string subjects[] = {"REG_LANG", "ENGLISH", "MATHS", "SCIENCE", "SOCIAL"};
    cout << "Enter Roll Number > ";
    cin.ignore();
    getline(cin, rollnumber, '\n');
    for (int i = 0; i < 5; i++)
    {
        cout << "Enter Marks for " << subjects[i] << "> ";
        getline(cin, marks, '\n');
        const string stmnt = "INSERT INTO marks (student_id, subject_id, mark) VALUES"
                             "((SELECT id FROM student WHERE roll_no='" +
                             rollnumber + "'),"
                                          "(SELECT id FROM subject WHERE name='" +
                             subjects[i] + "'), " + marks + ");";
        runsql(db, stmnt.c_str());
    }
    return;
}

void runchoice(int choice, sqlite3 *db)
{
    switch (choice)
    {
    case 1:
        createtables(db);
        break;
    case 2:
        showstudent(db);
        break;
    case 3:
        showstudentmarks(db);
        break;
    case 4:
        addstudent(db);
        break;
    case 5:
        addmarks(db);
        break;
    default:
        break;
    }
}

void displaymenu(sqlite3 *db)
{
    int choice;
    const char *menu =
        "MENU:\n"
        "=====\n"
        "1)Initialize Database - First Time only. \033[1;31m(Warning This will overwrite your previous data)\033[0m\n"
        "2)Show Student\n"
        "3)Show Student Marks\n"
        "4)Add Student\n"
        "5)Add Student Mark\n"
        "6)Quit\n";
    while (1)
    {
        cout << menu << endl
             << "Your Choice > ";
        cin >> choice;
        if (choice > 6 || choice < 1)
            cout << "Wrong Choice\n"
                 << endl;
        if (choice == 6)
            break;
        runchoice(choice, db);
    }
}
