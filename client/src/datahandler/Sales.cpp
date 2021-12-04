#include <iostream>
#include <Windows.h>
#include "datahandler/Sales.h"
#include <vector>

using namespace std;

vector<itemObj> shoppingCart;

class itemObj
{
    public:
     string name,sku;
    int price=0;

    itemObj(string x, string y, int z)
    {
        name = x;
        sku = y;
        price =z;
    }
    
    string getName()
    {
        return name;
    }
    string getSku()
    {
        return sku;
    }
    int getPrice()
    {
        return price;
    }
    
    void setName(string Name)
    {
        name = Name;
    }
    
    void setSku(string SKU)
    {
        sku = SKU;
    }
    
    void setPrice(int Price)
    {
        price = Price;
    }
    
};


int Sales::addToCart(std::string name, std::string sku, int price)
{
    itemObj newItem(name, sku, price);
    shoppingCart.push_back(newItem);
}

int Sales::removeFromCart(std::string SKU)
{

}

void Sales::clearCart()
{
    shoppingCart.clear();
}