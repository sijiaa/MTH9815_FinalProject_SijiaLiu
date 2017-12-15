/**
* BondMarketDataServiceConnector.hpp
* The Connector specific for OrderBook<Bond>
* Flow the txt data to BondMarketDataService
*
* @author Sijia Liu
*/
#pragma once

#include"soa.hpp"
#include"products.hpp"
#include"BondMarketDataService.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

/*
Connector for BondMarketDataService
subscrible only
flow OrderBook<Bond> data to the service from txt file via onMessage

*/
class BondMarketDataServiceConnector :public Connector<OrderBook<Bond>>
{
public:
	//ctor
	BondMarketDataServiceConnector(BondMarketDataService &_bookingservice, string _file);

	// Publish data to the Connector
	virtual void Publish(OrderBook<Bond> &data);

	//get data from file and create Trade<Bond> object, 
	//then flow into the service via onMessage()
	void Subscribe();

private:
	//file to read trade data
	string file;

	//service to flow data to (via onMessage)
	BondMarketDataService &marketdataservice;
};

BondMarketDataServiceConnector::BondMarketDataServiceConnector(BondMarketDataService &_marketdataservice, string _file)
	:marketdataservice(_marketdataservice), file(_file)
{ }


void BondMarketDataServiceConnector::Publish(OrderBook<Bond> &data)
{
	//doing nothing. This is subscribe only
}

void BondMarketDataServiceConnector::Subscribe()
{
	ifstream inf;
	inf.open(file, ifstream::in);


	string productId;
	string Type;
	BondIdType bondIdType;
	string ticker;
	float coupon;
	date maturityDate;

	
	double price;
	long quantity = 10000000;

	string line;
	size_t comma = 0;
	size_t comma2 = 0;


	while (!inf.eof())
	{
		getline(inf, line);


		comma = line.find(',', 0);
		productId = line.substr(0, comma).c_str();

		comma2 = line.find(',', comma + 1);
		Type = line.substr(comma + 1, comma2 - comma - 1).c_str();
		if (Type == "CUSIP")
		{
			bondIdType = CUSIP;
		}
		else if (Type == "ISIN")
		{
			bondIdType = ISIN;
		}
		comma = comma2;


		comma2 = line.find(',', comma + 1);
		ticker = line.substr(comma + 1, comma2 - comma - 1).c_str();
		comma = comma2;


		comma2 = line.find(',', comma + 1);
		coupon = atof(line.substr(comma + 1, comma2 - comma - 1).c_str());
		comma = comma2;

		comma2 = line.find(',', comma + 1);
		string strdate = line.substr(comma + 1, comma2 - comma - 1).c_str();
		maturityDate = date(atoi(line.substr(comma + 1, comma + 4).c_str()),
			atoi(line.substr(comma + 6, comma + 7).c_str()), atoi(line.substr(comma + 9, comma + 10).c_str()));
		comma = comma2;

		//get bond
		Bond mybond(productId, bondIdType, ticker, coupon, maturityDate);

		vector<Order> bidStack;
		vector<Order> offerStack;

		//get bid stack
		for (int i = 0; i < 5; ++i)
		{
			comma2 = line.find(',', comma + 1);
			price = atof(line.substr(comma + 1, comma2 - comma - 1).c_str());
			bidStack.push_back(Order(price, quantity*(i + 1), BID));
			comma = comma2;
		}

		//get offer stack
		for (int i = 0; i < 5; ++i)
		{
			comma2 = line.find(',', comma + 1);
			price = atof(line.substr(comma + 1, comma2 - comma - 1).c_str());
			offerStack.push_back(Order(price, quantity*(i + 1), OFFER));
			comma = comma2;
		}

		//create orderbook object from data
		OrderBook<Bond> myorderbook(mybond, bidStack, offerStack);

		//invoke the onMessage() method of the service
		marketdataservice.OnMessage(myorderbook);
	}

	inf.close();
}