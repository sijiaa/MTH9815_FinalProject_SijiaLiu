/**
* BondInquiryServiceListener.hpp
* The Listener specific for BondInquiryService
*
* @author Sijia Liu
*/
#pragma once

#include"soa.hpp"
#include"products.hpp"
#include"bondinquiryservicechangestateconnector.hpp"

/*
Service Listener for Bond Inquiry Service.
When the BondInquiryService which sends back a quote when the inquiry is in the RECEIVED state,
the service listener flow the data to a connect to publish to outside world
*/
class BondInquiryServiceListener :public ServiceListener<Inquiry<Bond>>
{
private:
	BondIquiryServiceChangeStateConnector &changestateconnector;
public:
	//ctor
	BondInquiryServiceListener(BondIquiryServiceChangeStateConnector &_changestateconnector);

	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(Inquiry<Bond> &data);

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(Inquiry<Bond> &data);

	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(Inquiry<Bond> &data);
};

BondInquiryServiceListener::BondInquiryServiceListener(BondIquiryServiceChangeStateConnector &_changestateconnector)
	:changestateconnector(_changestateconnector) {}


void BondInquiryServiceListener::ProcessAdd(Inquiry<Bond> &data)
{

}

void BondInquiryServiceListener::ProcessRemove(Inquiry<Bond> &data)
{

}

void BondInquiryServiceListener::ProcessUpdate(Inquiry<Bond> &data)
{
	//if the state id received, flow the data to connector
	if (data.GetState() == RECEIVED)
	{
		//then the connector publish it to the outside world
		changestateconnector.Publish(data);
	}
}
