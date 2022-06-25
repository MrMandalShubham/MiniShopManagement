#include <iostream>
#include <utility>
#include "/home/dark/Desktop/Shop Management/Store/Grocery/Grocery.hpp"
#include "/home/dark/Desktop/Shop Management/Shop/Discounts/Discounts.hpp"

using namespace std;

class OverAllValues : public Grocery , public Discounts{

private:

  // int product_overallprice;

public:
  // Default Counstructer
  OverAllValues(){}

  pair<int, int> ProductOverAllValues(string product_name){

    pair<int, int> product_values = SelectInDB(product_name);
    int product_overalldiscount = SelectInDiscountDB(product_name);

    cout << "product_overalldiscount " << product_overalldiscount << endl;

    int product_overallprice = product_values.second - (product_overalldiscount * product_values.second)/100;

    product_values.second = product_overallprice;
    // cout << product_values.first << "  " << product_values.second << endl;

    return product_values;
  }

};

// int main(int argc, char const *argv[]) {
//
//     // Store Products
//     {
//       Grocery Products1 = Grocery("Fruits");
//       Products1.ProductAdd("Orange", 100, 80);
//       Products1.ProductAdd("Apple", 100, 200);
//       Products1.ProductAdd("Mangoes", 200, 120);
//       Products1.ProductAdd("PineApple", 60, 150);
//     }
//
//
//     // Set Discounts
//     {
//       Discounts D1("Big Sales Day");
//       D1.ProductDiscount("Orange", 50);
//       D1.ProductDiscount("Mangoes", 10);
//       D1.ProductDiscount("Apple", 50);
//       // D1.ProductDiscount("Apple",0);
//       // D1.ViewInDiscountDB();
//       D1.ViewInDiscountDB("Mangoes");
//     }
//
//   OverAllValues ProductValues;
//   pair<int, int> values = ProductValues.ProductOverAllValues("Orange");
//   cout << values.first << "  " << values.second << endl;
//
//   return 0;
// }
