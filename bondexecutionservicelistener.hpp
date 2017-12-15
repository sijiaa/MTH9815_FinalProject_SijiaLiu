/**
* BondExecutionServiceListener.hpp
* The Listener specific for BondExecutionService
*
* @author Sijia Liu
*/
#pragma once

#include"soa.hpp"
#include"products.hpp"
#include"executionservice.hpp"
#include"BondTradeBookingService.hpp"


/*
Listener for BondExecutionService
datamember: BondTradeBookingService
Flow the ExecutionOrder<Bond> data to BondTradeBookingService
*/

class BondExecutionServiceListener :public ServiceListener<ExecutionOrder<Bond>>
{
public:
	//ctor
	BondExecutionServiceListener(BondTradeBookingService &_bookingservice);

	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(ExecutionOrder<Bond> &data);

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(ExecutionOrder<Bond> &data);


	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(ExecutionOrder<Bond> &data);

private:
	BondTradeBookingService &bookingservice;
	string book;
	//use to generate monotone trade id
	int n;
};


BondExecutionServiceListener::BondExecutionServiceListener(BondTradeBookingService &_bookingservice)
	:bookingservice(_bookingservice), n(0) {}

void BondExecutionServiceListener::ProcessAdd(ExecutionOrder<Bond> &data)
{
	//get ExecutionOrder from bond execution service
	//need to change to Trade to invoke the booktrade method on BondTradeBookingService
	Side side;
	if (data.GetPricingSide() == BID)
	{
		side = SELL;
	}
	else
	{
		side = BUY;
	}

	//generate tradeid?
	string tradeid = "marketaggresstrade" + to_string(n++);
	Trade<Bond> newtrade(data.GetProduct(), tradeid, data.GetPrice(), book, data.GetVisibleQuantity(), side);

	//update the book(should cycle through TRSY1, TRSY2, TRSY3)
	if (book == "TRSY1")
	{
		book = "TRSY2";
	}
	else if (book == "TRSY2")
	{
		book = "TRSY3";
	}
	else
	{
		book = "TRSY1";
	}

	bookingservice.BookTrade(newtrade);
}

void BondExecutionServiceListener::ProcessRemove(ExecutionOrder<Bond> &data)
{

}

void BondExecutionServiceListener::ProcessUpdate(ExecutionOrder<Bond> &data)
{
	
}