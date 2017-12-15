/**
* BondTradeBookingService.hpp
* The TradeBookingService specific for bond
*
* @author Sijia Liu
*/
#pragma once

#include"tradebookingservice.hpp"
#include"products.hpp"


/*
* Service defined for bond
* Implement all the method from base class for bond
*/
class BondTradeBookingService : public TradeBookingService<Bond>
{
private:
	//map to store service data as <key, value>
	map<string, Trade<Bond>> servicedata;

	//vector of listener
	vector< ServiceListener<Trade<Bond>>* > listeners;

public:
	//ctor
	BondTradeBookingService() = default;

	// Get data on our service given a key
	virtual Trade<Bond>& GetData(string key);

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(Trade<Bond> &data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<Trade<Bond>> *listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<Trade<Bond>>* >& GetListeners() const;

	// Book the trade
	virtual void BookTrade(Trade<Bond> &trade);
};

void BondTradeBookingService::BookTrade(Trade<Bond> &trade)
{
	//should key on tradeid
	string key = trade.GetTradeId();
	servicedata.emplace(key, trade);

	//notify listener
	for (auto &item : GetListeners())
	{
		item->ProcessAdd(trade);
	}
}

Trade<Bond>& BondTradeBookingService::GetData(string key)
{
	return servicedata[key];
}

void BondTradeBookingService::OnMessage(Trade<Bond> &data)
{
	//when a trade data come in, we should book the trade
	BookTrade(data);
}

void BondTradeBookingService::AddListener(ServiceListener<Trade<Bond>> *listener)
{
	listeners.push_back(listener);
}

const vector< ServiceListener<Trade<Bond>>* >& BondTradeBookingService::GetListeners() const
{
	return listeners;
}