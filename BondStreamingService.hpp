/**
* BondStreamingService.hpp
* The StreamingService specific for bond
*
* @author Sijia Liu
*/
#pragma once
#include"streamingservice.hpp"
#include"products.hpp"


/*
* Service defined for bond
* Implement all the method from base class for bond
*/
class BondStreamingService : public StreamingService<Bond>
{
private:
	//map to store service data as <key, value>
	map<string, PriceStream<Bond>> servicedata;

	//vector of listener
	vector< ServiceListener<PriceStream<Bond>>* > listeners;

public:
	// Get data on our service given a key
	virtual PriceStream<Bond>& GetData(string key);

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(PriceStream<Bond> &data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<PriceStream<Bond>> *listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<PriceStream<Bond>>* >& GetListeners() const;


	// Publish two-way prices
	void PublishPrice(const PriceStream<Bond>& priceStream);
};


void BondStreamingService::PublishPrice(const PriceStream<Bond>& priceStream)
{
	//?how to implement
	//stream prices to markets as limit orders 
	//or just as an open one-way stream (depending on the market)

	//add to servicedata
	string key = priceStream.GetProduct().GetProductId();
	servicedata[key] = priceStream;

	//notify the listeners
	for (auto &item : GetListeners())
	{
		item->ProcessAdd(servicedata[key]);
	}

}

PriceStream<Bond>& BondStreamingService::GetData(string key)
{
	return servicedata[key];
}

void BondStreamingService::OnMessage(PriceStream<Bond> &data)
{
	string key = data.GetProduct().GetProductId();
	servicedata[key] = data;
}

void BondStreamingService::AddListener(ServiceListener<PriceStream<Bond>> *listener)
{
	listeners.push_back(listener);
}

const vector< ServiceListener<PriceStream<Bond>>* >& BondStreamingService::GetListeners() const
{
	return listeners;
}
