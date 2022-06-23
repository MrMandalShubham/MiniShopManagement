#include<iostream>
#include "/home/dark/Desktop/Shop Management/Shop/OverAllValues/OverAllValues.hpp"
#include "/home/dark/Desktop/Shop Management/Shop/Cart/Cart.hpp"
using namespace std;



class MainCounter : public Cart , public OverAllValues{
private:
  string counter_name;
  // Cart cart;
public:
  MainCounter(){}

  MainCounter(string counter_name){
    this -> counter_name = counter_name;
  }

  void Checkout(Cart cart){

    int total_price = 0;
    cout << " Products Invoice Bill : " << endl;
    // cout << "Counter" << counter_name << endl;
    cout << " Product Name : Product Quantity  =>  Product Price" << endl;
    for(int i = 0; i < cart.Size(); i++){

      pair<int, int> product_overallvalues = ProductOverAllValues(cart.ProductName(i));

      cout << product_overallvalues.first << "  " << product_overallvalues.second << endl;

      int product_overallquantity = product_overallvalues.first;
      int product_overallprice = product_overallvalues.second;
      int product_payableprice = cart.ProductQuantity(i) * product_overallprice;
      cout << " " << cart.ProductName(i) << " : " << cart.ProductQuantity(i) << "  =>  " << product_payableprice << endl;
      total_price += product_payableprice;

    }

    cout << "____________________________________________________________________" << endl;
    cout << "Products Total Price : " << total_price << endl;
  }

};



// This is the main function of this whole store
int main(int argc, char const *argv[]) {

  // Set Products in Store
    Grocery Products1("Fruits");
    Products1.ProductAdd("chiku", 100, 80);
    Products1.ProductAdd("Apple", 100, 200);

    Grocery Products2("Oils");
    Products2.ProductAdd("Masted Oil", 100, 220);
    Products2.ProductAdd("Coconut Oil", 100, 180);

    Grocery Products3("Vages");
    Products3.ProductAdd("Bhindi", 30, 20);


  // Set Products Discount
    Discounts Discount1("Sales");
    Discount1.ProductDiscount("chiku", 50);
    Discount1.ProductDiscount("Apple", 50);
    Discount1.ProductDiscount("Bhindi", 10);

  MainCounter counter = MainCounter("Main Counter");

  Cart cart1 = Cart("Mr Dark");
  cart1.Add("chiku", 2);
  cart1.Add("Apple", 3);
  cart1.Add("Coconut", 5);
  cart1.Add("Bhindi", 2);
  cart1.Details();
  counter.Checkout(cart1);


  Cart cart2 = Cart("Mr Daitya");
  cart2.Add("chiku", 3);
  cart2.Add("Apple", 4);
  cart2.Add("Coc", 7);
  cart2.Add("Bhindi", 9);
  cart2.Details();
  counter.Checkout(cart2);

  return 0;
}
