#include <string>
#include "OrderBookEntry.h"
#include <map>
#include "CSVReader.h"

#pragma once
class Wallet
{
	public:
		Wallet();
	
		/** insert currency to the wallet */
		void insertCurrency(std::string type, double amount);
	
		/** remove currency from the wallet */
		bool removeCurrency(std::string type, double amount);
		
		/** check whether the wallet contains the specific amount of a currency or more */
		bool containsCurrency(std::string type, double amount);

		/**check whether the wallet can cope with this ask or bid */
		bool canFulfillOrder(OrderBookEntry order);

		/** Generate a string representation of the wallet */
		std::string toString();

	private:
		std::map<std::string, double> currencies;
};

