/**
* BondPricingService.hpp
* The PricingService specific for bond
*
* @author Sijia Liu
*/
#pragma once

#include"pricingservice.hpp"
#include"products.hpp"

/*
* Service defined for bond
* Implement all the method from base class for bond
*/
class BondPricingService :public PricingService<Bond>
{
private:
	//map to store service data as <key, value>
	map<string, Price<Bond>> servicedata;

	//vector of listener
	vector< ServiceListener<Price<Bond>>* > listeners;

public:
	// Get data on our service given a key
	virtual Price<Bond>& GetData(string key);

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(Price<Bond> &data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<Price<Bond>> *listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<Price<Bond>>* >& GetListeners() const;
};

Price<Bond>& BondPricingService::GetData(string key)
{
	return servicedata[key];
}

void BondPricingService::OnMessage(Price<Bond> &data)
{
	//important since data comes from connector
	string key = data.GetProduct().GetProductId();
	servicedata.emplace(key, data);;

	//after a price come in, notify the listener
	for (auto &item : GetListeners())
	{
		item->ProcessAdd(data);
	}
}

void BondPricingService::AddListener(ServiceListener<Price<Bond>> *listener)
{
	listeners.push_back(listener);
}

const vector< ServiceListener<Price<Bond>>* >& BondPricingService::GetListeners() const
{
	return listeners;
}
