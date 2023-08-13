#pragma once

#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <map>

class OrderBook
{
	public:
		/** construct, reading a csv data file*/
		OrderBook(std::string filename);
		/** return a vector of all known products in the dataset*/
		std::vector<std::string> getKnownProducts();
		/** return a vector of orders according to the sent filters*/
		std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);

		/** Return the first timestamp*/
		std::string getEarliestTime();
		/** Return the next timestamp. If there is no next time stamp will return to the begining*/
		std::string getNextTime(std::string timestamp);

		//void initialize_vector(size_t a);

		void insertNewOrder(OrderBookEntry& order);

		std::vector<OrderBookEntry> matchAsksToBid(std::string product, std::string timestamp);

		static std::vector<double> get_max_since_start(std::vector<OrderBookEntry>& orders_ask, std::vector<OrderBookEntry>& orders_bid, std::string const& p, std::vector<double>& max_since_start, std::map<std::string, int> stringToNumber);

		static std::vector<double> get_min_since_start(std::vector<OrderBookEntry>& orders_ask, std::vector<OrderBookEntry>& orders_bid, std::string const& p, std::vector<double>& min_since_start, std::map<std::string, int> stringToNumber);
		

		/** Return the highest price of a bid or ask order, it depends on the type of the order passed as an argument*/
		static double getHighPrice(std::vector<OrderBookEntry>& orders);
		
		/** Return the lowest price of a bid or ask order, it depends on the type of the order passed as an argument*/
		static double getLowPrice(std::vector<OrderBookEntry>& orders);
		
		/** Return the spread, a ask order must be passed as a first argument and a ask order as second*/
		static double getSpread(std::vector<OrderBookEntry>& orders_ask, std::vector<OrderBookEntry>& orders_bid);

		

		
	private:
		std::vector<OrderBookEntry> orders;
		std::vector<double> max_since_start;
		std::vector<double> min_since_start;
};
