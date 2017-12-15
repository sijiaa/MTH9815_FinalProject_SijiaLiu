/**
* BondAlgoStreamingService.hpp
* The AlgoStreamingService specific for bond
*
* @author Sijia Liu
*/
#pragma once

#include"executionservice.hpp"
#include"products.hpp"

/*
* Service defined for bond
* Implement all the method from base class for bond
*/
class BondExecutionService :public ExecutionService<Bond>
{
private:
	//map to store service data as <key, value>
	map<string, ExecutionOrder<Bond>> servicedata;

	//vector of listener
	vector< ServiceListener<ExecutionOrder<Bond>>* > listeners;

public:
	// Get data on our service given a key
	virtual ExecutionOrder<Bond>& GetData(string key);

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(ExecutionOrder<Bond> &data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<ExecutionOrder<Bond>> *listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<ExecutionOrder<Bond>>* >& GetListeners() const;


	// Execute an order on a market
	void ExecuteOrder(ExecutionOrder<Bond>& order, Market market);
};



void BondExecutionService::ExecuteOrder(ExecutionOrder<Bond>& order, Market market)
{
	//do something to execute the order on the market
	//in this program it is simplified

	//add to servicedata
	string key = order.GetProduct().GetProductId();
	servicedata.emplace(key, order);

	//notify the listeners
	for (auto &item : GetListeners())
	{
		item->ProcessAdd(order);
	}
}

ExecutionOrder<Bond>& BondExecutionService::GetData(string key)
{
	return servicedata[key];
}

void BondExecutionService::OnMessage(ExecutionOrder<Bond> &data)
{
	string key = data.GetProduct().GetProductId();
	servicedata.emplace(key, data);
}

void BondExecutionService::AddListener(ServiceListener<ExecutionOrder<Bond>> *listener)
{
	listeners.push_back(listener);
}

const vector< ServiceListener<ExecutionOrder<Bond>>* >& BondExecutionService::GetListeners() const
{
	return listeners;
}