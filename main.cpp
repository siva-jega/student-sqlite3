#include <sqlite3.h>
#include "sqlutils.h"
#include "student.h"

using namespace std;

int main(int argc, char *argv[])
{
  sqlite3 *db = opendb();
  displaymenu(db);
  closedb(db);
  return 0;
}
