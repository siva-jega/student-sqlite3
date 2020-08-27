#include <iostream>
#include <sqlite3.h>

using namespace std;

int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
  cout << "**********************************" << endl;
  for (int i = 0; i < argc; i++)
  {
    cout << azColName[i] << " : " << (argv[i] ? argv[i] : "NULL") << endl;
  }
  cout << "**********************************" << endl;
  return 0;
}

sqlite3 *opendb()
{
  /* Open database */
  sqlite3 *db;
  int ret_code = sqlite3_open("test.db", &db);
  if (ret_code)
  {
    cerr << "[Error]: Can't open database: " << sqlite3_errmsg(db) << endl;
    return NULL;
  }
  cout << "[Info] Opened database successfully" << endl;
  return db;
}

void closedb(sqlite3 *db)
{
  sqlite3_close(db);
}

void runsql(sqlite3 *db, const char *sql)
{
  char *zErrMsg = 0;
  /* Execute SQL statement */
  int ret_code = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  if (ret_code != SQLITE_OK)
  {
    cerr << "[Error] SQL error: " << zErrMsg << endl;
    sqlite3_free(zErrMsg);
  }
}