#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"

// MerkelMain::MerkelMain(){
// } //Não preciso chamar dnv se estabeleci como padrão no .h

void MerkelMain::init(){

    loadOrderBook();
    int user_option;
    while (true)
    {
        menu_printing();
        user_option = user_input();
        verifying_option(user_option);
    }
}

void MerkelMain::loadOrderBook(){

    
    Orders.push_back(OrderBookEntry{0.021873, 7.445649, "17/03/2020  17:01:25", "ETH/BTC", OrderBookType::bid}); //Calling constructor directly

    Orders.push_back(OrderBookEntry{0.021873, 3.467434, "17/03/2020  17:01:25", "ETH/BTC", OrderBookType::bid});

    Orders.push_back(OrderBookEntry{0.02187305, 6.85567013, "17/03/2020  17:01:25", "ETH/BTC", OrderBookType::bid});

    Orders.push_back(OrderBookEntry{0.02187305, 32.74659999, "17/03/2020  17:01:25", "ETH/BTC", OrderBookType::bid});

    // std::cout << "The average price is: " << computeAveragePrice(Orders) << std::endl;
    // std::cout << "The higher price is: " << computeHighPrice(Orders) << std::endl;
    // std::cout << "The lower price is: " << computeLowPrice(Orders) << std::endl;
    // std::cout << "The price spread is: " << computePriceSpread(Orders) << std::endl;
}

void MerkelMain::menu_printing()
{
    // Printing on the screen the options
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Print ask" << std::endl;
    std::cout << "4: Print bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
}

int MerkelMain::user_input()
{
    // Getting the user input
    int user_option;
    std::cout << "Choose among the options typing 1-6" << std::endl;
    std::cin >> user_option;
    return user_option;
}

void MerkelMain::P_help()
{
    std::cout << "\nHelp - choose options from the menu" << std::endl;
    std::cout << "and follow the on screen instructions." << std::endl;
}

void MerkelMain::P_stats()
{
    std::cout << "\nOrderBook contains: " << Orders.size() << " entries." << std::endl;
}

void MerkelMain::P_ask()
{
    std::cout << "\nYou chose Ask" << std::endl;
}

void MerkelMain::P_bid()
{
    std::cout << "\nYou chose Bid" << std::endl;
}

void MerkelMain::P_wallet()
{
    std::cout << "\nYou chose Wallet" << std::endl;
}

void MerkelMain::go_to_next_frame()
{
    std::cout << "\nYou chose Continue" << std::endl;
}

void MerkelMain::verifying_option(int user_option)
{
    // Checking the user option
    if (std::cin.fail() || user_option < 1 || user_option > 6)
    {
        std::cout << "\nInvalid input. Please enter a valid integer number from 1 to 6." << std::endl;
        std::cin.clear();           // If it fail, clear the fail state
        std::cin.ignore(256, '\n'); // Ignore what comes after
    }
    else
    {
        switch (user_option)
        {
        case 1:
            P_help();
            break;
        case 2:
            P_stats();
            break;
        case 3:
            P_ask();
            break;
        case 4:
            P_bid();
            break;
        case 5:
            P_wallet();
            break;
        case 6:
            go_to_next_frame();
            break;
        }
    }
}