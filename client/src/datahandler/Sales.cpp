#include <iostream>
#include <Windows.h>
#include "datahandler/Sales.h"
#include <vector>

using namespace std;

Sales::Sales()
{
    
}


int Sales::addToCart(std::string name, std::string sku, int price)
{
    itemObj newItem(name, sku, price);
    shoppingCart.push_back(newItem);

    return 0;
}

int Sales::removeFromCart(std::string SKU)
{

    return 0;
}

void Sales::clearCart()
{
    shoppingCart.clear();
}