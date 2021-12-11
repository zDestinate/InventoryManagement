#include <iostream>
#include <Windows.h>
#include "datahandler/Sales.h"
#include <vector>
#include "lib/json.hpp"

using namespace std;
using json = nlohmann::json;

/*
bool getallItems(json itemsArray)
{
    //'/inventory/create/:desc/:cost/:quant/:Upc'
    string description,cost,quantity,upc;

    if(itemsArray.is_array())
    {
        for(int i = 0; i < itemsArray.size(); i++)
        {
            if(itemsArray[i].contains("desc"))
            {
                description = itemsArray[i].at("desc").get<string>();
            } 

            if(itemsArray[i].contains("cost"))
            {
                cost = itemsArray[i].at("cost").get<string>();
            } 

            if(itemsArray[i].contains("quant"))
            {
                quantity = itemsArray[i].at("quant").get<string>();
            } 

            if(itemsArray[i].contains("upc"))
            {
                upc = itemsArray[i].at("upc").get<string>();
            } 
            itemObj item(description,cost,upc);
        }
    }    

    return false;
}


bool Sales::addToCart(json itemInfo)
{
    string name,sku;
    float price;
    
    if(itemInfo.is_array()){
        name = itemInfo[0].at("code").get<string>();
        sku = itemInfo[1].at("code").get<string>();
        price = stof(itemInfo[2].at("code").get<string>());
        
        total += price;

        itemObj newItem(name, sku, price);
        shoppingCart.push_back(newItem);

        return true;
    }

    return false;
}
*/
bool Sales::removeFromCart(std::string sku)
{
    int position =0;

    if(shoppingCart.size() == 0)
    {
        return false;
    }

    for(int i = 0; i < shoppingCart.size(); i++)
    {
        if(shoppingCart[i].getSku() == sku)
        {
            position = i;

            total -= shoppingCart[i].getPrice();
            shoppingCart.erase(shoppingCart.begin()+position);
            return true;
        }
    }
    return false;
}

bool Sales::clearCart()
{
    shoppingCart.clear();
    total = 0;
    return "cart cleared";
}

void Sales::shoppingCartToString()
{
    std::string sentence;
    for(int i  = 0; i < shoppingCart.size(); i++){
        if(i == shoppingCart.size()-1)
        {
        sentence += shoppingCart[i].getName() +","+shoppingCart[i].getSku()+","+to_string(shoppingCart[i].getPrice());
        break;
        }
        sentence += shoppingCart[i].getName() +","+shoppingCart[i].getSku()+","+to_string(shoppingCart[i].getPrice())+",";
    }
    cartString = sentence;
}


