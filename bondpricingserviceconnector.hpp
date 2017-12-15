/**
* BondPricingServiceConnector.hpp
* The Connector specific for Price<Bond>
* Flow the txt data to BondPricingServiceC
*
* @author Sijia Liu
*/
#pragma once


#include"soa.hpp"
#include"products.hpp"
#include"BondPricingService.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

/*
Connector for BondPricingService
subscrible only
flow Price<Bond> data to the service from txt file via onMessage

*/

class BondPricingServiceConnector :public Connector<Price<Bond>>
{
public:
	//ctor
	BondPricingServiceConnector(BondPricingService &_pricingservice, string _file);

	// Publish data to the Connector
	virtual void Publish(Price<Bond> &data);

	//get data from file and create Trade<Bond> object, 
	//then flow into the service via onMessage()
	void Subscribe();

private:
	//file to read trade data
	string file;

	//service to flow data to (via onMessage)
	BondPricingService &pricingservice;

};

BondPricingServiceConnector::BondPricingServiceConnector(BondPricingService &_pricingservice, string _file)
	:pricingservice(_pricingservice), file(_file)
{ }


void BondPricingServiceConnector::Publish(Price<Bond> &data)
{
	//doing nothing. This is subscribe only
}

void BondPricingServiceConnector::Subscribe()
{
	ifstream inf;
	inf.open(file, ifstream::in);


	string productId;
	string Type;
	BondIdType bondIdType;
	string ticker;
	float coupon;
	date maturityDate;


	double mid;
	double spread;

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

		//create bond object
		Bond mybond(productId, bondIdType, ticker, coupon, maturityDate);

		//get mid
		comma2 = line.find(',', comma + 1);
		mid = atof(line.substr(comma + 1, comma2 - comma - 1).c_str());
		comma = comma2;

		//get spread
		comma2 = line.find(',', comma + 1);
		spread = atof(line.substr(comma + 1, comma2 - comma - 1).c_str());
		comma = comma2;

		Price<Bond> myprice(mybond, mid, spread);

		//invoke the onMessage() method of the service
		pricingservice.OnMessage(myprice);
	}

}