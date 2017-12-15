/**
* BondGUIServiceWriteConnector.hpp
* The Connector specific for Price<Bond>
* Used to write data to txt file
*
* @author Sijia Liu
*/
#pragma once
#pragma warning( disable : 4996)

#include"soa.hpp"
#include"products.hpp"
#include<fstream>


class BondGUIServiceWriteConnector :public Connector<Price<Bond>>
{
public:
	//ctor
	BondGUIServiceWriteConnector(string _file);
	~BondGUIServiceWriteConnector();

	// Publish data to the Connector
	virtual void Publish(Price<Bond> &data);

private:
	//the file that the listener write data to
	string file;
	ofstream outf;
};


BondGUIServiceWriteConnector::BondGUIServiceWriteConnector(string _file)
	:file(_file)
{
	outf = ofstream(file);
}

BondGUIServiceWriteConnector::~BondGUIServiceWriteConnector()
{
	outf.close();
}

void BondGUIServiceWriteConnector::Publish(Price<Bond> &data)
{
	auto n = chrono::system_clock::now();
	std::time_t t = chrono::system_clock::to_time_t(n);
	outf << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S") << ",";
	outf << data.GetProduct().GetProductId() << ",";
	double mid = data.GetMid();
	double first = floor(mid);
	int second = int(256 * (mid - first)) / 8;
	int third = int(256 * (mid - first)) % 8;
	if (second < 10)
	{
		outf << first << "-0" << second << third << ",";
	}
	else
	{
		outf << first << "-" << second << third << ",";
	}
	
	outf << data.GetBidOfferSpread();
	outf << endl;
	outf << flush;
}