#ifndef __STUDENT_H__
#define __STUDENT_H__

void showstudent(sqlite3 *db);
void showstudentmarks(sqlite3 *db);
void addstudent(sqlite3 *db);
void addmarks(sqlite3 *db);
void runchoice(int choice, sqlite3 *db);
void displaymenu(sqlite3 * db);

#endif // __STUDENT_H__ 
