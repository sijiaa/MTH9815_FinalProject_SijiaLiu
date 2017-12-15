/**
* BondTradeBookingServiceListener.hpp
* The Listener specific for BondTradeBookingService
*
* @author Sijia Liu
*/
#pragma once

#include"soa.hpp"
#include"products.hpp"
#include"BondPositionService.hpp"

/*
Listener for BondTradeBookingService
datamember: BondPositionService
Flow the Trade<Bond> data to BondPositionService
*/

class BondTradeBookingServiceListener :public ServiceListener<Trade<Bond>>
{
private:
	BondPositionService &positionservice;
public:
	//ctor
	BondTradeBookingServiceListener(BondPositionService &_positionservice);

	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(Trade<Bond> &data);

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(Trade<Bond> &data);
	

	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(Trade<Bond> &data);
	
};

BondTradeBookingServiceListener::BondTradeBookingServiceListener(BondPositionService &_positionservice)
	:positionservice(_positionservice) {}


void BondTradeBookingServiceListener::ProcessAdd(Trade<Bond> &data)
{
	positionservice.AddTrade(data);
}

void BondTradeBookingServiceListener::ProcessRemove(Trade<Bond> &data)
{
	
}

void BondTradeBookingServiceListener::ProcessUpdate(Trade<Bond> &data)
{
	
}

