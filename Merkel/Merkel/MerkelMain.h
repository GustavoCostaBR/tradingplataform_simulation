#pragma once
#include <vector>
#include <iostream>
#include <limits>
#include <map>
//#include <stdio.h>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "OrderBook.h"

class MerkelMain{

    public:
        MerkelMain() = default;
        /**Call it to start the program */
        void init();
        
    private:
        /*void loadOrderBook();*/
        void menu_printing();
        int user_input();
        void P_help();
        //std::vector <double> stats();
        void P_stats(int a);
        void P_ask();
        void P_bid();
        void P_wallet();
        void go_to_next_frame();
        void verifying_option(int user_option);

        std::string currentTime;

        //OrderBook orderBook{ "20200317.csv" };
        
        OrderBook orderBook{ "2020.csv" };
        
        std::vector<double> max_since_start;
        std::vector<double> min_since_start;
        std::map<std::string, int> stringToNumber;
};