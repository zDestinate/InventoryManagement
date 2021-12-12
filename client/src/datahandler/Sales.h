#pragma once
#include <string>
#include <vector>
#include "lib/json.hpp"
using json = nlohmann::json;

class itemObj
{
    public:
    std::string itemId,description,upc,quantity,price;

    itemObj(std::string itemId,std::string upc,std::string description, std::string quantity, std::string price)
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
    
    bool addItemToCart(std::string sku);
    bool removeFromCart(std::string SKU);
    bool clearCart();
    
    void demoItems();
    bool createDemoItem(std::string upc,std::string description,std::string quantity,std::string price);
    bool deleteDemoItem(std::string upc);

    void shoppingCartToString();
    bool getItemsData(json itemArray);
    
};

