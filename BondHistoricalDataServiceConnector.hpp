/**
* HistoricalDataServiceConnector.hpp
* HistoricalDataServiceConnector and its derived class for different type
* Used to write data to txt file
*
* @author Sijia Liu
*/
#pragma once
#pragma warning( disable : 4996)

#include"soa.hpp"
#include"products.hpp"
#include"positionservice.hpp"
#include"riskservice.hpp"
#include"executionservice.hpp"
#include"streamingservice.hpp"
#include"inquiryservice.hpp"
#include<chrono>

/*
Special Connector for HistoricalDataService
Served as a private data member of BondHistoricalDataService
Publish method will be called in PersistData() when new data flow in 
*/
//need derive class according to different type of T, since write to txt file for different object is different
//T can be Position<Bond>, PV01<Bond>, ExecutionOrder<Bond>, PriceStream<Bond>, Inquiry<Bond>

template<typename T>
class HistoricalDataServiceConnector :public Connector<T>
{
public:
	// Publish data to the Connector
	//In this Connector for HistoricalDataService, Publish will write the data to txt file
	virtual void Publish(T &data) = 0;
};



class HistoricalDataServiceConnectorforPosition :public HistoricalDataServiceConnector<Position<Bond>>
{
public:
	//ctor
	HistoricalDataServiceConnectorforPosition(string _file);
	~HistoricalDataServiceConnectorforPosition();

	//write the data to txt file
	virtual void Publish(Position<Bond> &data);

private:
	//the file that the listener write data to
	string file;
	ofstream outf;
};

HistoricalDataServiceConnectorforPosition::HistoricalDataServiceConnectorforPosition(string _file)
	:file(_file) 
{
	outf = ofstream(file);
}

HistoricalDataServiceConnectorforPosition::~HistoricalDataServiceConnectorforPosition()
{
	outf.close();
}

void HistoricalDataServiceConnectorforPosition::Publish(Position<Bond> &data)
{
	auto n = chrono::system_clock::now();
	std::time_t t = chrono::system_clock::to_time_t(n);
	outf << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S") << ",";
	outf << data.GetProduct().GetProductId() << ",";
	outf << data.GetAggregatePosition() << ",";
	outf << "TRSY1," << data.GetPosition("TRSY1") << ",";
	outf << "TRSY2," << data.GetPosition("TRSY2") << ",";
	outf << "TRSY3," << data.GetPosition("TRSY3") << endl;
	outf << flush;
}

class HistoricalDataServiceConnectorforRisk :public HistoricalDataServiceConnector<PV01<Bond>>
{
public:
	//ctor
	HistoricalDataServiceConnectorforRisk(string _file);
	~HistoricalDataServiceConnectorforRisk();
	//write the data to txt file
	virtual void Publish(PV01<Bond> &data);

private:
	//the file that the listener write data to
	string file;
	ofstream outf;
};

HistoricalDataServiceConnectorforRisk::HistoricalDataServiceConnectorforRisk(string _file)
	:file(_file) 
{
	outf = ofstream(file);
}

HistoricalDataServiceConnectorforRisk::~HistoricalDataServiceConnectorforRisk()
{
	outf.close();
}

void HistoricalDataServiceConnectorforRisk::Publish(PV01<Bond> &data)
{
	auto n = chrono::system_clock::now();
	std::time_t t = chrono::system_clock::to_time_t(n);
	outf << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S") << ",";
	outf << data.GetProduct().GetProductId() << ",";
	outf << data.GetPV01() << ",";
	outf << data.GetQuantity() << endl;
	outf << flush;
}

class HistoricalDataServiceConnectorforExecution :public HistoricalDataServiceConnector<ExecutionOrder<Bond>>
{
public:
	//ctor
	HistoricalDataServiceConnectorforExecution(string _file);
	~HistoricalDataServiceConnectorforExecution();

	//write the data to txt file
	virtual void Publish(ExecutionOrder<Bond> &data);

private:
	//the file that the listener write data to
	string file;
	ofstream outf;
};

HistoricalDataServiceConnectorforExecution::HistoricalDataServiceConnectorforExecution(string _file)
	:file(_file) 
{
	outf = ofstream(file);
}

HistoricalDataServiceConnectorforExecution::~HistoricalDataServiceConnectorforExecution()
{
	outf.close();
}


