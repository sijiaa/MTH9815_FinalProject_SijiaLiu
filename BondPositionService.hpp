/**
* BondPositionService.hpp
* The PositionService specific for bond
*
* @author Sijia Liu
*/
#pragma once

#include"positionservice.hpp"
#include"products.hpp"

/*
* Service defined for bond
* Implement all the method from base class for bond
*/
class BondPositionService :public PositionService<Bond>
{
private:

	//map to store service data as <key, value>
	map<string, Position<Bond>> servicedata;

	//vector of listener
	vector< ServiceListener<Position<Bond>>* > listeners;

public:
	//ctor
	BondPositionService() = default;

	// Get data on our service given a key
	virtual Position<Bond>& GetData(string key);

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(Position<Bond> &data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<Position<Bond>> *listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<Position<Bond>>* >& GetListeners() const;

	// Add a trade to the service
	virtual void AddTrade(Trade<Bond> &trade);

};



void BondPositionService::AddTrade(Trade<Bond> &trade)
{
	//when a trade come in, we should update the position in the service data
	string key = trade.GetProduct().GetProductId();
	if (servicedata.find(key) != servicedata.end())
	{
		servicedata[key].UpdatePosition(trade.GetBook(), trade.GetQuantity(), trade.GetSide());
	}
	else
	{
		Position<Bond> newposition(trade.GetProduct());
		newposition.AddBook(trade.GetBook());
		newposition.UpdatePosition(trade.GetBook(), trade.GetQuantity(), trade.GetSide());
		
		servicedata.emplace(key, newposition);
	}

	//update the service listeners
	for (auto &item : GetListeners())
	{
		item->ProcessUpdate(servicedata[key]);
	}
	
}

Position<Bond>& BondPositionService::GetData(string key)
{
	return servicedata[key];
}

void BondPositionService::OnMessage(Position<Bond> &data)
{
	//Actually no need because there is no connector for this class. All the data is flow from AddTrade

	string key = data.GetProduct().GetProductId();
	servicedata.emplace(key, data);
}

void BondPositionService::AddListener(ServiceListener<Position<Bond>> *listener)
{
	listeners.push_back(listener);
}

const vector< ServiceListener<Position<Bond>>* >& BondPositionService::GetListeners() const
{
	return listeners;
}
