#include "CSVReader.h"


CSVReader::CSVReader() {


}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename)
{	
	std::ifstream csvFile{csvFilename};
	std::string line;
	std::vector<std::string> tokens;
	std::vector<OrderBookEntry> Orders;

	if (csvFile.is_open()) {
		std::cout << "File open " << std::endl;
		while (std::getline(csvFile, line)) {
			try {
				OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
				Orders.push_back(obe);
			}
			catch (const std::exception& e) {

				std::cout << "Bad data!" << std::endl;
			}
			}
	}
	std::cout << "CSVReader::readCSV read " << Orders.size() <<" entries" << std::endl;
	return Orders;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{	
	std::vector<std::string> tokens;
	signed int start, end;
	std::string token;

	start = csvLine.find_first_not_of(separator, 0); //Position = 0

	do {
		end = csvLine.find_first_of(separator, start); //First separator after start

		if (start == csvLine.length() || start == end) break;


		if (end >= 0) token = csvLine.substr(start, end - start);

		else token = csvLine.substr(start, csvLine.length() - start);

		tokens.push_back(token);

		start = end + 1;

	} while (end != std::string::npos);

	return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(std::string priceString, std::string amountString, std::string timestamp, std::string product, OrderBookType orderbooktype)
{
	double price, amount;
	try {
		price = std::stod(priceString);
		amount = std::stod(amountString);
		}
	catch (std::exception& e) {
		std::cout << "CSVReader::stringsToOBE Bad double!" << priceString << std::endl;
		std::cout << "CSVReader::stringsToOBE Bad double!" << amountString << std::endl;
		throw;
	}
	OrderBookEntry obe{ price, amount, timestamp, product, orderbooktype };



	return obe;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
	if (tokens.size() != 5) {
		std::cout << "Something bad happend!" << std::endl;
		throw std::exception{};
	}
	std::string timestamp;
	std::string product;
	OrderBookType ordertype;
	double price;
	double amount;
	
	timestamp = tokens[0];
	product = tokens[1];
	try {
		price = std::stod(tokens[3]);
		amount = std::stod(tokens[4]);
		ordertype = OrderBookEntry::stringToOBT(tokens[2]);
	}
	catch (std::exception& e) {
		std::cout << "CSVReader::stringsToOBE Bad double!" << tokens[3] << std::endl;
		std::cout << "CSVReader::stringsToOBE Bad double!" << tokens[4] << std::endl;
		throw;
	}

	OrderBookEntry obe{price, amount, timestamp, product, ordertype};
	return obe;
}

