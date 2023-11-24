#include "MerkelMain.h"




// MerkelMain::MerkelMain(){
// } //Não preciso chamar dnv se estabeleci como padrão no .h

void MerkelMain::init(){

    
    int user_option;
       
    currentTime = orderBook.getEarliestTime();
    
    P_wallet();
    wallet.insertCurrency("BTC", 10.0);
    wallet.insertCurrency("ETH", 20.0);
    P_wallet();
    wallet.insertCurrency("BTC", 10.0);
    P_wallet();
    try {
        wallet.insertCurrency("ETH", -20.0);
    }
    catch (const std::runtime_error& e) {
        // Catch the exception and print the custom message
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    P_wallet();
    wallet.removeCurrency("BTC", 30.00);
    P_wallet();
    wallet.removeCurrency("BTC", 20.00);
    P_wallet();
    try {
        wallet.removeCurrency("ETH", -20.0);
    }
    catch (const std::runtime_error& e) {
        // Catch the exception and print the custom message
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    P_wallet();
    wallet.containsCurrency("ETH", 10.00);
    P_wallet();
    wallet.containsCurrency("ETH", 30.00);
    P_wallet();
    
    
    /*P_stats(0);
    while (true)
    {
        menu_printing();
        user_option = user_input();
        verifying_option(user_option);
    }*/
}

    // std::cout << "The average price is: " << computeAveragePrice(Orders) << std::endl;
    // std::cout << "The higher price is: " << computeHighPrice(Orders) << std::endl;
    // std::cout << "The lower price is: " << computeLowPrice(Orders) << std::endl;
    // std::cout << "The price spread is: " << computePriceSpread(Orders) << std::endl;


void MerkelMain::menu_printing()
{
    // Printing on the screen the options
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Print ask" << std::endl;
    std::cout << "4: Print bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
    std::cout << "=========================" << std::endl;
    std::cout << "Current time is: " << currentTime << std::endl;
}

int MerkelMain::user_input()
{
    // Getting the user input
    int user_option = 0;
    std::string line;
    std::cout << "\nChoose among the options typing 1-6" << std::endl;
    std::getline(std::cin, line);
    try {
        user_option = std::stoi(line);
    }
    catch (const std::exception& e) {
        std::cout << "MerkelMain::user_input Bad input! " << std::endl;
    }
    
    return user_option;
}

void MerkelMain::P_help()
{
    std::cout << "\nHelp - choose options from the menu" << std::endl;
    std::cout << "and follow the on screen instructions." << std::endl;
}

//std::vector <double> MerkelMain::stats()
//{
//    for (std::string const p : orderBook.getKnownProducts()) {
//        std::cout << "Product: " << p << std::endl;
//        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
//            p, CurrentTime);
//
//        std::vector<OrderBookEntry> entries2 = orderBook.getOrders(OrderBookType::bid,
//            p, CurrentTime);
//
//        std::vector <double> calculated_values;
//
//        double maxask = OrderBook::getHighPrice(entries);
//        calculated_values.push_back(maxask);
//        
//        double minask = OrderBook::getLowPrice(entries);
//        calculated_values.push_back(minask);
//
//        double maxbid = OrderBook::getHighPrice(entries2);
//        
//        double minbid = OrderBook::getLowPrice(entries2);
//        
//        double spread;
//
//        spread = OrderBook::getSpread(entries, entries2);
//
//        }
//
//}

void MerkelMain::P_stats(int a)
{   
    std::vector<std::string> products = (orderBook.getKnownProducts());
    int j = 0;
    for (std::string const p : products) {
        std::cout << "Product: " << p << std::endl;
        
        if (stringToNumber.size() < products.size()) {
            stringToNumber[p] = j;
            j++;

        }
        
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
            p, currentTime);
        //std::cout << "AAAAAAAAAAAAAAAAA" << std::endl;

        std::vector<OrderBookEntry> entries2 = orderBook.getOrders(OrderBookType::bid,
            p, currentTime);
        //std::cout << "BBBBBBBBBBBBBBBBB" << std::endl;
        
        if (entries.size() > 0) {
            double maxask = OrderBook::getHighPrice(entries);

            //std::cout << "ZZZZZZZZZZZZZZZZZZZZZ" << std::endl;

            double minask = OrderBook::getLowPrice(entries);

            double maxbid = OrderBook::getHighPrice(entries2);

            double minbid = OrderBook::getLowPrice(entries2);

            double spread;

            spread = OrderBook::getSpread(entries, entries2);



            if (max_since_start.size() < products.size()) {
                for (int e = 0; e < products.size(); ++e) {
                    max_since_start.push_back(0);
                    min_since_start.push_back(std::numeric_limits<double>::max());
                }
            }



            max_since_start = orderBook.get_max_since_start(entries, entries2, p, max_since_start, stringToNumber);

            //std::cout << "CCCCCCCCCCCCCCCCCCC" << std::endl;

            min_since_start = orderBook.get_min_since_start(entries, entries2, p, min_since_start, stringToNumber);

            //std::cout << "DDDDDDDDDDDDDDDDDDD" << std::endl;


            if (a == 1) {
                std::cout << "Asks seen: " << entries.size() << std::endl;
                std::cout << "Bids seen: " << entries2.size() << std::endl;
                std::cout << "The maximum ask value is: " << maxask << std::endl;
                std::cout << "The minimum ask value is: " << minask << std::endl;
                std::cout << "The maximum bid value is: " << maxbid << std::endl;
                std::cout << "The minimum bid value is: " << minbid << "\n" << std::endl;
                std::cout << "The spread value is: " << spread << "\n" << std::endl;
                std::cout << "The Highest value since the program started is: " << max_since_start[stringToNumber[p]] << "\n" << std::endl;
                std::cout << "The lowest value since the program started is: " << min_since_start[stringToNumber[p]] << "\n" << std::endl;
            }
        }
    }

    /*std::cout << "\nOrderBook contains: " << Orders.size() << " entries." << std::endl;
    unsigned int bids = 0;
    unsigned int asks = 0;
    for (auto& ord : Orders) {
        if (ord.orderType == OrderBookType::bid) {
            bids++;
        }
        else if (ord.orderType == OrderBookType::ask) {
            asks++;
        }
        
    }
    std::cout << "There are " << bids << " bids in the order book;" << std::endl;
    std::cout << "There are " << asks << " asks in the order book;" << std::endl;*/
}

void MerkelMain::P_ask()
{
    std::cout << "\nYou chose Ask, enter the amount following the format: product, price, amount, eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
   // Treatment only to cin as the first input
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);
    std::cout << "You typed: " << input << std::endl;
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    //std::cout << "O VALOR DO TOKEN PRODUTO É: " << tokens[0] << std::endl;
    if (tokens.size() != 3) {
        /*std::cout << tokens[0] << std::endl;
        std::cout << tokens[1] << std::endl;
        std::cout << tokens[2] << std::endl;*/
        std::cout << "MerkelMain::P_ask Bad input! (The input must be like the eg) " << input << std::endl;
    }
    else {
        /*std::cout << tokens[0] << std::endl;
        std::cout << tokens[1] << std::endl;
        std::cout << tokens[2] << std::endl;*/
        std::string invertedToken = CSVReader::invertPair(tokens[0]);
        
        auto result = stringToNumber.find(tokens[0]);
        auto result2 = stringToNumber.find(invertedToken);

        if (result != stringToNumber.end()) {
            try {
                std::cout << "came so far 0" << std::endl;
                OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::ask);
                std::cout << "came so far 1" << std::endl;
                if (wallet.canFulfillOrder(obe)) {
                    std::cout << "Wallet looks good. " << std::endl;
                    orderBook.insertNewOrder(obe);
                }
                else {
                    std::cout << "Wallet has insuficient funds. " << std::endl;
                }
                
            }
            catch (const std::exception& e) {
                std::cout << "MerkelMain::P_ask Bad input! " << std::endl;
            }
        }
        // If an BTC/ETH pair does not exist in my order book the program will not crash, it will convert the BTC/ETH ask to an ETH/BTC bid, correcting the prices and amounts
        else if (result2 != stringToNumber.end()) {

            try {
                std::cout << "came so far 0" << std::endl;
                std::string temporaryPrice = std::to_string(1.0 / (std::stod(tokens[1])));
                std::string temporaryAmount = std::to_string((std::stod(tokens[1]) * std::stod(tokens[2])));

                OrderBookEntry obe = CSVReader::stringsToOBE(temporaryPrice, temporaryAmount, currentTime, invertedToken, OrderBookType::bid);
                std::cout << "came so far 1" << std::endl;
                if (wallet.canFulfillOrder(obe)) {
                    std::cout << "Wallet looks good. " << std::endl;
                    orderBook.insertNewOrder(obe);
                    std::cout << "came so far 2" << std::endl;
                }
                else {
                    std::cout << "Wallet has insuficient funds. " << std::endl;
                }

            }
            catch (const std::exception& e) {
                std::cout << "MerkelMain::P_ask Bad input! " << std::endl;
            }

        }
        else {
            std::cout << "came so far 0" << std::endl;
            std::cout << "MerkelMain::P_ask Bad input for product! " << std::endl;
        }
        }

}

