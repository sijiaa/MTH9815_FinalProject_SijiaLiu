/**
* BondIquiryServiceReadfileConnector.hpp
* The Connector specific for vector Inquiry<Bond>
* Flow the txt data to BondIquiryService
*
* @author Sijia Liu
*/
#pragma once

#include"soa.hpp"
#include"products.hpp"
#include"BondInquiryService.hpp"

#include <fstream>
#include <sstream>
#include <iostream>


/*
Connector for BondInquiryService
subscrible only
flow Inquiry<Bond> data to the service from txt file via onMessage

*/
class BondIquiryServiceReadfileConnector :public Connector<Inquiry<Bond>>
{
public:
	//ctor
	BondIquiryServiceReadfileConnector(BondInquiryService &_inquiryservice, string _file);

	// Publish data to the Connector
	virtual void Publish(Inquiry<Bond> &data);

	//get data from file and create Trade<Bond> object, 
	//then flow into the service via onMessage()
	void Subscribe();

private:
	//file to read trade data
	string file;

	//service to flow data to (via onMessage)
	BondInquiryService &inquiryservice;

};

BondIquiryServiceReadfileConnector::BondIquiryServiceReadfileConnector(BondInquiryService &_inquiryservice, string _file)
	:inquiryservice(_inquiryservice), file(_file) {}

void BondIquiryServiceReadfileConnector::Publish(Inquiry<Bond> &data)
{

}

void BondIquiryServiceReadfileConnector::Subscribe()
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
	string inquiryId;
	Side side;
	string tempside;
	long quantity;
	double price;
	InquiryState state;
	string tempstate;

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

		//get inqury id
		comma2 = line.find(',', comma + 1);
		inquiryId = line.substr(comma + 1, comma2 - comma - 1).c_str();
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
		comma = comma2;


		//get quantity
		comma2 = line.find(',', comma + 1);
		quantity = atol(line.substr(comma + 1, comma2 - comma - 1).c_str());
		comma = comma2;

		//get price
		comma2 = line.find(',', comma + 1);
		price = atof(line.substr(comma + 1, comma2 - comma - 1).c_str());
		comma = comma2;

		//get state
		comma2 = line.find(',', comma + 1);
		tempstate = line.substr(comma + 1, comma2 - comma - 1).c_str();
		if (tempstate == "RECEIVED")
		{
			state = RECEIVED;
		}
		else if (tempstate == "QUOTED")
		{
			state = QUOTED;
		}

		//create trade<bond> object according to the data from txt
		Inquiry<Bond> myinquiry(inquiryId, mybond, side, quantity, price, state);

		//invoke the onMessage() method of the service
		inquiryservice.OnMessage(myinquiry);
	}

	inf.close();
}