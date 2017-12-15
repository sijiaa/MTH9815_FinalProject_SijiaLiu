/**
* BondAlgoExecutionService.hpp
* The AlgoExecutionService specific for bond
*
* @author Sijia Liu
*/
#pragma once

#include"products.hpp"
#include"algoexecutionservice.hpp"


/*
* Service defined for bond
* Implement all the method from base class for bond
*/
class BondAlgoExecutionService :public AlgoExecutionService<Bond>
{
private:
	//map to store service data as <key, value>
	map<string, AlgoExecution<Bond>> servicedata;

	//vector of listener
	vector< ServiceListener<AlgoExecution<Bond>>* > listeners;

public:
	// Get data on our service given a key
	virtual AlgoExecution<Bond>& GetData(string key);

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(AlgoExecution<Bond> &data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<AlgoExecution<Bond>> *listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<AlgoExecution<Bond>>* >& GetListeners() const;

	//when a new orderbook come in, generate on order base on the orderbook using an algo
	virtual void GenerateOrder(OrderBook <Bond> &book);
};



void BondAlgoExecutionService::GenerateOrder(OrderBook<Bond> &book)
{
	string key = book.GetProduct().GetProductId();
	bool signal;
	if (servicedata.find(key) != servicedata.end())
	{
		signal = servicedata[key].algo(book);

	}
	else
	{
		Bond mybond = book.GetProduct();
		AlgoExecution<Bond> newalgo(mybond);
		servicedata.emplace(key, newalgo);;
		signal = servicedata[key].algo(book);
	}

	//add on the service listeners if we generate a trade
	if (signal == true)
	{
		for (auto &item : GetListeners())
		{
			item->ProcessAdd(servicedata[key]);
		}
	}


}

AlgoExecution<Bond>& BondAlgoExecutionService::GetData(string key)
{
	return servicedata[key];
}

void BondAlgoExecutionService::OnMessage(AlgoExecution<Bond> &data)
{
	string key = data.GetProduct().GetProductId();
	servicedata.emplace(key, data);
}

void BondAlgoExecutionService::AddListener(ServiceListener<AlgoExecution<Bond>> *listener)
{
	listeners.push_back(listener);
}

const vector< ServiceListener<AlgoExecution<Bond>>* >& BondAlgoExecutionService::GetListeners() const
{
	return listeners;
}