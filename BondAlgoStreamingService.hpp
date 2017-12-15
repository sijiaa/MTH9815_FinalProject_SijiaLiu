/**
* BondAlgoStreamingService.hpp
* The AlgoStreamingService specific for bond
*
* @author Sijia Liu
*/
#pragma once

#include"products.hpp"
#include"algostreamingservice.hpp"

/*
* Service defined for bond
* Implement all the method from base class for bond
*/
class BondAlgoStreamingService :public AlgoStreamingService<Bond>
{
private:
	//map to store service data as <key, value>
	map<string, AlgoStream<Bond>> servicedata;

	//vector of listener
	vector< ServiceListener<AlgoStream<Bond>>* > listeners;

public:
	// Get data on our service given a key
	virtual AlgoStream<Bond>& GetData(string key);

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(AlgoStream<Bond> &data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<AlgoStream<Bond>> *listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<AlgoStream<Bond>>* >& GetListeners() const;

	//generate stream according to Price object
	virtual void GenerateStream(Price<Bond> &price);
};

void BondAlgoStreamingService::GenerateStream(Price<Bond> &price) 
{
	string key = price.GetProduct().GetProductId();
	if (servicedata.find(key) != servicedata.end())
	{
		servicedata[key].algo(price);

	}
	else
	{
		AlgoStream<Bond> newalgo(price.GetProduct());
		servicedata.emplace(key, newalgo);
		servicedata[key].algo(price);
	}

	//add on the service listeners
	for (auto &item : GetListeners())
	{
		item->ProcessAdd(servicedata[key]);
	}
}

AlgoStream<Bond>& BondAlgoStreamingService::GetData(string key)
{
	return servicedata[key];
}

void BondAlgoStreamingService::OnMessage(AlgoStream<Bond> &data)
{
	string key = data.GetProduct().GetProductId();
	servicedata.emplace(key, data);
}

void BondAlgoStreamingService::AddListener(ServiceListener<AlgoStream<Bond>> *listener)
{
	listeners.push_back(listener);
}

const vector< ServiceListener<AlgoStream<Bond>>* >& BondAlgoStreamingService::GetListeners() const
{
	return listeners;
}