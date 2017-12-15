/**
* BondRiskService.hpp
* The RiskService specific for bond
*
* @author Sijia Liu
*/
#pragma once
#include"riskservice.hpp"
#include"products.hpp"


/*
* Service defined for bond
* Implement all the method from base class for bond
*/
class BondRiskService :public RiskService<Bond>
{
private:
	//map to store service data as <key, value>
	map<string, PV01<Bond>> servicedata;

	//vector of listener
	vector< ServiceListener<PV01<Bond>>* > listeners;

	vector< ServiceListener<vector <PV01<BucketedSector<Bond>>>>*> spec_listeners;

	//store the PV01 of each product
	//will be used when constructing a PV01 object
	map<string, double> PV01map;

public:
	//ctor
	BondRiskService()
	{
		PV01map["30Y"] = 17.876;
		PV01map["10Y"] = 8.691;
		PV01map["7Y"] = 6.735;
		PV01map["5Y"] = 4.768;
		PV01map["3Y"] = 2.867;
		PV01map["2Y"] = 1.965;
	}
	// Get data on our service given a key
	virtual PV01<Bond>& GetData(string key);

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(PV01<Bond> &data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<PV01<Bond>> *listener); 
	void AddSpecListener(ServiceListener<vector <PV01<BucketedSector<Bond>>>>* spec_listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<PV01<Bond>>* >& GetListeners() const;
	virtual const vector< ServiceListener<vector <PV01<BucketedSector<Bond>>>>* >& GetSpecListeners() const;

	// Add a position that the service will risk
	virtual void AddPosition(Position<Bond> &position);

	// Get the bucketed risk for the bucket sector
	virtual const PV01< BucketedSector<Bond> > GetBucketedRisk(const BucketedSector<Bond> &sector) ;
};





void BondRiskService::AddPosition(Position<Bond> &position)
{
	//when the position is updated, it should also be updated in PV01 
	//by changing the quantity of the product
	string key = position.GetProduct().GetProductId();
	if (servicedata.find(key) != servicedata.end())
	{
		//update
		servicedata[key].SetQuantity(position.GetAggregatePosition());
	}
	else
	{
		//create a new PV01 object
		//?? actual walue of pv01??
		double pv01 = PV01map[position.GetProduct().GetTicker()];
		PV01<Bond> newpv(position.GetProduct(), pv01, position.GetAggregatePosition());
		servicedata.emplace(key, newpv);
	}

	//update the service listeners
	for (auto &item : GetListeners())
	{
		item->ProcessUpdate(servicedata[key]);
	}
	for (auto &item : GetSpecListeners())
	{
		PV01<BucketedSector<Bond>> p2 = GetBucketedRisk(Belly);
		PV01<BucketedSector<Bond>> p1 = GetBucketedRisk(FrontEnd);
		
		PV01<BucketedSector<Bond>> p3 = GetBucketedRisk(LongEnd);
		vector<PV01<BucketedSector<Bond>>> vec{ p1,p2,p3 };
		item->ProcessUpdate(vec);
	}
	
}


//? to aggregate the risk
//ok to use double as return type?
const PV01<BucketedSector<Bond>> BondRiskService::GetBucketedRisk(const BucketedSector<Bond> &sector) 
{
	double totalpv01 = 0;
	long totalquantity = 0;
	for (auto &product : sector.GetProducts())
	{
		string key = product.GetProductId();
		if (servicedata.find(key) != servicedata.end())
		{
			totalpv01 += servicedata[key].GetPV01()*servicedata[key].GetQuantity();
			totalquantity += servicedata[key].GetQuantity();
		}
	}
	double pv01 = totalquantity == 0 ? 0 : totalpv01 / totalquantity;
	return PV01<BucketedSector<Bond>>(sector, pv01, totalquantity);
}

PV01<Bond>& BondRiskService::GetData(string key)
{
	return servicedata[key];
}

void BondRiskService::OnMessage(PV01<Bond> &data)
{
	string key = data.GetProduct().GetProductId();
	servicedata.emplace(key, data);
}


void BondRiskService::AddListener(ServiceListener<PV01<Bond>> *listener)
{
	listeners.push_back(listener);
}

void BondRiskService::AddSpecListener(ServiceListener<vector <PV01<BucketedSector<Bond>>>>* spec_listener)
{
	spec_listeners.push_back(spec_listener);
}

const vector< ServiceListener<PV01<Bond>>* >& BondRiskService::GetListeners() const
{
	return listeners;
}

const vector< ServiceListener<vector <PV01<BucketedSector<Bond>>>>* >& BondRiskService::GetSpecListeners() const
{
	return spec_listeners;
}
