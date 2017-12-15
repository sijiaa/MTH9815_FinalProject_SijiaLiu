/**
* BondInquiryService.hpp
* The InquiryService specific for bond
*
* @author Sijia Liu
*/
#pragma once
#include"inquiryservice.hpp"
#include"products.hpp"


/*
* Service defined for bond
* Implement all the method from base class for bond
*/
class BondInquiryService :public InquiryService<Bond>
{
private:
	//map to store service data as <key, value>
	map<string, Inquiry<Bond>> servicedata;

	//vector of listener
	vector< ServiceListener<Inquiry<Bond>>* > listeners;

public:
	// Get data on our service given a key
	virtual Inquiry<Bond>& GetData(string key);

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(Inquiry<Bond> &data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<Inquiry<Bond>> *listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<Inquiry<Bond>>* >& GetListeners() const;


	// Send a quote back to the client
	void SendQuote(const string &inquiryId, double price);

	// Reject an inquiry from the client
	void RejectInquiry(const string &inquiryId);
};

void BondInquiryService::SendQuote(const string &inquiryId, double price)
{
	//update with the quoted price
	servicedata[inquiryId].UpdatePrice(price);

	//make update to listeners
	//update with quoted price
	for (auto &item : GetListeners())
	{
		item->ProcessUpdate(servicedata[inquiryId]);
	}
}

void BondInquiryService::RejectInquiry(const string &inquiryId)
{

	//change to REJECTED state and update in servicedata
	servicedata[inquiryId].UpdateState(REJECTED);

	//make update to listeners
	for (auto &item : GetListeners())
	{
		item->ProcessUpdate(servicedata[inquiryId]);
	}
}

Inquiry<Bond>& BondInquiryService::GetData(string key)
{
	return servicedata[key];
}

void BondInquiryService::OnMessage(Inquiry<Bond> &data)
{
	string key = data.GetInquiryId();
	servicedata.emplace(key, data);

	//add the new inquiry to listener
	for (auto &item : GetListeners())
	{
		item->ProcessAdd(data);
	}
	if (data.GetState() == RECEIVED)
	{
		//hard code part, price always 100
		double price = 100;
		SendQuote(key,price);
	}
	else if (data.GetState() == QUOTED)
	{
		servicedata[key].UpdateState(DONE);
		for (auto &item : GetListeners())
		{
			item->ProcessUpdate(servicedata[key]);
		}
	}
}

void BondInquiryService::AddListener(ServiceListener<Inquiry<Bond>> *listener)
{
	listeners.push_back(listener);
}

const vector< ServiceListener<Inquiry<Bond>>* >& BondInquiryService::GetListeners() const
{
	return listeners;
}