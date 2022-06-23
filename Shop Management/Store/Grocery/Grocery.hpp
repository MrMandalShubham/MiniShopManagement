#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "/home/dark/Desktop/Shop Management/Sqlite3/sqlite3.h"

using namespace std;

static int product_availableInDB;
static int product_priceInDB;

struct VALUES{

  string product_category;
  string product_name;
  int product_available;
  int product_price;

  VALUES(){}

  VALUES(string product_category, string product_name, int product_available, int product_price){

    this -> product_category = product_category;
    this -> product_name = product_name;
    this -> product_available = product_available;
    this -> product_price = product_price;

  }

};

class Grocery{

private:
  vector<VALUES*> Grocery_Products;
  string product_category;

public:

  Grocery(){
  }

  Grocery (string product_category){
    this -> product_category = product_category;
  }



  // Callback fuction
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



 static int callback_price(void *data, int argc, char **argv, char **azColName){

   string val = argv[0];
   product_priceInDB = stoi(val);
   // cout << azColName[0] << " => " << val << endl;
   return 0;

 }

 static int callback_available(void *data, int argc, char **argv, char **azColName){

   string val = argv[0];
   product_availableInDB = stoi(val);
   // cout << azColName[0] << " => " << val << endl;
   return 0;

 }



  // Add values in database
  void AddInDB(string product_name, int product_available, int product_price){

    sqlite3 * db;
    char * error;
    string sql;
    string sql_qurey;
    int DB;
    void * data;

    sqlite3_open("/home/dark/Desktop/Shop Management/Store/Grocery/Grocery.db", &db);

    sql =  "CREATE TABLE IF NOT EXISTS GroceryProducts("\
            "ProductName         TEXT PRIMARY KEY NOT NULL,"\
            "ProductAvailable    INT,"\
            "ProductPrice        INT );";

    DB = sqlite3_exec(db, sql.c_str(), callback, data, & error);

    if(DB != SQLITE_OK){
      // cout << "SQL Exsicution Error : " << error << endl;
      // sqlite3_free(error);
      return;
    }

    // cout << "Create Table Successfully" << endl;

    sql_qurey = "INSERT INTO GroceryProducts (ProductName, ProductAvailable, ProductPrice)"\
                "VALUES('" + product_name + "'," + to_string(product_available) + "," + to_string(product_price) + ");";

    DB = sqlite3_exec(db, sql_qurey.c_str(), NULL, 0, & error);

    if(DB != SQLITE_OK){
      // cout << " SQL Inserting Error :" << error << endl;
      // sqlite3_free(error);
      return;
    }
    // cout << "Insert records Successfully" << endl;
    sqlite3_close(db);
    return;
  }



  // Update Database
  void UpdateInDB(string product_name, int product_available, int product_price){
    sqlite3 * db;
    char * error;
    void * data;
    string sql_qurey;
    int DB;

    sqlite3_open("/home/dark/Desktop/Shop Management/Store/Grocery/Grocery.db", &db);

    sql_qurey = " UPDATE GroceryProducts SET"\
                " ProductAvailable = " + to_string(product_available) + ","\
                " ProductPrice = " + to_string(product_price) + \
                " WHERE ProductName = '" + product_name + "';";

    // sql_qurey = "UPDATE GroceryProducts set ProductAvailable = 500 WHERE ProductName = 'Orange';"

    DB = sqlite3_exec(db, sql_qurey.c_str(), callback, data, & error);
    if(DB != SQLITE_OK){
      // cout << " Error to Update Data in DataBase : " << error << endl;
      return;
    }

    // cout << " Update Data Successfully in DataBase." << endl;

    sqlite3_close(db);
    return;
  }



  void DeleteInDB(string product_name){
    sqlite3 * db;
    char * error;
    void * data;
    string sql_qurey;
    int DB;

    sqlite3_open("/home/dark/Desktop/Shop Management/Store/Grocery/Grocery.db", &db);

    sql_qurey = "DELETE FROM GroceryProducts WHERE ProductName = '" + product_name + "';";

    DB = sqlite3_exec(db, sql_qurey.c_str(), callback, data, & error);
    if(DB != SQLITE_OK){
      cout << "Error to Delete Data from DataBase : " << endl;
      return;
    }

    cout << " Successfully Delete Data from Data Base." << endl;
    sqlite3_close(db);
    return;

  }


  //select from database
  pair<int,int> SelectInDB(string product_name){
    sqlite3 * db;
    char * error;
    void * data;
    string sql;
    string sql_qurey;
    int DB;
    pair<int, int> values;

    sqlite3_open("/home/dark/Desktop/Shop Management/Store/Grocery/Grocery.db", &db);

    sql_qurey = "SELECT ProductAvailable FROM GroceryProducts WHERE ProductName LIKE '" +  product_name +  "' ";
    DB = sqlite3_exec(db, sql_qurey.c_str(), callback_available, data, & error);
    if(DB != SQLITE_OK){
      // cout << "Data Selection Error : " << error << endl;
      // sqlite3_free(error);
      values.first = 0;
    }
    values.first = product_availableInDB;
    product_availableInDB = 0;

    sql_qurey = "SELECT ProductPrice FROM GroceryProducts WHERE ProductName LIKE '" +  product_name +  "' ";
    DB = sqlite3_exec(db, sql_qurey.c_str(), callback_price, data, & error);
    if(DB != SQLITE_OK){
      // cout << "Data Selection Error : " << error << endl;
      // sqlite3_free(error);
      values.second = 0;
    }
    values.second = product_priceInDB;
    product_priceInDB = 0;

    // cout << values.first << " " << values.second << endl;
    return values;
  }

