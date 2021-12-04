#pragma once
#include <string>


class Sales {    
  private:
    
    
  public:

  std::string item;
  int addToCart(std::string name, std::string sku, int price);
  int removeFromCart(std::string SKU);
  void clearCart();
};