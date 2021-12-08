#include <iostream>
#include <Windows.h>
#include "datahandler/Sales.h"
#include <vector>

using namespace std;

Sales::Sales()
{
    
}


string Sales::addToCart(std::string name, std::string sku, int price)
{
    itemObj newItem(name, sku, price);
    shoppingCart.push_back(newItem);

    return "item added to cart";
}

string Sales::removeFromCart(std::string SKU)
{

    return "item removed from cart";
}

string Sales::clearCart()
{
    shoppingCart.clear();
    return "cart cleared";
}