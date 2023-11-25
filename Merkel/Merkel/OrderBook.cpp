#include "OrderBook.h"


OrderBook::OrderBook(std::string filename)
{	
	orders = CSVReader::readCSV(filename);
	}

std::vector<std::string> OrderBook::getKnownProducts()
{	
	std::vector<std::string> products;
	std::map<std::string, bool> prodMap;
	
	for (OrderBookEntry& e : orders) {

		prodMap[e.product] = true;
	}
	// Now flatten the map to a vector of strings
	for (auto const& e : prodMap) {
		products.push_back(e.first);
	}

	return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp)
{	
	std::vector<OrderBookEntry> orders_sub;
	for (const OrderBookEntry& e : orders) {
		if (e.orderType == type &&
			e.product == product &&
			e.timestamp == timestamp) {
			
			orders_sub.push_back(e);
		}

	}
	
	return orders_sub;
}

std::string OrderBook::getEarliestTime()
{	
	return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp)
{
	std::string next_timestamp = "";
	for (OrderBookEntry& e : orders) {
		if (e.timestamp > timestamp){
			next_timestamp = e.timestamp;
			break;
		}
	}
	if (next_timestamp == "") {
		next_timestamp = orders[0].timestamp;
		}
	
	return next_timestamp;
}


void OrderBook::insertNewOrder(OrderBookEntry& order)
{
	orders.push_back(order);
	std::sort(orders.begin(), orders.end(), OrderBookEntry::compareOrderTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBid(std::string product, std::string timestamp)
{
	std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
	
	std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);
	
	std::vector<OrderBookEntry> sales;

	std::sort(asks.begin(), asks.end(), OrderBookEntry::compareOrderPriceAsc);

	std::sort(bids.begin(), bids.end(), OrderBookEntry::compareOrderPriceDesc);

	for (OrderBookEntry& ask : asks) {
		for (OrderBookEntry& bid : bids) {

			if (bid.price >= ask.price) {
				OrderBookType type = OrderBookType::asksale;
				OrderBookEntry sale{ ask.price, 0, timestamp, product, type };
				
				if (bid.username == "simuser") {
					type = OrderBookType::bidsale;
					sale.username = "simuser";
					sale.orderType = type;
				}
				else if (ask.username == "simuser") {
					sale.username = "simuser";
					sale.orderType = type;
				}

				

				if (bid.amount == ask.amount) {
					sale.amount = ask.amount;
					sales.push_back(sale);
					bid.amount = 0;
					break;
				}
				if (bid.amount > ask.amount) {
					sale.amount = ask.amount;
					sales.push_back(sale);
					bid.amount = bid.amount - ask.amount;
					break;

				}

				if (bid.amount < ask.amount && bid.amount > 0) {
					sale.amount = bid.amount;
					sales.push_back(sale);
					ask.amount = ask.amount - bid.amount;
					bid.amount = 0;
					continue;
				}
			}
		}
	}

	return sales;
}

std::vector<double> OrderBook::get_max_since_start(std::vector<OrderBookEntry>& orders_ask, std::vector<OrderBookEntry>& orders_bid, std::string const &p, std::vector<double>& max_since_start, std::map<std::string, int> stringToNumber)
{
	double temp;
	temp = (OrderBook::getLowPrice(orders_ask) + OrderBook::getHighPrice(orders_bid))/2.0;
	if (max_since_start[stringToNumber[p]] < temp) {
		max_since_start[stringToNumber[p]] = temp;
		}
	return max_since_start;
}

std::vector<double> OrderBook::get_min_since_start(std::vector<OrderBookEntry>& orders_ask, std::vector<OrderBookEntry>& orders_bid, std::string const& p, std::vector<double> &min_since_start, std::map<std::string, int> stringToNumber)
{
	double temp;
	temp = (OrderBook::getLowPrice(orders_ask) + OrderBook::getHighPrice(orders_bid)) / 2.0;
	if (min_since_start[stringToNumber[p]] > temp) {
		min_since_start[stringToNumber[p]] = temp;
	}
	return min_since_start;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
	double max = orders[0].price;
	for (OrderBookEntry& e : orders) {

		if (e.price > max) {
			max = e.price;
		}
	}
	return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
	double min = orders[0].price;
	for (OrderBookEntry& e : orders) {

		if (e.price < min) {
			min = e.price;
		}
	}
	return min;
}

double OrderBook::getSpread(std::vector<OrderBookEntry>& orders_ask, std::vector<OrderBookEntry>& orders_bid)
{
	double spread;
	
	spread = (OrderBook::getLowPrice(orders_ask) - OrderBook::getHighPrice(orders_bid));

	return spread;
}


