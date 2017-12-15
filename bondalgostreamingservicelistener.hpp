/**
* BondAlgoStreamingServiceListener.hpp
* The Listener specific for BondAlgoStreamingService
*
* @author Sijia Liu
*/
#pragma once

#include"soa.hpp"
#include"products.hpp"
#include"BondStreamingService.hpp"
#include"algostreamingservice.hpp"


/*
Listener for BondAlgoStreamingService
datamember: BondStreamingService
Flow the AlgoStream<Bond> data to BondStreamingService
*/

class BondAlgoStreamingServiceListener :public ServiceListener<AlgoStream<Bond>>
{
public:
	//ctor
	BondAlgoStreamingServiceListener(BondStreamingService &_streamingservice);

	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(AlgoStream<Bond> &data);

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(AlgoStream<Bond> &data);


	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(AlgoStream<Bond> &data);

private:
	BondStreamingService &streamingservice;
};


BondAlgoStreamingServiceListener::BondAlgoStreamingServiceListener(BondStreamingService &_streamingservice)
	:streamingservice(_streamingservice) {}


void BondAlgoStreamingServiceListener::ProcessAdd(AlgoStream<Bond> &data)
{
	streamingservice.PublishPrice(data.GetPriceStream());

}

void BondAlgoStreamingServiceListener::ProcessRemove(AlgoStream<Bond> &data)
{

}

void BondAlgoStreamingServiceListener::ProcessUpdate(AlgoStream<Bond> &data)
{

}

