#pragma once

#include"soa.hpp"
#include"products.hpp"
#include"BondHistoricalDataService.hpp"


/*
This is the service listener which HistoricalDataService register on other service
T can be Position<Bond>, PV01<Bond>, ExecutionOrder<Bond>, PriceStream<Bond>, Inquiry<Bond>
*/
template<typename T>
class ServiceListenerforHistoricalData :public ServiceListener<T>
{
public:
	//ctor
	ServiceListenerforHistoricalData(BondHistoricalDataService<T> &_dataservice);

	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(T &data);

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(T &data);

	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(T &data);

private:
	BondHistoricalDataService<T> &dataservice;
};


template<typename T>
ServiceListenerforHistoricalData<T>::ServiceListenerforHistoricalData(BondHistoricalDataService<T> &_dataservice)
	:dataservice(_dataservice) {}


template<typename T>
void ServiceListenerforHistoricalData<T>::ProcessAdd(T &data)
{
	string key = data.GetProduct().GetProductId();
	dataservice.PersistData(key, data);

}

template<typename T>
void ServiceListenerforHistoricalData<T>::ProcessRemove(T &data)
{

}

template<typename T>
void ServiceListenerforHistoricalData<T>::ProcessUpdate(T &data)
{
	string key = data.GetProduct().GetProductId();
	dataservice.PersistData(key, data);
}