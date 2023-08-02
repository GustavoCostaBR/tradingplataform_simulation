#pragma once
#include <vector>
#include "OrderBookEntry.h"

class MerkelMain{

    public:
        MerkelMain() = default;
        /**Call it to start the program */
        void init();
    private:
        void loadOrderBook();
        void menu_printing();
        int user_input();
        void P_help();
        void P_stats();
        void P_ask();
        void P_bid();
        void P_wallet();
        void go_to_next_frame();
        void verifying_option(int user_option);

        std::vector<OrderBookEntry> Orders;
};