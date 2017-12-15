/**
* BondMarketDataServiceListener.hpp
* The Listener specific for BondMarketDataService
*
* @author Sijia Liu
*/
#pragma once

#include"soa.hpp"
#include"products.hpp"
#include"marketdataservice.hpp"
#include"BondAlgoExecutionService.hpp"

/*
Listener for BondMarketDataService
datamember: BondAlgoExecutionService
Flow the OrderBook<Bond> data to BondAlgoExecutionService
*/

class BondMarketDataServiceListener :public ServiceListener<OrderBook<Bond>>
{
private:
	BondAlgoExecutionService &algoservice;

public:
	//ctor
	BondMarketDataServiceListener(BondAlgoExecutionService &_algoservice);

	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(OrderBook<Bond> &data);

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(OrderBook<Bond> &data);


	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(OrderBook<Bond> &data);
};

BondMarketDataServiceListener::BondMarketDataServiceListener(BondAlgoExecutionService &_algoservice)
	:algoservice(_algoservice) {}


void BondMarketDataServiceListener::ProcessAdd(OrderBook<Bond> &data)
{

}

void BondMarketDataServiceListener::ProcessRemove(OrderBook<Bond> &data)
{

}

void BondMarketDataServiceListener::ProcessUpdate(OrderBook<Bond> &data)
{
	algoservice.GenerateOrder(data);
}
