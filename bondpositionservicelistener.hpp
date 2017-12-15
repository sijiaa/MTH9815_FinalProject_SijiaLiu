/**
* BondPositionServiceListener.hpp
* The Listener specific for BondPositionService
*
* @author Sijia Liu
*/
#pragma once

#include"soa.hpp"
#include"products.hpp"
#include"BondRiskService.hpp"

/*
Listener for BondPositionServiceListener
datamember: BondRiskService
Flow the Position<Bond> data to BondRiskService
*/
class BondPositionServiceListener : public ServiceListener<Position<Bond>>
{
private:
	BondRiskService &riskservice;
public:
	//ctor
	BondPositionServiceListener(BondRiskService &_riskservice);

	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(Position<Bond> &data);

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(Position<Bond> &data);


	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(Position<Bond> &data);
};

BondPositionServiceListener::BondPositionServiceListener(BondRiskService &_riskservice)
	:riskservice(_riskservice) {}



void BondPositionServiceListener::ProcessAdd(Position<Bond> &data)
{

}

void BondPositionServiceListener::ProcessRemove(Position<Bond> &data)
{

}

void BondPositionServiceListener::ProcessUpdate(Position<Bond> &data)
{
	riskservice.AddPosition(data);
}
