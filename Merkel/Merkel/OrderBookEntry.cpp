#include "OrderBookEntry.h"

bool OrderBookEntry::compareOrderTimestamp(OrderBookEntry& e1, OrderBookEntry& e2)
{
    return e1.timestamp < e2.timestamp;
}

bool OrderBookEntry::compareOrderPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
{
    return e1.price < e2.price;
}

bool OrderBookEntry::compareOrderPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
{
    return e1.price > e2.price;
}

OrderBookEntry :: OrderBookEntry(double price,
               double amount,
               std::string timestamp,
               std::string product,
               OrderBookType orderType,
               std::string username) : //Declarando aqui eu tenho em tempo de compilação
                                          price(price),
                                          amount(amount),
                                          timestamp(timestamp),
                                          product(product),
                                          orderType(orderType),
                                          username(username)
{
      }

OrderBookType OrderBookEntry::stringToOBT(std::string s)
{   
    OrderBookType ordertype;

    if (s == "bid") {
        ordertype = OrderBookType::bid;
    }
    else if (s == "ask") {
        ordertype = OrderBookType::ask;
    }
    else {
        ordertype = OrderBookType::unknown;
    }
    return ordertype;
}
