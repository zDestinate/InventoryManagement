#pragma once
#include <string>
#include <vector>
#include "lib/json.hpp"
using json = nlohmann::json;

class itemObj
{
    public:
    std::string name,sku;
    float price=0;

    itemObj(std::string x, std::string y, float z)
    {
        name = x;
        sku = y;
        price =z;
    }
    
    std::string getName()
    {
        return name;
    }
    std::string getSku()
    {
        return sku;
    }
    float getPrice()
    {
        return price;
    }
    
    void setName(std::string Name)
    {
        name = Name;
    }
    
    void setSku(std::string SKU)
    {
        sku = SKU;
    }
    
    void setPrice(float Price)
    {
        price = Price;
    }
    
};

class Sales {    
  private:
   
    
  public:

    std::vector<itemObj> shoppingCart;
    float total;
    std::string cartString;

    bool addToCart(json itemInfo);
    bool removeFromCart(std::string SKU);
    bool clearCart();
    void shoppingCartToString();
};