void MerkelMain::P_bid()
{
    std::cout << "\nYou chose Bid, enter the amount following the format: product, price, amount, eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    // Treatment only to cin as the first input
     // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);
    std::cout << "You typed: " << input << std::endl;
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) {
        std::cout << "MerkelMain::P_bid Bad input! (The input must be like the eg) " << input << std::endl;
    }
    else {
        auto result = stringToNumber.find(tokens[0]);
        
        std::string invertedToken = CSVReader::invertPair(tokens[0]);

        auto result2 = stringToNumber.find(invertedToken);
        
        
        if (result != stringToNumber.end()) {
            try {
                OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::bid);
                orderBook.insertNewOrder(obe);
                if (wallet.canFulfillOrder(obe)) {
                    std::cout << "Wallet looks good. " << std::endl;
                    orderBook.insertNewOrder(obe);
                    std::cout << "came so far 2" << std::endl;
                }
                else {
                    std::cout << "Wallet has insuficient funds. " << std::endl;
                }
            }
            catch (const std::exception& e) {
                std::cout << "MerkelMain::P_bid Bad input! " << std::endl;
            }
        }

        else if (result2 != stringToNumber.end()) {

            try {
                std::cout << "came so far 0" << std::endl;
                std::string temporaryPrice = std::to_string(1.0 / (std::stod(tokens[1])));
                std::string temporaryAmount = std::to_string((std::stod(tokens[1]) * std::stod(tokens[2])));

                OrderBookEntry obe = CSVReader::stringsToOBE(temporaryPrice, temporaryAmount, currentTime, invertedToken, OrderBookType::ask);
                std::cout << "came so far 1" << std::endl;
                if (wallet.canFulfillOrder(obe)) {
                    std::cout << "Wallet looks good. " << std::endl;
                    orderBook.insertNewOrder(obe);
                    std::cout << "came so far 2" << std::endl;
                }
                else {
                    std::cout << "Wallet has insuficient funds. " << std::endl;
                }

            }
            catch (const std::exception& e) {
                std::cout << "MerkelMain::P_ask Bad input! " << std::endl;
            }

        }

        else {
            std::cout << "MerkelMain::P_bid Bad input for product! " << std::endl;
        }
    }

}

