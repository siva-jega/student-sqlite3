#ifndef __SQLUTILS_H__
#define __SQLUTILS_H__

int callback(void *NotUsed, int argc, char **argv, char **azColName);
sqlite3 * opendb();
void closedb(sqlite3 *db);
void runsql(sqlite3 *db, const char * sql);
void createtables(sqlite3 *db);

#endif // __SQLUTILS_H__ 