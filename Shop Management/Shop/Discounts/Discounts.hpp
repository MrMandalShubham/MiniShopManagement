#include <iostream>
#include "/home/dark/Desktop/Shop Management/Sqlite3/sqlite3.h"

using namespace std;

int discount_inDB;

class Discounts{

private:
  string discount_name;

protected:

public:

  Discounts(){
    this -> discount_name = "Not Mention";
  }

  Discounts(string discount_name){
    this -> discount_name = discount_name;
  }



  static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   // cout << data << endl;
   for(i = 0; i < argc; i++){
     cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
      // printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
   cout << endl;
   return 0;
  }



  static int callback_discount(void *data, int argc, char **argv, char **azColName){

    string val = argv[0];
    discount_inDB = stoi(val);
    // cout << azColName[0] << " => " << val << endl;
    return 0;

  }




  int AddInDiscountDB(string product_name ,int product_discount){
    // this -> allover_discount = allover_discount;
    sqlite3 * db;
    char * error;
    void * data;
    string sql_qurey;
    int DB;

    sqlite3_open("/home/dark/Desktop/Shop Management/Shop/Discounts/Discounts.db",&db);

    sql_qurey = "CREATE TABLE IF NOT EXISTS DiscountsDB("\
                "ProductName              TEXT PRIMARY KEY NOT NULL,"\
                "ProductDiscount         INT);";

    DB = sqlite3_exec(db, sql_qurey.c_str(), callback, data, &error);
    if(DB != SQLITE_OK){
      cout << " Creat Table Error : " << error << endl;
      return -1;
    }

    // cout << "Crate Table is Successful " << endl;

    sql_qurey = "INSERT INTO DiscountsDB(ProductName, ProductDiscount)"\
                "VALUES('" + product_name + "'," + to_string(product_discount) + ");";

    DB = sqlite3_exec(db, sql_qurey.c_str(), callback, data, &error);
    if(DB != SQLITE_OK){
      cout << " Insert Values Error : " << error << endl;
      sqlite3_free(error);
      return 0;
    }

    // cout << " Insert Values Successfully " << endl;
    sqlite3_close(db);
    return 1;
  }




  void UpdateInDiscountDB(string product_name, int product_discount){
    sqlite3 * db;
    char * error;
    void * data;
    string sql_qurey;
    int DB;

    sqlite3_open("/home/dark/Desktop/Shop Management/Shop/Discounts/Discounts.db",&db);

    sql_qurey = " UPDATE DiscountsDB SET"\
                " ProductDiscount = " + to_string(product_discount) + \
                " WHERE ProductName LIKE '" + product_name + "';";

    DB = sqlite3_exec(db, sql_qurey.c_str(), callback, data, &error);
    if(DB != SQLITE_OK){
      cout << " DataBase Update Error : " << error << endl;
      sqlite3_free(error);
      return;
    }

    // cout << " DataBase Update Successful " << endl;
    sqlite3_close(db);
    return;
  }



  int SelectInDiscountDB(string product_name){
    sqlite3 * db;
    char * error;
    void * data;
    string sql_qurey;
    int DB;

    sqlite3_open("/home/dark/Desktop/Shop Management/Shop/Discounts/Discounts.db",&db);

    sql_qurey = "SELECT ProductDiscount FROM DiscountsDB WHERE ProductName LIKE '" + product_name + "';";
    DB = sqlite3_exec(db, sql_qurey.c_str(), callback_discount, data, &error);
    if(DB != SQLITE_OK){
      cout << " Error to Select from DataBase : " << error << endl;
      sqlite3_free(error);
      return -1;
    }

    int overall_discount = discount_inDB;
    discount_inDB = 0;

    // cout << " Successfully Select from DataBase : " << overall_discount << endl;
    sqlite3_close(db);
    return overall_discount;
  }



  void DeleteInDiscountDB(string product_name){

    sqlite3 * db;
    char * error;
    void * data;
    string sql_qurey;
    int DB;

    sqlite3_open("/home/dark/Desktop/Shop Management/Shop/Discounts/Discounts.db",&db);

    sql_qurey = "DELETE FROM DiscountsDB WHERE product_name LIKE '" + product_name + "';";
    DB = sqlite3_exec(db,sql_qurey.c_str(), callback, data, &error);
    if(DB != SQLITE_OK){
      cout << " Error to Record Delete From Data Base : " << error << endl;
      sqlite3_free(error);
      return;
    }

    // cout << " Record Delete from DataBase Successfully " << endl;
    sqlite3_close(db);
    return;

  }



  void ViewInDiscountDB(){
    sqlite3 * db;
    char * error;
    void * data;
    string sql_qurey;
    int DB;

    sqlite3_open("/home/dark/Desktop/Shop Management/Shop/Discounts/Discounts.db",&db);

    sql_qurey = "SELECT * FROM DiscountsDB;";

    DB = sqlite3_exec(db, sql_qurey.c_str(), callback, data, &error);
    if(DB != SQLITE_OK){
      cout << " Error to View in Database : " << error << endl;
      sqlite3_free(error);
      return;
    }

    cout << "Done" << endl;
    sqlite3_close(db);
    return;

  }



  void ViewInDiscountDB(string product_name){
    sqlite3 * db;
    char * error;
    void * data;
    string sql_qurey;
    int DB;

    sqlite3_open("/home/dark/Desktop/Shop Management/Shop/Discounts/Discounts.db",&db);

    sql_qurey = " SELECT * FROM DiscountsDB WHERE ProductName LIKE '" + product_name + "';";

    DB = sqlite3_exec(db, sql_qurey.c_str(), callback, data, &error);
    if(DB != SQLITE_OK){
      cout << " Error to View in Database : " << error << endl;
      sqlite3_free(error);
      return;
    }

    cout << "Done" << endl;
    sqlite3_close(db);
    return;

  }



  void ProductDiscount(string product_name, int product_discount){

    int res = AddInDiscountDB(product_name, product_discount);
    if(res == 1){
      cout << "Product Successfully added " << endl;
      return;
    }

    UpdateInDiscountDB(product_name, product_discount);
    cout << "Product Successfully updated " << endl;
    return;
  }

};




// int main(int argc, char const *argv[]) {
//   Discounts Discount1("Big Sale Discounts");
//   Discount1.ProductDiscount("Orange", 20);    //product name and product discount  return 0;
//   Discount1.ProductDiscount("Apple", 30);
//   Discount1.ProductDiscount("Pine apple", 46);
//
//   Discount1.ProductDiscount("Orange",50);
//   // Discount1.SelectInDiscountDB("Apple");
//
//   // Discount1.ViewInDiscountDB();
//
//   Discount1.ViewInDiscountDB("Orange");
// }
