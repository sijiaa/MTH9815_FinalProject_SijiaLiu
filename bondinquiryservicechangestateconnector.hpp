/**
* BondIquiryServiceChangeStateConnector.hpp
* Used to change the inquiry state
*
* @author Sijia Liu
*/
#pragma once

#include"soa.hpp"
#include"products.hpp"

#include"BondInquiryService.hpp"

/*
Connector for BondInquiryService
subscrible only
flow Inquiry<Bond> data to the service from txt file via onMessage

*/
class BondIquiryServiceChangeStateConnector :public Connector<Inquiry<Bond>>
{
public:
	//ctor
	BondIquiryServiceChangeStateConnector(BondInquiryService &_inquiryservice);

	// Publish data to the outside world
	//for this service, this connector send the quote back to market
	virtual void Publish(Inquiry<Bond> &data);

	//Get the quoted inquiry back from market and flow the data into service
	void Subscribe();

private:
	BondInquiryService &inquiryservice;

};

BondIquiryServiceChangeStateConnector::BondIquiryServiceChangeStateConnector(BondInquiryService &_inquiryservice)
	:inquiryservice(_inquiryservice) {}

void BondIquiryServiceChangeStateConnector::Publish(Inquiry<Bond> &data)
{
	//In our implementation, we just change the state and send back to service
	if (data.GetState() == RECEIVED)
	{
		data.UpdateState(QUOTED);
		inquiryservice.OnMessage(data);
	}
	

}

void BondIquiryServiceChangeStateConnector::Subscribe()
{

}