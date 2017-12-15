/**
* RiskServiceSpecConnector.hpp
* The Connector specific for vector <PV01<BucketedSector<Bond>>>
* Used to write data to txt file
*
* @author Sijia Liu
*/
#pragma once
#pragma warning( disable : 4996)

#include"soa.hpp"
#include"riskservice.hpp"
#include<fstream>
#include<chrono>

class RiskServiceSpecConnector : public Connector<vector <PV01<BucketedSector<Bond>>>>
{
private:
	//the file that the listener write data to
	string file;
	ofstream outf;
public:
	//ctor
	RiskServiceSpecConnector(string _file);
	~RiskServiceSpecConnector();

	//write the data to txt file
	virtual void Publish(vector <PV01<BucketedSector<Bond>>> &data);
};

RiskServiceSpecConnector::RiskServiceSpecConnector(string _file)
	:file(_file) 
{
	outf = ofstream(file);
}


RiskServiceSpecConnector::~RiskServiceSpecConnector()
{
	outf.close();
}

void RiskServiceSpecConnector::Publish(vector <PV01<BucketedSector<Bond>>> &data)
{
	auto n = chrono::system_clock::now();
	std::time_t t = chrono::system_clock::to_time_t(n);
	outf << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S") << "," ;
	for (int i = 0; i < data.size(); ++i)
	{
		outf << data[i].GetProduct().GetName() << ",";
		outf << data[i].GetPV01() << ",";
		outf << data[i].GetQuantity() << ",";
		
	}
	outf << endl;
	outf << flush;
}