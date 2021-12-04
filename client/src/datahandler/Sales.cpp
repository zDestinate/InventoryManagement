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

    return "added to cart";
}

string Sales::removeFromCart(std::string SKU)
{

    return "added to cart";
}

string Sales::clearCart()
{
    shoppingCart.clear();
    return "added to cart";
}