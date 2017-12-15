/**
* BondTradeBookingServiceConnector.hpp
* The Connector specific for Trade<Bond>
* Flow the txt data to BondTradeBookingService
*
* @author Sijia Liu
*/
#pragma once

#include"soa.hpp"
#include"products.hpp"
#include"BondTradeBookingService.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

/*
Connector for BondTradeBookingService
subscrible only
flow Trade<Bond> data to the service from txt file via onMessage

*/

class BondTradeBookingServiceConnector :public Connector<Trade<Bond>>
{
public:
	//ctor
	BondTradeBookingServiceConnector(BondTradeBookingService &_bookingservice, string _file);

	// Publish data to the Connector
	virtual void Publish(Trade<Bond> &data);

	//get data from file and create Trade<Bond> object, 
	//then flow into the service via onMessage()
	void Subscribe();

private:
	//file to read trade data
	string file;
	
	//service to flow data to (via onMessage)
	BondTradeBookingService &bookingservice;

};

BondTradeBookingServiceConnector::BondTradeBookingServiceConnector(BondTradeBookingService &_bookingservice, string _file)
	:bookingservice(_bookingservice),file(_file)
{ }


void BondTradeBookingServiceConnector::Publish(Trade<Bond> &data)
{
	//doing nothing. This is subscribe only
}

void BondTradeBookingServiceConnector::Subscribe()
{
	ifstream inf;
	inf.open(file, ifstream::in);

	//attribute of bond
	string productId;
	string Type;
	BondIdType bondIdType;
	string ticker;
	float coupon;
	date maturityDate;

	//attribute of trade
	string tradeId;
	double price;
	string book;
	long quantity;
	string tempside;
	Side side;

	//parameter used to read txt file
	string line;
	size_t comma = 0;
	size_t comma2 = 0;


	while (!inf.eof())
	{
		getline(inf, line);

		//get product id
		comma = line.find(',', 0);
		productId = line.substr(0, comma).c_str();

		//get id type
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

		//get ticker
		comma2 = line.find(',', comma + 1);
		ticker = line.substr(comma + 1, comma2 - comma - 1).c_str();
		comma = comma2;

		//get coupon
		comma2 = line.find(',', comma + 1);
		coupon = atof(line.substr(comma + 1, comma2 - comma - 1).c_str());
		comma = comma2;

		//get maturity date
		comma2 = line.find(',', comma + 1);
		string strdate = line.substr(comma + 1, comma2 - comma - 1).c_str();
		maturityDate = date(atoi(line.substr(comma + 1, comma + 4).c_str()),
			atoi(line.substr(comma + 6, comma + 7).c_str()), atoi(line.substr(comma + 9, comma + 10).c_str()));
		comma = comma2;

		//create bond object
		Bond mybond(productId, bondIdType, ticker, coupon, maturityDate);

		//get trade id
		comma2 = line.find(',', comma + 1);
		tradeId = line.substr(comma + 1, comma2 - comma - 1).c_str();
		comma = comma2;

		//get price
		comma2 = line.find(',', comma + 1);
		price = atof(line.substr(comma + 1, comma2 - comma - 1).c_str());
		comma = comma2;

		//get book
		comma2 = line.find(',', comma + 1);
		book = line.substr(comma + 1, comma2 - comma - 1).c_str();
		comma = comma2;

		//get quantity
		comma2 = line.find(',', comma + 1);
		quantity = atol(line.substr(comma + 1, comma2 - comma - 1).c_str());
		comma = comma2;

		//get side
		comma2 = line.find(',', comma + 1);
		tempside = line.substr(comma + 1, comma2 - comma - 1).c_str();
		if (tempside == "BUY")
		{
			side = BUY;
		}
		else if (tempside == "SELL")
		{
			side = SELL;
		}

		//create trade<bond> object according to the data from txt
		Trade<Bond> mytrade(mybond, tradeId, price, book, quantity, side);

		//invoke the onMessage() method of the service
		bookingservice.OnMessage(mytrade);

	}

	inf.close();

}