
#include <stdio.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}
int query_str(char *str) 
{
    /*Check for the table presence*/
    /*If table not present create new one*/
    /*Create a query based on */
}
int main(int argc, char **argv){
  sqlite3 *db;
  char *zErrMsg = 0;
  char **result;
  char *sql = "select * from temp where id=3";
  char str[250];
  int rows = 0, cols=0;
  int rc;

  if( argc!=3 ){
    fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
    //return(1);
  }
  rc = sqlite3_open(argv[1], &db);
  if( rc ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return(1);
  }
  rc = sqlite3_get_table(db, sql, &result, &rows, &cols, &zErrMsg);
  if( rc!=SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  printf("id=%s min=%s max=%s avg=%s\n id=%s max=%s min=%s avg=%s\n", result[0], result[1],result[2],result[3],result[4],result[5], result[6], result[7]);
  int val = strtoul(result[7], NULL, 0);
  val += val + 1;
  sprintf(str, "insert into temp (id, max, min, avg) values (%s, %s, %s, %d);",
          result[4], result[5], result[6], val);
  printf("str=%s\n",str);
  rc = sqlite3_exec(db, str, callback, 0, &zErrMsg);
  if( rc!=SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  if( rc!=SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  sqlite3_free_table(result);
  sqlite3_close(db);
  return 0;
}
