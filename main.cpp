
#include"BondTradeBookingService.hpp"
#include"bondtradebookingserviceconnector.hpp"
#include"bondtradebookingservicelistener.hpp"
#include"BondPositionService.hpp"
#include"bondpositionservicelistener.hpp"
#include"BondRiskService.hpp"

#include"BondMarketDataService.hpp"
#include"bondmarketdataserviceconnector.hpp"
#include"bondmarketdataserviclistener.hpp"
#include"BondAlgoExecutionService.hpp"
#include"bondalgoexecutionservicelistener.hpp"
#include"BondExecutionService.hpp"
#include"bondexecutionservicelistener.hpp"

#include"BondPricingService.hpp"
#include"bondpricingserviceconnector.hpp"
#include"bondpricingservicelistener.hpp"
#include"BondAlgoStreamingService.hpp"
#include"bondalgostreamingservicelistener.hpp"
#include"BondStreamingService.hpp"

#include"BondInquiryService.hpp"
#include"bondinquiryservicereadfileconnector.hpp"
#include"bondinquiryservicelistener.hpp"
#include"bondinquiryservicechangestateconnector.hpp"

#include"BondHistoricalDataService.hpp"
#include"servicelistenerforhistoricaldata.hpp"
#include"bondhistoricaldataservicelistener.hpp"
#include"BondHistoricalDataServiceConnector.hpp"

#include"riskservicespecconnector.hpp"
#include"riskservicespeclistener.hpp"

#include"BondGUIService.hpp"
#include"bondpricingservicelistenerforGUI.hpp"
#include"bondguiservicelistener.hpp"
#include"bondguiservicewriteconnector.hpp"

#include"generatedata.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include"products.hpp"
using namespace std;

