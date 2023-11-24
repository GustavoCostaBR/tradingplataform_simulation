#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "OrderBookEntry.h"
#include <exception>
#include <iostream>
#include <sstream>
#include <algorithm>

class CSVReader
{
	public:
		CSVReader();

		static std::vector<OrderBookEntry> readCSV(std::string csvFile);
		static std::vector<std::string> tokenise(std::string csvLine, char separator);
		static OrderBookEntry stringsToOBE(std::string price, std::string amount, std::string timestamp, std::string product, OrderBookType orderbooktype);
		static std::string invertPair(const std::string& originalPair);

	private:
		static OrderBookEntry stringsToOBE(std::vector<std::string> strings);

};

