// Developed by Gustavo da Costa.
// 30/07/2023 - 01/08/2023 
// A simple menu for a cripto exchanging platform
#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"

double computeAveragePrice(std::vector<OrderBookEntry> &entries)
{
    double sum = 0;
    double avg = 0;
    int count = 0;
    for (auto entrie : entries)
    {
        sum = entrie.price + sum;
        ++count;
    }
    avg = sum / count;
    return avg;
}

double computeLowPrice(std::vector<OrderBookEntry> &entries)
{
    double temp = 1000000;
    for (auto entrie : entries)
    {
        if (entrie.price < temp)
        {
            temp = entrie.price;
        }
    }
    return temp;
}

double computeHighPrice(std::vector<OrderBookEntry> &entries)
{
    double temp = 0;
    for (auto entrie : entries)
    {
        if (entrie.price > temp)
        {
            temp = entrie.price;
        }
    }
    return temp;
}

double computePriceSpread(std::vector<OrderBookEntry> &entries)
{
    double spread;
    spread = computeHighPrice(entries) - computeLowPrice(entries);
    return spread;
}

int main(int argc, char **argv)
{
    
    // std::vector<double> prices;
    // std::vector<double> amounts;
    // std::vector<std::string> timestamps;
    
    // std::vector<std::string> products;
    // std::vector<OrderBookType> orderTypes;

    // prices.push_back(0.021873);
    // amounts.push_back(7.445649);
    // timestamps.push_back("17/03/2020  17:01:25");
    // products.push_back("ETH/BTC");
    // orderTypes.push_back(OrderBookType::bid);

    // std::cout << prices[0] << std::endl;

        
        MerkelMain app{};
        app.init();

    

        




        //     menu_printing();
        //     // Getting the user input
        //     int user_option;
        //     user_option = user_input();

        //     // Checking the user option
        //     verifying_option(user_option);
    
    // std::vector<OrderBookEntry> Orders;
    // OrderBookEntry order_temp{1000, 0.02, "17/03/2020  17:01:25", "ETH/BTC", OrderBookType::bid};
    // OrderBookEntry order
    // Orders.push_back(order_temp);
    // std::cout << Orders.at(0).price << std::endl; //With this I can catch specific errors
    // std::cout << Orders[0].price << std::endl; //This is the normal way

    // for (auto order : Orders) //Generally I can acces in this way. Any of the ways using for you are actually making a copy to order
    // for (OrderBookEntry &order : Orders) //It is the option to work in place, It does not make any copy
    // for (OrderBookEntry& order : Orders)
    //     {
    //     std::cout << order.price << std::endl;
    //     }



    // Orders.push_back(OrderBookEntry{0.021873, 7.445649, "17/03/2020  17:01:25", "ETH/BTC", OrderBookType::bid}); //Calling constructor directly

    // Orders.push_back(OrderBookEntry{0.021873, 3.467434, "17/03/2020  17:01:25", "ETH/BTC", OrderBookType::bid});

    // Orders.push_back(OrderBookEntry{0.02187305, 6.85567013, "17/03/2020  17:01:25", "ETH/BTC", OrderBookType::bid});

    // Orders.push_back(OrderBookEntry{0.02187305, 32.74659999, "17/03/2020  17:01:25", "ETH/BTC", OrderBookType::bid});

    // std::cout << "The average price is: " << computeAveragePrice(Orders) << std::endl;
    // std::cout << "The higher price is: " << computeHighPrice(Orders) << std::endl;
    // std::cout << "The lower price is: " << computeLowPrice(Orders) << std::endl;
    // std::cout << "The price spread is: " << computePriceSpread(Orders) << std::endl;



    // for (unsigned int i = 0; i < Orders.size(); ++i) //It is faster than i++ 
    //     {
    //         std::cout << Orders[i].price << std::endl;
    //     }

    // for (unsigned int i = 0; i < Orders.size(); ++i) //It is faster than i++
    //     {
    //         std::cout << Orders.at(i).price << std::endl;
    //     }

        return 0;
}