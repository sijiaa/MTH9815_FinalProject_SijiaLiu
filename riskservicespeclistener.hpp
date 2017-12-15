/**
* RiskServiceSpecListener.hpp
* The Special Listenerfor BondRiskService
* with vector <PV01<BucketedSector<Bond>>> as value
*
* @author Sijia Liu
*/
#pragma once

#include"soa.hpp"
#include"products.hpp"
#include"riskservice.hpp"
#include"riskservicespecconnector.hpp"

class RiskServiceSpecListener :public ServiceListener<vector <PV01<BucketedSector<Bond>>>>
{
public:
	//ctor
	RiskServiceSpecListener(RiskServiceSpecConnector &_specconnector);

	// Listener callback to process an add event to the Service
	virtual void ProcessAdd(vector <PV01<BucketedSector<Bond>>> &data);

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(vector <PV01<BucketedSector<Bond>>> &data);

	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(vector <PV01<BucketedSector<Bond>>> &data);

private:
	RiskServiceSpecConnector &specconnector;
};


RiskServiceSpecListener::RiskServiceSpecListener(RiskServiceSpecConnector &_specconnector)
	:specconnector(_specconnector) {}


void RiskServiceSpecListener::ProcessAdd(vector <PV01<BucketedSector<Bond>>> &data)
{

}

void RiskServiceSpecListener::ProcessRemove(vector <PV01<BucketedSector<Bond>>> &data)
{

}

void RiskServiceSpecListener::ProcessUpdate(vector <PV01<BucketedSector<Bond>>> &data)
{
	specconnector.Publish(data);
}
