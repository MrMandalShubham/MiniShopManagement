#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class Cart{
private:
  string cart_owner;
  vector<pair<string, int>> cart;
protected:
public:

  // Default Constracter
  Cart(){
    this -> cart_owner = "Not Mention";
  };

  // Constracter
  Cart(string cart_owner){

    this -> cart_owner = cart_owner;
  }

  void Add(string product_name, int product_quantity){
    pair<string, int> product;
    product.first = product_name;
    product.second = product_quantity;

    this -> cart.push_back(product);
  }

  int Size(){
    return this -> cart.size();
  }

  string ProductName(int i){
    if(i > this -> cart.size()){
      return "None";
    }
    return this -> cart[i].first;
  }

  int ProductQuantity(int i){
    if(i > this -> cart.size()){
      return 0;
    }
    return this -> cart[i].second;
  }

  void Details(){

    cout << " Cart Details of " << this -> cart_owner << endl;

    cout << " Product Name : " << "Product Quantity "<< endl;
    for(int i = 0; i < this -> cart.size(); i++){
      cout << " " << this -> cart[i].first << "\t\t" << this -> cart[i].second << endl;
    }

    cout << "____________________________________________________________________" << endl;

  }
};


// int main(int argc, char const *argv[]) {
//
//   Cart cart1 = Cart("Mr Mandal");
//   cart1.Add("p1",10);
//   cart1.Add("p2",20);
//   cart1.Add("p3",30);
//   cart1.Add("p4",40);
//
//   cart1.Details();
//
//   Cart cart2 = Cart("Mr Dark");
//   cart2.Add("p1",10);
//   cart2.Add("p2",20);
//   cart2.Add("p3",30);
//   cart2.Add("p4",40);
//
//   cart2.Details();
//
//   return 0;
// }
