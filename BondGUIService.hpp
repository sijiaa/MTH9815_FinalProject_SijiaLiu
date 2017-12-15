/**
* BondGUIService.hpp
* The GUIService specific for bond
*
* @author Sijia Liu
*/
#pragma once

#include"soa.hpp"
#include"products.hpp"
#include"guiservice.hpp"

#include <chrono>
#include <thread>

/*
* Service defined for bond
* Implement all the method from base class for bond
*/
class BondGUIService :public GuiService<Bond>
{
private:
	//
	std::chrono::steady_clock::time_point service_clock;
	int n;

	// map to store service data as <key, value>
	map<string, Price<Bond>> servicedata;

	//vector of listener
	vector< ServiceListener<Price<Bond>>* > listeners;


public:
	//ctor
	BondGUIService();

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


BondGUIService::BondGUIService()
{
	service_clock = std::chrono::high_resolution_clock::now();
	n = 0;
}


Price<Bond>& BondGUIService::GetData(string key)
{
	return servicedata[key];
}

void BondGUIService::OnMessage(Price<Bond> &data)
{
	string key = data.GetProduct().GetProductId();
	servicedata.emplace(key, data);

	//notify the listener every 30 second
	std::chrono::steady_clock::time_point newtime = std::chrono::high_resolution_clock::now();
	auto temp = newtime - service_clock;
	std::chrono::duration<int, std::milli> step = 
		std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(temp);
	if (step.count() >= 300 && n<100)
	{
		for (auto &item : GetListeners())
		{
			item->ProcessUpdate(data);
		}
		service_clock = std::chrono::high_resolution_clock::now();
		++n;
	}

	
}

void BondGUIService::AddListener(ServiceListener<Price<Bond>> *listener)
{
	listeners.push_back(listener);
}

const vector< ServiceListener<Price<Bond>>* >& BondGUIService::GetListeners() const
{
	return listeners;
}