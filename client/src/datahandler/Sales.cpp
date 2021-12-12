#include <iostream>
#include <Windows.h>
#include "datahandler/Sales.h"
#include <vector>
#include "lib/json.hpp"

using namespace std;
using json = nlohmann::json;


bool Sales::getItemsData(json itemsArray)
{
    //'/inventory/create/:desc/:cost/:quant/:Upc'
    string id,description,quantity,upc;
    float cost;

    if(itemsArray.is_array())
    {
        for(int i = 0; i < itemsArray.size(); i++)
        {   
            if(itemsArray[i].contains("_id"))
            {
                id = itemsArray[i].at("_id").get<string>();
            } 
            
            if(itemsArray[i].contains("desc"))
            {
                description = itemsArray[i].at("desc").get<string>();
            } 

            if(itemsArray[i].contains("price"))
            {
                cost = itemsArray[i].at("price").get<float>();
            } 

            if(itemsArray[i].contains("quantity"))
            {
                quantity = itemsArray[i].at("quantity").get<string>();
            } 

            if(itemsArray[i].contains("upc"))
            {
                upc = itemsArray[i].at("upc").get<string>();
            } 
            itemObj item(id,upc,description,quantity,cost);
            vItems.push_back(item);
        }
    }    

    return false;
}

/*
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
*/

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
        sentence += shoppingCart[i].description +","+shoppingCart[i].upc+","+to_string(shoppingCart[i].price);
        break;
        }
        sentence += shoppingCart[i].description +","+shoppingCart[i].upc+","+to_string(shoppingCart[i].price)+",";
    }
    cartString = sentence;
}


