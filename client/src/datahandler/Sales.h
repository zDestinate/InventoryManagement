#pragma once
#include <string>
#include <vector>

class itemObj
{
    public:
    std::string name,sku;
    int price=0;

    itemObj(std::string x, std::string y, int z)
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
    int getPrice()
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
    
    void setPrice(int Price)
    {
        price = Price;
    }
    
};

class Sales {    
  private:
   
    
  public:

    std::vector<itemObj> shoppingCart;

    Sales();
    int addToCart(std::string name, std::string sku, int price);
    int removeFromCart(std::string SKU);
    void clearCart();
};

