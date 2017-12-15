This is a structure of Trading System.

Only need to run the main.cpp
It will first generate the txt we need.
Then it will read the trade.txt, marketdata.txt, price.txt, inquiry.txt sequencially, invoking all the services.
Specifically, they are :
1. trade.txt--Connector--TradeBookingService--ServiceListener--PositionService--ServiceListener--RiskService
2. marketdata.txt--Connector--MarketDataService--AlgoExecutionService--ServiceListener--ExecutionSercice--ServicListener--TradeBookingService--ServiceListener--PositionService--ServiceListener--RiskService
3. price.txt--Connctor--PricingService--ServiceListener--AlgoStreamingService--ServiceListener--StreamingService
4. inquiry.txt--Connector--InquiryService--Connector--InquiryService

And at the same time, for historical data service
1. PositionService--ServiceListener--HistoricalDataService--ServiceListener--Connector--txt
2. RiskService--ServiceListener--HistoricalDataService--ServiceListener--Connector--txt
3. ExecutionSercice--ServiceListener--HistoricalDataService--ServiceListener--Connector--txt
4. StreamingService--ServiceListener--HistoricalDataService--ServiceListener--Connector--txt
5. InquiryService--ServiceListener--HistoricalDataService--ServiceListener--Connector--txt

For GUIService
PricingService--ServiceListener--GuiService--Connector--txt