/**
* BondGUIServiceListener.hpp
* The Listener specific for BondGUIService
*
* @author Sijia Liu
*/
#pragma once

#include"soa.hpp"
#include"products.hpp"
#include"pricingservice.hpp"
#include"bondguiservicewriteconnector.hpp"

/*
Listener for BondGUIServiceListener
datamember: BondGUIServiceWriteConnector
Flow the Price<Bond> data to BondGUIServiceWriteConnector
*/

class BondGUIServiceListener :public ServiceListener<Price<Bond>>
{
private:
	BondGUIServiceWriteConnector &guiconnector;
public:
	//ctor
	BondGUIServiceListener(BondGUIServiceWriteConnector &_guiconnector);

	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(Price<Bond> &data);

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(Price<Bond> &data);


	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(Price<Bond> &data);
};

BondGUIServiceListener::BondGUIServiceListener(BondGUIServiceWriteConnector &_guiconnector)
	:guiconnector(_guiconnector) {}


void BondGUIServiceListener::ProcessAdd(Price<Bond> &data)
{
	
}

void BondGUIServiceListener::ProcessRemove(Price<Bond> &data)
{

}

void BondGUIServiceListener::ProcessUpdate(Price<Bond> &data)
{
	guiconnector.Publish(data);
}
