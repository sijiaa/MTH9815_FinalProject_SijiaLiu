/**
* BondMarketDataService.hpp
* The MarketDataService specific for bond
*
* @author Sijia Liu
*/
#pragma once
#include"marketdataservice.hpp"
#include"products.hpp"

/*
* Service defined for bond
* Implement all the method from base class for bond
*/
class BondMarketDataService :public MarketDataService<Bond>
{
private:
	//map to store service data as <key, value>
	map<string, OrderBook<Bond>> servicedata;

	//vector of listener
	vector< ServiceListener<OrderBook<Bond>>* > listeners;

public:
	//ctor
	BondMarketDataService() = default;

	// Get data on our service given a key
	virtual OrderBook<Bond>& GetData(string key);

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(OrderBook<Bond> &data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<OrderBook<Bond>> *listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<OrderBook<Bond>>* >& GetListeners() const;


	// Get the best bid/offer order
	virtual const BidOffer GetBestBidOffer(const string &productId);

	// Aggregate the order book
	virtual const OrderBook<Bond>& AggregateDepth(const string &productId);
};



const BidOffer BondMarketDataService::GetBestBidOffer(const string &productId)
{
	//The top of order book has smallest spread
	OrderBook<Bond> order = servicedata[productId];
	Order bidOrder = order.GetBidStack()[0];
	Order offerOrder = order.GetOfferStack()[0];
	return BidOffer(bidOrder, offerOrder);

}


//aggregate multiple order with same price
const OrderBook<Bond>& BondMarketDataService::AggregateDepth(const string &productId)
{
	OrderBook<Bond> order = servicedata[productId];
	vector<Order> bidOrder = order.GetBidStack();
	for (int i = 1; i < bidOrder.size(); ++i)
	{
		if (bidOrder[i].GetPrice() == bidOrder[i - 1].GetPrice())
		{
			bidOrder[i - 1].AddQuantity(bidOrder[i].GetQuantity());
		}
		bidOrder.erase(bidOrder.begin() + i);
	}
	vector<Order> offerOrder = order.GetOfferStack();
	for (int i = 1; i < offerOrder.size(); ++i)
	{
		if (offerOrder[i].GetPrice() == offerOrder[i - 1].GetPrice())
		{
			offerOrder[i - 1].AddQuantity(offerOrder[i].GetQuantity());
		}
		offerOrder.erase(offerOrder.begin() + i);
	}

	return OrderBook<Bond>(order.GetProduct(), bidOrder, offerOrder);
}


OrderBook<Bond>& BondMarketDataService::GetData(string key)
{
	return servicedata[key];
}

void BondMarketDataService::OnMessage(OrderBook<Bond> &data)
{
	//Market data service get data from connector from txt file
	string key = data.GetProduct().GetProductId();
	servicedata.emplace(key, data);

	//notify the service listener about the updataed market data(the total orderbook)
	for (auto &item : GetListeners())
	{
		item->ProcessUpdate(data);
	}
}

void BondMarketDataService::AddListener(ServiceListener<OrderBook<Bond>> *listener)
{
	listeners.push_back(listener);
}

const vector< ServiceListener<OrderBook<Bond>>* >& BondMarketDataService::GetListeners() const
{
	return listeners;
}