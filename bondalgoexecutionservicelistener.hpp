/**
* BondAlgoExecutionServiceListener.hpp
* The Listener specific for BondAlgoExecutionService
*
* @author Sijia Liu
*/
#pragma once

#include"soa.hpp"
#include"products.hpp"
#include"BondExecutionService.hpp"
#include"algoexecutionservice.hpp"


/*
Listener for BondAlgoExecutionService
datamember: BondExecutionService
Flow the AlgoExecution<Bond> data to BondExecutionService
*/

class BondAlgoExecutionServiceListener :public ServiceListener<AlgoExecution<Bond>>
{
public:
	//ctor
	BondAlgoExecutionServiceListener(BondExecutionService &_executionservice);

	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(AlgoExecution<Bond> &data);

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(AlgoExecution<Bond> &data);


	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(AlgoExecution<Bond> &data);

private:
	BondExecutionService &executionservice;
};


BondAlgoExecutionServiceListener::BondAlgoExecutionServiceListener(BondExecutionService &_executionservice)
	:executionservice(_executionservice) {}

void BondAlgoExecutionServiceListener::ProcessAdd(AlgoExecution<Bond> &data)
{
    auto exe = data.GetExecutionOrder();
	executionservice.ExecuteOrder(exe, BROKERTEC);

}

void BondAlgoExecutionServiceListener::ProcessRemove(AlgoExecution<Bond> &data)
{

}

void BondAlgoExecutionServiceListener::ProcessUpdate(AlgoExecution<Bond> &data)
{

}

