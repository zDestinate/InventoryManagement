#pragma once
#include <string>
#include <vector>
#include "lib/json.hpp"
using json = nlohmann::json;

class itemObj
{
    public:
    std::string itemId,description,upc,quantity;
    float price=0;

    itemObj(std::string itemId,std::string upc,std::string description, std::string quantity, float price)
    {   
        this->itemId = itemId;
        this->upc = upc;
        this->description = description;
        this->quantity = quantity;
        this->price =price;
    }
};

class Sales {    
  private:
   
    
  public:

    std::vector<itemObj> shoppingCart;
    std::vector<itemObj> vItems;
    float total;
    std::string cartString;

    bool getallItems(json dataSon);
    //bool addToCart(string sku);
    // bool removeFromCart(std::string SKU);
    bool clearCart();
    void shoppingCartToString();
    bool getItemsData(json itemArray);
    
};

