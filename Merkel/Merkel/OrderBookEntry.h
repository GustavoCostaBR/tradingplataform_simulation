#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

enum class OrderBookType
{
    bid,
    ask,
    sale,
    unknown
};

class OrderBookEntry
{

public:
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;

    static bool compareOrderTimestamp(OrderBookEntry& e1, OrderBookEntry& e2);

    static bool compareOrderPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2);

    static bool compareOrderPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2);

    OrderBookEntry(double price,
                   double amount,
                   std::string timestamp,
                   std::string product,
                   OrderBookType orderType);
    static OrderBookType stringToOBT(std::string s);
};
    