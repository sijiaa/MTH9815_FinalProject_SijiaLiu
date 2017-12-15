/**
* BondPricingServiceListener.hpp
* The Listener specific for BondPricingService
*
* @author Sijia Liu
*/
#pragma once

#include"soa.hpp"
#include"products.hpp"
#include"BondAlgoStreamingService.hpp"


/*
Listener for BondPricingService
datamember: BondAlgoStreamingService
Flow the Price<Bond> data to BondAlgoStreamingService
*/

class BondPricingServiceListener :public ServiceListener<Price<Bond>>
{
private:
	BondAlgoStreamingService &algoservice;
public:
	//ctor
	BondPricingServiceListener(BondAlgoStreamingService &_algoservice);

	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(Price<Bond> &data);

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(Price<Bond> &data);


	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(Price<Bond> &data);
};

BondPricingServiceListener::BondPricingServiceListener(BondAlgoStreamingService &_algoservice)
	:algoservice(_algoservice) {}


void BondPricingServiceListener::ProcessAdd(Price<Bond> &data)
{
	algoservice.GenerateStream(data);
}

void BondPricingServiceListener::ProcessRemove(Price<Bond> &data)
{

}

void BondPricingServiceListener::ProcessUpdate(Price<Bond> &data)
{

}
