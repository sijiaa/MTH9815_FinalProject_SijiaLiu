/**
* BondHistoricalDataService.hpp
* The HistoricalDataService specific for bond
*
* @author Sijia Liu
*/
#pragma once
#include"historicaldataservice.hpp"
#include"products.hpp"
#include"BondHistoricalDataServiceConnector.hpp"
#include"BondRiskService.hpp"

/*
* Service defined for bond
* Implement all the method from base class for bond
* With T as template class
*/
template<typename T>
class BondHistoricalDataService :public HistoricalDataService<T>
{
private:
	//map to store service data as <key, value>
	map<string, T> servicedata;

	//vector of listener
	vector< ServiceListener<T>* > listeners;

public:
	// Get data on our service given a key
	virtual T& GetData(string key);

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(T &data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<T> *listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<T>* >& GetListeners() const;

	// Persist data to a store
	void PersistData(string persistKey,  T& data);
};

template<typename T>
void BondHistoricalDataService<T>::PersistData(string persistKey,  T& data)
{
	servicedata.emplace(persistKey, data);
	for (auto &item : GetListeners())
	{
		item->ProcessAdd(data);
	}

}

template<typename T>
T& BondHistoricalDataService<T>::GetData(string key)
{
	return servicedata[key];
}

template<typename T>
void BondHistoricalDataService<T>::OnMessage(T &data)
{
	string key = data.GetProduct().GetProductId();
	servicedata.emplace(key, data);
}

template<typename T>
void BondHistoricalDataService<T>::AddListener(ServiceListener<T> *listener)
{
	listeners.push_back(listener);
}

template<typename T>
const vector< ServiceListener<T>* >& BondHistoricalDataService<T>::GetListeners() const
{
	return listeners;
}

