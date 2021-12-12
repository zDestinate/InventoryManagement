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
    string id,description,quantity,upc,cost;

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
                cost = itemsArray[i].at("price").get<string>();
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

void Sales::demoItems()
{
    string itemId,description,upc,quantity,price;

    itemObj product("0","31512", "Black Crewneck T-shirt", "10","6.98");
    vItems.push_back(product);

    itemObj product1("1","91414", "White Crewneck T-shirt", "15","6.98");
    vItems.push_back(product1);

    itemObj product2("2","41051", "32x30 Mens Black Ripped Jeans","2", "29.99");
    vItems.push_back(product2);

    itemObj product3("3","51251", "28x30 Mens Skinny Jeans", "1","35.00");
    vItems.push_back(product3);

    itemObj product4("4","92151", "M SUPREME x Bape Hoodie", "17","99.99");
    vItems.push_back(product4);

    itemObj product5("5","91527", "PUMA Joggers", "15","18.99");
    vItems.push_back(product5);

    itemObj product6("6","51285", "Nike Sneakers", "5","149.99");
    vItems.push_back(product6);
}

bool Sales::addItemToCart(std::string upc)
{
    for(int i = 0; i < vItems.size(); i++)
    {
        if(vItems[i].upc == upc)
        {
            shoppingCart.push_back(vItems[i]);
            return true;
        }
    }
    return false;
}

bool Sales::createDemoItem(string upc,string description,string quantity,string price)
{  
    string strItemID = to_string(vItems.size());

    itemObj product(strItemID, upc, description, quantity, price);
    vItems.push_back(product);
    return true;
}

bool Sales::deleteDemoItem(std::string upc)
{   
    int position =0;

    if(vItems.size() == 0)
    {
        return false;
    }

    for(int i = 0; i < vItems.size(); i++)
    {
        if(vItems[i].upc == upc)
        {
            position = i;

            vItems.erase(vItems.begin()+position);
            return true;
        }
    }
    return false;
}

bool Sales::removeFromCart(std::string upc)
{
    int position =0;

    if(shoppingCart.size() == 0)
    {
        return false;
    }

    for(int i = 0; i < shoppingCart.size(); i++)
    {
        if(shoppingCart[i].upc == upc)
        {
            position = i;

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
        sentence += shoppingCart[i].description +","+shoppingCart[i].upc+","+shoppingCart[i].price;
        break;
        }
        sentence += shoppingCart[i].description +","+shoppingCart[i].upc+","+shoppingCart[i].price +",";
    }
    cartString = sentence;
}