  // View database
  void ViewInDB(){
    sqlite3 * db;
    char * error;
    void * data;
    string sql;
    string sql_qurey;
    int DB;

    sqlite3_open("/home/dark/Desktop/Shop Management/Store/Grocery/Grocery.db", &db);

    sql_qurey = "SELECT * FROM GroceryProducts";

    DB = sqlite3_exec(db, sql_qurey.c_str(), callback, data, & error);

    if(DB != SQLITE_OK){
      // cout << "Error to Select data " << error << endl;
      sqlite3_free(error);
      return;
    }

    // cout << "Select Data Successfully " << endl;
    return;
  }



  // Add product in Grocery
  void ProductAdd(string product_name, int product_available, int product_price){

    AddInDB(product_name, product_available, product_price);
    VALUES * product_values = new VALUES(product_category, product_name, product_available, product_price);
    this -> Grocery_Products.push_back(product_values);

  }

  // Get ProductPrice
  int ProductPrice(string product_name){
    int product_idx = -1;
    for(int i = 0; i < this -> Grocery_Products.size(); i++){

      if(product_name == this -> Grocery_Products.at(i) -> product_name){
        product_idx = i;
        break;
      }
      continue;
    }

    if(product_idx != -1){
      return this -> Grocery_Products.at(product_idx) -> product_price;
    }
    return 0;
  }

  // ProductAvailablity
  int ProductAvailable(string product_name){
    int product_idx = -1;
    for(int i = 0; i < this -> Grocery_Products.size(); i++){

      if(product_name == this -> Grocery_Products.at(i) -> product_name){
        product_idx = i;
        break;
      }
      continue;
    }

    if(product_idx != -1){
      return this -> Grocery_Products.at(product_idx) -> product_available;
    }
    return 0;
  }

  // print out all product Details
  void Details(){

    cout << "Grocery Products Details" << endl;

    for(int i = 0; i < this -> Grocery_Products.size(); i++){

    cout << " Product Category : " << this -> Grocery_Products[i] -> product_category << endl;
    cout << " Product Name : " << this -> Grocery_Products[i] -> product_name << endl;
    cout << " Product Avaliable : " << this -> Grocery_Products[i] -> product_available << endl;
    cout << " Product Price : " << this -> Grocery_Products[i] -> product_price << endl;
    cout << endl;

    }
    return;
  }

  // Print Details Of Product
  void Details(string product_name){

    int product_idx = -1;
    for(int i = 0; i < Grocery_Products.size(); i++){

      if(product_name == Grocery_Products.at(i) -> product_name){
        product_idx = i;
        break;
      }
      continue;
    }
    if(product_idx != -1){
      cout << " Product Category : " << this -> Grocery_Products.at(product_idx) -> product_category << endl;
      cout << " Product Name : " << this -> Grocery_Products.at(product_idx) -> product_name << endl;
      cout << " Product Avaliable : " << this -> Grocery_Products.at(product_idx) -> product_available << endl;
      cout << " Product Price : " << this -> Grocery_Products.at(product_idx) -> product_price << endl;
      cout << endl;
    }
    else{
      cout << " Product is Not Avaliable in Store :(" << endl;
      cout << endl;
    }
    return;
  }

};


// int main(int argc, char const *argv[]) {
//
//   Grocery Products1 = Grocery("Fruits");
//   Products1.ProductAdd("Orange", 100, 80);
//   Products1.ProductAdd("Apple", 100, 200);
//   Products1.ProductAdd("Mangoes", 200, 120);
//   Products1.ProductAdd("PineApple", 60, 150);
//
//   Grocery Products2 = Grocery("Oils");
//   Products2.ProductAdd("Masted Oil", 100, 220);
//   Products2.ProductAdd("Coconet Oil", 100, 180);
//
//   Grocery products3 = Grocery("Powders");
//   products3.ProductAdd("Haldi Powder", 20, 50);
//   products3.ProductAdd("kasmiri lal mrich Powder", 40, 100);
//
//
//   // Products1.Details(); // Show all Avaliable Products Details
//   // Products1.Details("Mangoes"); // Show Orange Details
//   Products1.ViewInDB();
//   Products1.DeleteInDB("Mangoes");
//   Products1.ViewInDB();
//   // Products1.Details("Apple"); // Show Orange Details
//   // Products1.Details("Mango");
//   // Products2.Details("Masted Oil");
//   // cout << Products1.ProductPrice("Orange") << endl; // return product Price
//   // cout << Products1.ProductAvailable("Orange") << endl;
//   // Products1.Update();
//
//   // Products1.ViewInDB();
//   // Products1.SelectInDB("Mangoes");
//   // Products2.SelectInDB("Masted oil");
//
//   return 0;
//
// }
