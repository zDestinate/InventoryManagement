#include <iostream>
#include <Windows.h>
#include "datahandler/Inventory.h"

double price = 0;
int quantity = 0;
string productname,widxlen,description,empName,empID,empPosition; 

void Inventory::getProductData(string sku)
{
    price = 0, quantity = 0;
    EstablishConnection();
	string product = ConnectTo("/gvhjgvjhgvjhg");
	json productjson = json::parse(product);

     price = 29.99;
     quantity = 12;
     productname = "Dark Blue Men's Jeans";
     description = "Dark blue jeans for men";
     widxlen ="34x30";   

     
}

string Inventory::inventoryOrder()
{
    EstablishConnection();
	string invenOrder = ConnectTo("/gvhjgvjhgvjhg");
	json invenOrderjson = json::parse(invenOrder);

    return "sga";
}