void MerkelMain::P_wallet()
{
    std::cout << "\nYou chose Wallet" << std::endl;
    std::cout << wallet.toString() << std::endl;
}

void MerkelMain::go_to_next_frame()
{
    std::cout << "\nYou chose Continue to the next time frame" << std::endl;
    std::vector<OrderBookEntry> sales = orderBook.matchAsksToBid("ETH/BTC",currentTime);
    
    std::cout << "Number of Sales: " << sales.size() << std::endl;

    for (const OrderBookEntry& sale : sales) {
       
        std::cout << "Sale price: " << sale.price << "; Amount: " << sale.amount << std::endl;
    }

    currentTime = orderBook.getNextTime(currentTime);

}

void MerkelMain::verifying_option(int user_option)
{
    // Checking the user option
    //if (std::cin.fail() || user_option < 1 || user_option > 6)
    if (user_option < 1 || user_option > 6)
    {
        std::cout << "\nInvalid input. Please enter a valid integer number from 1 to 6." << std::endl;
 // This treatmente only worked to cin fails;
        //std::cin.clear();           // If it fail, clear the fail state
        //std::cin.ignore(256, '\n'); // Ignore what comes after
    }
    else
    {
        switch (user_option)
        {
        case 1:
            P_help();
            break;
        case 2:
            P_stats(1);
            break;
        case 3:
            P_ask();
            P_stats(0);
            break;
        case 4:
            P_bid();
            break;
        case 5:
            P_wallet();
            break;
        case 6:
            go_to_next_frame();
            // Calculate every stats, max and minimum included, but does not print. 
            P_stats(0);
            break;
        }
    }
}