int main()
{
	//generate txt file
	//note that it takes about 10 min for each 6,000,000 data
	generateTrade(10);
	generateInquiry(10);
	generateMarketdata(1000);
	generatePrice(1000);
	
	//HISTORICAL SERVICE AND LISTENER, CONNECTOR
	//for position
	BondHistoricalDataService<Position<Bond>> historicaldataserviceforposition;
	ServiceListenerforHistoricalData<Position<Bond>>* positionservicelistenerforhistoricaldata 
		= new ServiceListenerforHistoricalData<Position<Bond>>(historicaldataserviceforposition);
	HistoricalDataServiceConnectorforPosition* historicaldataserviceconnectorforposition
		= new HistoricalDataServiceConnectorforPosition("positiondata.txt");
	BondHistoricalDataServiceListener<Position<Bond>>* historicaldataservicelistnerforposition
		= new BondHistoricalDataServiceListener<Position<Bond>>(historicaldataserviceconnectorforposition);
	historicaldataserviceforposition.AddListener(historicaldataservicelistnerforposition);

	//for risk
	BondHistoricalDataService<PV01<Bond>> historicaldataserviceforrisk;
	ServiceListenerforHistoricalData<PV01<Bond>>* riskservicelistenerforhistoricaldata
		= new ServiceListenerforHistoricalData<PV01<Bond>>(historicaldataserviceforrisk);
	HistoricalDataServiceConnectorforRisk* historicaldataserviceconnectorforrisk
		= new HistoricalDataServiceConnectorforRisk("riskdata.txt");
	BondHistoricalDataServiceListener<PV01<Bond>>* historicaldataservicelistnerforrisk
		= new BondHistoricalDataServiceListener<PV01<Bond>>(historicaldataserviceconnectorforrisk);
	historicaldataserviceforrisk.AddListener(historicaldataservicelistnerforrisk);

	//for execution order
	BondHistoricalDataService<ExecutionOrder<Bond>> historicaldataserviceforexecution;
	ServiceListenerforHistoricalData<ExecutionOrder<Bond>>* executionservicelistenerforhistoricaldata
		= new ServiceListenerforHistoricalData<ExecutionOrder<Bond>>(historicaldataserviceforexecution);
	HistoricalDataServiceConnectorforExecution* historicaldataserviceconnectorforexecution
		= new HistoricalDataServiceConnectorforExecution("executiondata.txt");
	BondHistoricalDataServiceListener<ExecutionOrder<Bond>>* historicaldataservicelistnerforexecution
		= new BondHistoricalDataServiceListener<ExecutionOrder<Bond>>(historicaldataserviceconnectorforexecution);
	historicaldataserviceforexecution.AddListener(historicaldataservicelistnerforexecution);

	//for stream
	BondHistoricalDataService<PriceStream<Bond>> historicaldataserviceforstream;
	ServiceListenerforHistoricalData<PriceStream<Bond>>* streamservicelistenerforhistoricaldata
		= new ServiceListenerforHistoricalData<PriceStream<Bond>>(historicaldataserviceforstream);
	HistoricalDataServiceConnectorforStream* historicaldataserviceconnectorforstream
		= new HistoricalDataServiceConnectorforStream("streamdata.txt");
	BondHistoricalDataServiceListener<PriceStream<Bond>>* historicaldataservicelistnerforstream
		= new BondHistoricalDataServiceListener<PriceStream<Bond>>(historicaldataserviceconnectorforstream);
	historicaldataserviceforstream.AddListener(historicaldataservicelistnerforstream);

	//for inquiry
	BondHistoricalDataService<Inquiry<Bond>> historicaldataserviceforinquiry;
	ServiceListenerforHistoricalData<Inquiry<Bond>>* inquiryservicelistenerforhistoricaldata
		= new ServiceListenerforHistoricalData<Inquiry<Bond>>(historicaldataserviceforinquiry);
	HistoricalDataServiceConnectorforInquiry* historicaldataserviceconnectorforinquiry
		= new HistoricalDataServiceConnectorforInquiry("inquirydata.txt");
	BondHistoricalDataServiceListener<Inquiry<Bond>>* historicaldataservicelistnerforinquiry
		= new BondHistoricalDataServiceListener<Inquiry<Bond>>(historicaldataserviceconnectorforinquiry);
	historicaldataserviceforinquiry.AddListener(historicaldataservicelistnerforinquiry);

	//TRADEBOOKING---POSITION--RISK
	BondTradeBookingService bookingservice;
	BondTradeBookingServiceConnector bookingserviceconnector(bookingservice, "trade.txt");

	BondPositionService positionservice;
	BondTradeBookingServiceListener* bookingservicelistener = new BondTradeBookingServiceListener(positionservice);
	bookingservice.AddListener(bookingservicelistener);

	BondRiskService riskservice;
	BondPositionServiceListener* positionservicelistener = new BondPositionServiceListener(riskservice);
	positionservice.AddListener(positionservicelistener);

	positionservice.AddListener(positionservicelistenerforhistoricaldata);
	riskservice.AddListener(riskservicelistenerforhistoricaldata);

	RiskServiceSpecConnector riskspecconnector("BucketRisk.txt");
	RiskServiceSpecListener* riskspeclistener = new RiskServiceSpecListener(riskspecconnector);
	riskservice.AddSpecListener(riskspeclistener);

	bookingserviceconnector.Subscribe();

	
	//MARKETDATA--ALGOEXECUTION--EXECUTION--TRADINGBOOKING--POSIONTION--RISK
	BondMarketDataService marketdataservice;
	BondMarketDataServiceConnector marketdataserviceconnector(marketdataservice, "marketdata.txt");

	BondAlgoExecutionService  algoexecutionservice;
	BondMarketDataServiceListener* marketdataservicelistener = new BondMarketDataServiceListener(algoexecutionservice);
	marketdataservice.AddListener(marketdataservicelistener);

	BondExecutionService executionservice;
	BondAlgoExecutionServiceListener* algoexecutionservicelistener = new BondAlgoExecutionServiceListener(executionservice);
	algoexecutionservice.AddListener(algoexecutionservicelistener);

	BondExecutionServiceListener* executionservicelistener = new BondExecutionServiceListener(bookingservice);
	executionservice.AddListener(executionservicelistener);
	executionservice.AddListener(executionservicelistenerforhistoricaldata);

	marketdataserviceconnector.Subscribe();
	

	
	//PRICING--ALGOSTREAMING--STEAMING
	//PRICING-GUI
	BondPricingService pricingservice;
	BondPricingServiceConnector pricingserviceconnector(pricingservice, "price.txt");

	BondAlgoStreamingService algostreamingservice;
	BondPricingServiceListener* pricingservicelistener = new BondPricingServiceListener(algostreamingservice);
	pricingservice.AddListener(pricingservicelistener);

	BondStreamingService streamingservice;
	BondAlgoStreamingServiceListener* algostreamingservicelistener = new BondAlgoStreamingServiceListener(streamingservice);
	algostreamingservice.AddListener(algostreamingservicelistener);

	streamingservice.AddListener(streamservicelistenerforhistoricaldata);

	
	BondGUIService guiservice;
	BondPricingServiceListenerforGUI* pricingserviceliatenerforgui = new BondPricingServiceListenerforGUI(guiservice);
	pricingservice.AddListener(pricingserviceliatenerforgui);

	BondGUIServiceWriteConnector guiserviceconnector("GUIprice.txt");
	BondGUIServiceListener* guiservicelistener = new BondGUIServiceListener(guiserviceconnector);
	guiservice.AddListener(guiservicelistener);

	pricingserviceconnector.Subscribe();
	
	//INQUIRY--INQUIRY
	BondInquiryService inquiryservice;
	BondIquiryServiceReadfileConnector readfileconnector(inquiryservice, "inquiry.txt");
	BondIquiryServiceChangeStateConnector changestateconnector(inquiryservice);
	BondInquiryServiceListener* inquiryservicelistener = new BondInquiryServiceListener(changestateconnector);
	inquiryservice.AddListener(inquiryservicelistenerforhistoricaldata);

	inquiryservice.AddListener(inquiryservicelistener);

	

	readfileconnector.Subscribe();


	return 0;
}