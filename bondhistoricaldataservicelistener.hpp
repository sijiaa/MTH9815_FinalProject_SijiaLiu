/**
* BondHistoricalDataServiceListener.hpp
* The Listener specific for BondHistoricalDataService
* Implement as template class
*
* @author Sijia Liu
*/
#pragma once
#include"soa.hpp"
#include"products.hpp"
#include"BondHistoricalDataService.hpp"

/*
Listener for BondHistoricalDataServiceListener
datamember: BondHistoricalDataService
Flow the T data to BondExecutionService
*/
template<typename T>
class BondHistoricalDataServiceListener :public ServiceListener<T>
{
private:
	//connector to publish persist object to txt files
	HistoricalDataServiceConnector<T>* connector;

public:
	//ctor
	BondHistoricalDataServiceListener(HistoricalDataServiceConnector<T>* _connector);

	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(T &data);

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(T &data);


	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(T &data);
};
template<typename T>
BondHistoricalDataServiceListener<T>::BondHistoricalDataServiceListener(HistoricalDataServiceConnector<T>* _connector)
	:connector(_connector) {}

template<typename T>
void BondHistoricalDataServiceListener<T>::ProcessAdd(T &data)
{
	connector->Publish(data);
}

template<typename T>
void BondHistoricalDataServiceListener<T>::ProcessRemove(T &data)
{

}

template<typename T>
void BondHistoricalDataServiceListener<T>::ProcessUpdate(T &data)
{
	connector->Publish(data);
}
