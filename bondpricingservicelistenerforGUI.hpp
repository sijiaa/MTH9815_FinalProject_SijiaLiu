#pragma once

#include"soa.hpp"
#include"products.hpp"
#include"BondGUIService.hpp"


/*
Listener for BondPricingService
datamember: BondAlgoStreamingService
Flow the Price<Bond> data to BondAlgoStreamingService
*/

class BondPricingServiceListenerforGUI :public ServiceListener<Price<Bond>>
{
private:
	BondGUIService &guiservice;
public:
	//ctor
	BondPricingServiceListenerforGUI(BondGUIService &_guiservice);

	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(Price<Bond> &data);

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(Price<Bond> &data);


	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(Price<Bond> &data);
};

BondPricingServiceListenerforGUI::BondPricingServiceListenerforGUI(BondGUIService &_guiservice)
	:guiservice(_guiservice) {}


void BondPricingServiceListenerforGUI::ProcessAdd(Price<Bond> &data)
{
	guiservice.OnMessage(data);
}

void BondPricingServiceListenerforGUI::ProcessRemove(Price<Bond> &data)
{

}

void BondPricingServiceListenerforGUI::ProcessUpdate(Price<Bond> &data)
{
	
}