void HistoricalDataServiceConnectorforExecution::Publish(ExecutionOrder<Bond> &data)
{
	auto n = chrono::system_clock::now();
	std::time_t t = chrono::system_clock::to_time_t(n);
	outf << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S") << ",";
	outf << data.GetProduct().GetProductId() << ",";
	outf << data.GetOrderId() << ",";
	outf << data.GetOrderType() << ",";
	PricingSide tempside = data.GetPricingSide();
	if (tempside == BID)
	{
		outf << "BID" << ",";
	}
	else
	{
		outf << "OFFER" << ",";
	}	
	double mid = data.GetPrice();
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
	outf << data.GetVisibleQuantity() << ",";
	outf << data.GetHiddenQuantity() << ",";
	outf << data.GetParentOrderId() << ",";
	outf << data.IsChildOrder() <<endl;
	outf << flush;
}

class HistoricalDataServiceConnectorforStream :public HistoricalDataServiceConnector<PriceStream<Bond>>
{
public:
	//ctor
	HistoricalDataServiceConnectorforStream(string _file);
	~HistoricalDataServiceConnectorforStream();

	//write the data to txt file
	virtual void Publish(PriceStream<Bond> &data);

private:
	//the file that the listener write data to
	string file;
	ofstream outf;
};


HistoricalDataServiceConnectorforStream::HistoricalDataServiceConnectorforStream(string _file)
	:file(_file) 
{
	outf = ofstream(file);
}

HistoricalDataServiceConnectorforStream::~HistoricalDataServiceConnectorforStream()
{
	outf.close();
}


void HistoricalDataServiceConnectorforStream::Publish(PriceStream<Bond> &data)
{
	auto n = chrono::system_clock::now();
	std::time_t t = chrono::system_clock::to_time_t(n);
	outf << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S") << ",";
	outf << data.GetProduct().GetProductId() << ",";
	double mid = data.GetBidOrder().GetPrice();
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
	outf << data.GetBidOrder().GetVisibleQuantity() << ",";
	outf << data.GetBidOrder().GetHiddenQuantity() << ",";
	PricingSide tempside = data.GetBidOrder().GetSide();
	if (tempside == BID)
	{
		outf << "BID" << ",";
	}
	else
	{
		outf << "OFFER" << ",";
	}
	mid = data.GetOfferOrder().GetPrice();
	first = floor(mid);
	second = int(256 * (mid - first)) / 8;
	third = int(256 * (mid - first)) % 8;
	outf << first << "-" << second << third << ",";
	outf << data.GetOfferOrder().GetVisibleQuantity() << ",";
	outf << data.GetOfferOrder().GetHiddenQuantity() << ",";
	tempside = data.GetOfferOrder().GetSide();
	if (tempside == BID)
	{
		outf << "BID" ;
	}
	else
	{
		outf << "OFFER" ;
	}
	outf << endl;
	outf << flush;
}

class HistoricalDataServiceConnectorforInquiry :public HistoricalDataServiceConnector<Inquiry<Bond>>
{
public:
	//ctor
	HistoricalDataServiceConnectorforInquiry(string _file);
	~HistoricalDataServiceConnectorforInquiry();

	//write the data to txt file
	virtual void Publish(Inquiry<Bond> &data);
	

private:
	//the file that the listener write data to
	string file;
	ofstream outf;
};

HistoricalDataServiceConnectorforInquiry::HistoricalDataServiceConnectorforInquiry(string _file)
	:file(_file)
{
	outf = ofstream(file);
}

HistoricalDataServiceConnectorforInquiry::~HistoricalDataServiceConnectorforInquiry()
{
	outf.close();
}

void HistoricalDataServiceConnectorforInquiry::Publish(Inquiry<Bond> &data)
{
	auto n = chrono::system_clock::now();
	std::time_t t = chrono::system_clock::to_time_t(n);
	outf << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S") << ",";
	outf << data.GetProduct().GetProductId() << ",";
	outf << data.GetInquiryId() << ",";
	Side tempside = data.GetSide();
	if (tempside == BUY)
	{
		outf << "BUY" << ",";
	}
	else
	{
		outf << "SELL" << ",";
	}
	double mid = data.GetPrice();
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
	outf << data.GetQuantity() << ",";
	
	InquiryState tempstate = data.GetState();
	if (tempstate == RECEIVED)
	{
		outf << "RECEIVED" ;
	}
	else if (tempstate == QUOTED)
	{
		outf << "QUOTED" ;
	}
	else if (tempstate == DONE)
	{
		outf << "DONE" << ",";
	}
	else if (tempstate == REJECTED)
	{
		outf << "REJECTED";
	}
	else
	{
		outf << "CUSTOMER_REJECTED";
	}

	outf << endl;
	outf << flush;
}