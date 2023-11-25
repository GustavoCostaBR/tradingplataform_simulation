#include "Wallet.h"
#include <iostream>

Wallet::Wallet()
{
}

void Wallet::insertCurrency(std::string type, double amount)
{
	double balance;
	
	std::cout << "Trying to insert " << amount << " " << type << " in the wallet!" << std::endl;
	if (amount < 0) {
		//throw std::exception{};
		throw std::runtime_error("Amount cannot be negative!");
	}
	else {
		std::cout << amount << " " << type << " inserted in the wallet!" << std::endl;
	}
	if (this->containsCurrency(type, 0)) {
		balance = currencies[type];
	}
	else
	{
		balance = 0;
	}
	balance += amount;
	currencies[type] = balance;
}

bool Wallet::removeCurrency(std::string type, double amount)
{
	std::cout << "Trying to remove " << amount << " " << type << " from the wallet!" << std::endl;
	if (amount < 0) {
		//throw std::exception{};
		throw std::runtime_error("Amount cannot be negative!");
	}

	if (this->containsCurrency(type, amount)) {
		currencies[type] -= amount;
		std::cout << "Money removed: "<< amount << " " << type << std::endl;
		return true;
	}
	else
	{
		std::cout << "Insuficient funds: Tried to remove " << amount << " and has " << currencies[type]<< " " << type << std::endl;
		return false;
	}
}

bool Wallet::containsCurrency(std::string type, double amount)
{
	if (currencies.count(type) == 0) {
		std::cout << "Verified " << type <<  " count and it is equal to 0! Returning false!"<< std::endl;
		return false;
	}
	else {
		if (currencies[type] >= amount) {
			std::cout << "Verified " << type << " count (" << currencies[type] << ") and it is more than " << amount << " (amount). Returning true!" << std::endl;
		}
		else {
			std::cout << "Verified " << type << " count (" << currencies[type] << ") and it is less than " << amount << " (amount). Returning false!" << std::endl;
		}
	return (currencies[type] >= amount); // there is no crypto of this type yet

	}
}

bool Wallet::canFulfillOrder(OrderBookEntry order)
{
	std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');
	// ask
	if (order.orderType == OrderBookType::ask) {
		double amount = order.amount;
		std::string currency = currs[0];
		std::cout << "Wallet::canFulfillOrder: " << amount << "  " << currency << std::endl;
		return containsCurrency(currency, amount);
	}

	// bid
	if (order.orderType == OrderBookType::bid) {
		double amount = order.amount * order.price;
		std::string currency = currs[1];
		std::cout << "Wallet::canFulfillOrder: " << amount << "  " << currency << std::endl;
		return containsCurrency(currency, amount);
	}
	return false;
}

void Wallet::processSale(OrderBookEntry& sale)
{
	std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');
	// ask
	if (sale.orderType == OrderBookType::asksale) {
		double outgoingAmount = sale.amount;
		std::string outgoingCurrency = currs[0];
		double incomingAmount = sale.amount * sale.price;
		std::string incomingCurrency = currs[1];

		currencies[incomingCurrency] += incomingAmount;
		currencies[outgoingCurrency] -= outgoingAmount;
		
	}

	// bid
	else if (sale.orderType == OrderBookType::bidsale) {
		double incomingAmount = sale.amount;
		std::string incomingCurrency = currs[0];
		double outgoingAmount = sale.amount * sale.price;
		std::string outgoingCurrency = currs[1];

		currencies[incomingCurrency] += incomingAmount;
		currencies[outgoingCurrency] -= outgoingAmount;
	}
}

std::string Wallet::toString()
{
	std::string s;
	for (std::pair<const std::string, double> pair : currencies) {
		std::string currency = pair.first;
		double amount = pair.second;
		s += currency + " : " + std::to_string(amount) + "\n";
	}
	if (s.empty()) {
		s = "Your wallet is empty!";
	}
	return s;
}
