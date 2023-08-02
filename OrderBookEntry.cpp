#include "OrderBookEntry.h"

OrderBookEntry :: OrderBookEntry(double price,
               double amount,
               std::string timestamp,
               std::string product,
               OrderBookType orderType) : //Declarando aqui eu tenho em tempo de compilação
                                          price(price),
                                          amount(amount),
                                          timestamp(timestamp),
                                          product(product),
                                          orderType(orderType)
{
      }