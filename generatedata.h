/**
* generatedata.hpp
* four fucntion to generate four kinds of txt data for the trading system
*
* @author Sijia Liu
*/
#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include<random>

using namespace std;



void generateTrade(int N)
{
	cout << setprecision(10);
	ofstream outf("trade.txt");
	int j = 0;
	vector<int> price{ 99,100 };
	vector<string> book{ "TRSY1","TRSY2","TRSY3" };
	vector<string> side{ "BUY","SELL" };

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283F5" << ",";
		outf << "CUSIP" << ",";
		outf << "10Y" << ",";
		outf << "2.25" << ",";
		outf << "2027/11/15" << ",";
		outf << "trade" << ++j << ",";
		outf << price[(i % 2)] << ",";
		outf << book[(i % 3)] << ",";
		outf << 1000000 * (i % 5 + 1) << ",";
		outf << side[(i % 2)] ;
		outf << endl;
		outf << flush;

	}

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283H1" << ",";
		outf << "CUSIP" << ",";
		outf << "2Y" << ",";
		outf << "1.75" << ",";
		outf << "2019/11/30" << ",";
		outf << "trade" << ++j << ",";
		outf << price[(i % 2)] << ",";
		outf << book[(i % 3)] << ",";
		outf << 1000000 * (i % 5 + 1) << ",";
		outf << side[(i % 2)];
		outf << endl;
		outf << flush;

	}

	for (int i = 0; i < N; ++i)
	{
		outf << "912810RZ3" << ",";
		outf << "CUSIP" << ",";
		outf << "30Y" << ",";
		outf << "2.75" << ",";
		outf << "2047/11/15" << ",";
		outf << "trade" << ++j << ",";
		outf << price[(i % 2)] << ",";
		outf << book[(i % 3)] << ",";
		outf << 1000000 * (i % 5 + 1) << ",";
		outf << side[(i % 2)] ;
		outf << endl;
		outf << flush;
	}

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283L2" << ",";
		outf << "CUSIP" << ",";
		outf << "3Y" << ",";
		outf << "1.875" << ",";
		outf << "2020/12/15" << ",";
		outf << "trade" << ++j << ",";
		outf << price[(i % 2)] << ",";
		outf << book[(i % 3)] << ",";
		outf << 1000000 * (i % 5 + 1) << ",";
		outf << side[(i % 2)] ;
		outf << endl;
		outf << flush;
	}

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283K4" << ",";
		outf << "CUSIP" << ",";
		outf << "5Y" << ",";
		outf << "2.00" << ",";
		outf << "2022/11/30" << ",";
		outf << "trade" << ++j << ",";
		outf << price[(i % 2)] << ",";
		outf << book[(i % 3)] << ",";
		outf << 1000000 * (i % 5 + 1) << ",";
		outf << side[(i % 2)];
		outf << endl;
		outf << flush;
	}

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283J7" << ",";
		outf << "CUSIP" << ",";
		outf << "7Y" << ",";
		outf << "2.125" << ",";
		outf << "2024/11/30" << ",";
		outf << "trade" << ++j << ",";
		outf << price[(i % 2)] << ",";
		outf << book[(i % 3)] << ",";
		outf << 1000000 * (i % 5 + 1) << ",";
		outf << side[(i % 2)];
		if (i != N - 1)
			outf << endl;
		outf << flush;
	}

	outf.close();
}

void generateInquiry(int N)
{
	ofstream outf("inquiry.txt");
	int j = 0;
	vector<int> price{ 99,101 };
	vector<string> book{ "TRSY1","TRSY2","TRSY3" };
	vector<string> side{ "BUY","SELL" };

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283F5" << ",";
		outf << "CUSIP" << ",";
		outf << "10Y" << ",";
		outf << "2.25" << ",";
		outf << "2027/11/15" << ",";
		outf << "inquiry" << ++j << ",";
		outf << side[(i % 2)] << ",";
		outf << 1000000 * (i % 5 + 1) << ",";
		outf << price[(i % 2)] << ",";
		outf << "RECEIVED" ;
		outf << endl;
		outf << flush;

	}

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283H1" << ",";
		outf << "CUSIP" << ",";
		outf << "2Y" << ",";
		outf << "1.75" << ",";
		outf << "2019/11/30" << ",";
		outf << "inquiry" << ++j << ",";
		outf << side[(i % 2)] << ",";
		outf << 1000000 * (i % 5 + 1) << ",";
		outf << price[(i % 2)] << ",";
		outf << "RECEIVED" ;
		outf << endl;
		outf << flush;

	}

	for (int i = 0; i < N; ++i)
	{
		outf << "912810RZ3" << ",";
		outf << "CUSIP" << ",";
		outf << "30Y" << ",";
		outf << "2.75" << ",";
		outf << "2047/11/15" << ",";
		outf << "inquiry" << ++j << ",";
		outf << side[(i % 2)] << ",";
		outf << 1000000 * (i % 5 + 1) << ",";
		outf << price[(i % 2)] << ",";
		outf << "RECEIVED";
		outf << endl;
		outf << flush;
	}

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283L2" << ",";
		outf << "CUSIP" << ",";
		outf << "3Y" << ",";
		outf << "1.875" << ",";
		outf << "2020/12/15" << ",";
		outf << "inquiry" << ++j << ",";
		outf << side[(i % 2)] << ",";
		outf << 1000000 * (i % 5 + 1) << ",";
		outf << price[(i % 2)] << ",";
		outf << "RECEIVED";
		outf << endl;
		outf << flush;
	}

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283K4" << ",";
		outf << "CUSIP" << ",";
		outf << "5Y" << ",";
		outf << "2.00" << ",";
		outf << "2022/11/30" << ",";
		outf << "inquiry" << ++j << ",";
		outf << side[(i % 2)] << ",";
		outf << 1000000 * (i % 5 + 1) << ",";
		outf << price[(i % 2)] << ",";
		outf << "RECEIVED";
		outf << endl;
		outf << flush;
	}

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283J7" << ",";
		outf << "CUSIP" << ",";
		outf << "7Y" << ",";
		outf << "2.125" << ",";
		outf << "2024/11/30" << ",";
		outf << "inquiry" << ++j << ",";
		outf << side[(i % 2)] << ",";
		outf << 1000000 * (i % 5 + 1) << ",";
		outf << price[(i % 2)] << ",";
		outf << "RECEIVED";
		if (i != N - 1)
			outf << endl;
		outf << flush;
	}

	outf.close();
}


void generateMarketdata(int N)
{
	ofstream outf("marketdata.txt");
	outf.precision(10);
	
	for (int i = 0; i < N; ++i)
	{
		outf << "9128283F5" << ",";
		outf << "CUSIP" << ",";
		outf << "10Y" << ",";
		outf << "2.25" << ",";
		outf << "2027/11/15" << ",";
		double mid;
		double bid1, bid2, bid3, bid4, bid5;
		double offer1, offer2, offer3, offer4, offer5;
		const double minincrement = 1.0 / 256.0;

		unsigned int  temp = rand() % 511 + 1;
		mid = minincrement*temp + 99;
		bid1 = mid - (i % 4 + 1)*minincrement;
		bid2 = bid1 - minincrement;
		bid3 = bid2 - minincrement;
		bid4 = bid3 - minincrement;
		bid5 = bid4 - minincrement;
		offer1 = mid + minincrement;
		offer2 = offer1 + (i % 4 + 1)*minincrement;
		offer3 = offer2 + minincrement;
		offer4 = offer3 + minincrement;
		offer5 = offer4 + minincrement;
		outf << bid1 << ",";
		outf << bid2 << ",";
		outf << bid3 << ",";
		outf << bid4 << ",";
		outf << bid5 << ",";
		outf << offer1 << ",";
		outf << offer2 << ",";
		outf << offer3 << ",";
		outf << offer4 << ",";
		outf << offer5;
		outf << endl;
		outf << flush;

	}

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283H1" << ",";
		outf << "CUSIP" << ",";
		outf << "2Y" << ",";
		outf << "1.75" << ",";
		outf << "2019/11/30" << ",";
		double mid;
		double bid1, bid2, bid3, bid4, bid5;
		double offer1, offer2, offer3, offer4, offer5;
		const double minincrement = 1.0 / 256.0;

		unsigned int  temp = rand() % 511 + 1;
		mid = minincrement*temp + 99;
		bid1 = mid - (i % 4 + 1)*minincrement;
		bid2 = bid1 - minincrement;
		bid3 = bid2 - minincrement;
		bid4 = bid3 - minincrement;
		bid5 = bid4 - minincrement;
		offer1 = mid + minincrement;
		offer2 = offer1 + (i % 4 + 1)*minincrement;
		offer3 = offer2 + minincrement;
		offer4 = offer3 + minincrement;
		offer5 = offer4 + minincrement;
		outf << bid1 << ",";
		outf << bid2 << ",";
		outf << bid3 << ",";
		outf << bid4 << ",";
		outf << bid5 << ",";
		outf << offer1 << ",";
		outf << offer2 << ",";
		outf << offer3 << ",";
		outf << offer4 << ",";
		outf << offer5;
		outf << endl;
		outf << flush;

	}

	for (int i = 0; i < N; ++i)
	{
		outf << "912810RZ3" << ",";
		outf << "CUSIP" << ",";
		outf << "30Y" << ",";
		outf << "2.75" << ",";
		outf << "2047/11/15" << ",";
		double mid;
		double bid1, bid2, bid3, bid4, bid5;
		double offer1, offer2, offer3, offer4, offer5;
		const double minincrement = 1.0 / 256.0;

		unsigned int  temp = rand() % 511 + 1;
		mid = minincrement*temp + 99;
		bid1 = mid - (i % 4 + 1)*minincrement;
		bid2 = bid1 - minincrement;
		bid3 = bid2 - minincrement;
		bid4 = bid3 - minincrement;
		bid5 = bid4 - minincrement;
		offer1 = mid + (i % 4 + 1)*minincrement;
		offer2 = offer1 + minincrement;
		offer3 = offer2 + minincrement;
		offer4 = offer3 + minincrement;
		offer5 = offer4 + minincrement;
		outf << bid1 << ",";
		outf << bid2 << ",";
		outf << bid3 << ",";
		outf << bid4 << ",";
		outf << bid5 << ",";
		outf << offer1 << ",";
		outf << offer2 << ",";
		outf << offer3 << ",";
		outf << offer4 << ",";
		outf << offer5;
		outf << endl;
		outf << flush;
	}

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283L2" << ",";
		outf << "CUSIP" << ",";
		outf << "3Y" << ",";
		outf << "1.875" << ",";
		outf << "2020/12/15" << ",";
		double mid;
		double bid1, bid2, bid3, bid4, bid5;
		double offer1, offer2, offer3, offer4, offer5;
		const double minincrement = 1.0 / 256.0;

		unsigned int  temp = rand() % 511 + 1;
		mid = minincrement*temp + 99;
		bid1 = mid - (i % 4 + 1)*minincrement;
		bid2 = bid1 - minincrement;
		bid3 = bid2 - minincrement;
		bid4 = bid3 - minincrement;
		bid5 = bid4 - minincrement;
		offer1 = mid + (i % 4 + 1)*minincrement;
		offer2 = offer1 + minincrement;
		offer3 = offer2 + minincrement;
		offer4 = offer3 + minincrement;
		offer5 = offer4 + minincrement;
		outf << bid1 << ",";
		outf << bid2 << ",";
		outf << bid3 << ",";
		outf << bid4 << ",";
		outf << bid5 << ",";
		outf << offer1 << ",";
		outf << offer2 << ",";
		outf << offer3 << ",";
		outf << offer4 << ",";
		outf << offer5;
		outf << endl;
		outf << flush;
	}

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283K4" << ",";
		outf << "CUSIP" << ",";
		outf << "5Y" << ",";
		outf << "2.00" << ",";
		outf << "2022/11/30" << ",";
		double mid;
		double bid1, bid2, bid3, bid4, bid5;
		double offer1, offer2, offer3, offer4, offer5;
		const double minincrement = 1.0 / 256.0;

		unsigned int  temp = rand() % 511 + 1;
		mid = minincrement*temp + 99;
		bid1 = mid - (i % 4 + 1)*minincrement;
		bid2 = bid1 - minincrement;
		bid3 = bid2 - minincrement;
		bid4 = bid3 - minincrement;
		bid5 = bid4 - minincrement;
		offer1 = mid + (i % 4 + 1)*minincrement;
		offer2 = offer1 + minincrement;
		offer3 = offer2 + minincrement;
		offer4 = offer3 + minincrement;
		offer5 = offer4 + minincrement;
		outf << bid1 << ",";
		outf << bid2 << ",";
		outf << bid3 << ",";
		outf << bid4 << ",";
		outf << bid5 << ",";
		outf << offer1 << ",";
		outf << offer2 << ",";
		outf << offer3 << ",";
		outf << offer4 << ",";
		outf << offer5;
		outf << endl;
		outf << flush;
	}

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283J7" << ",";
		outf << "CUSIP" << ",";
		outf << "7Y" << ",";
		outf << "2.125" << ",";
		outf << "2024/11/30" << ",";
		double mid;
		double bid1, bid2, bid3, bid4, bid5;
		double offer1, offer2, offer3, offer4, offer5;
		const double minincrement = 1.0 / 256.0;

		unsigned int  temp = rand() % 511 + 1;
		mid = minincrement*temp + 99;
		bid1 = mid - (i % 4 + 1)*minincrement;
		bid2 = bid1 - minincrement;
		bid3 = bid2 - minincrement;
		bid4 = bid3 - minincrement;
		bid5 = bid4 - minincrement;
		offer1 = mid + minincrement;
		offer2 = offer1 + (i % 4 + 1)*minincrement;
		offer3 = offer2 + minincrement;
		offer4 = offer3 + minincrement;
		offer5 = offer4 + minincrement;
		outf << bid1 << ",";
		outf << bid2 << ",";
		outf << bid3 << ",";
		outf << bid4 << ",";
		outf << bid5 << ",";
		outf << offer1 << ",";
		outf << offer2 << ",";
		outf << offer3 << ",";
		outf << offer4 << ",";
		outf << offer5;
		if (i != N - 1)
			outf << endl;
		outf << flush;
	}

	outf.close();
}


void generatePrice(int N)
{
	ofstream outf("price.txt");
	outf.precision(10);
	vector<double> spread{ 1.0 / 128,1.0 / 64 };

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283F5" << ",";
		outf << "CUSIP" << ",";
		outf << "10Y" << ",";
		outf << "2.25" << ",";
		outf << "2027/11/15" << ",";
		double mid;
		const double minincrement = 1.0 / 256.0;
		unsigned int  temp = rand() % 511 + 1;
		mid = minincrement*temp + 99;
		outf << mid << ",";
		outf << spread[(i % 2)];		
		outf << endl;
		outf << flush;

	}

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283H1" << ",";
		outf << "CUSIP" << ",";
		outf << "2Y" << ",";
		outf << "1.75" << ",";
		outf << "2019/11/30" << ",";
		double mid;
		const double minincrement = 1.0 / 256.0;
		unsigned int  temp = rand() % 511 + 1;
		mid = minincrement*temp + 99;
		outf << mid << ",";
		outf << spread[(i % 2)];
		outf << endl;
		outf << flush;

	}

	for (int i = 0; i < N; ++i)
	{
		outf << "912810RZ3" << ",";
		outf << "CUSIP" << ",";
		outf << "30Y" << ",";
		outf << "2.75" << ",";
		outf << "2047/11/15" << ",";
		double mid;
		const double minincrement = 1.0 / 256.0;
		unsigned int  temp = rand() % 511 + 1;
		mid = minincrement*temp + 99;
		outf << mid << ",";
		outf << spread[(i % 2)];
		outf << endl;
		outf << flush;
	}

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283L2" << ",";
		outf << "CUSIP" << ",";
		outf << "3Y" << ",";
		outf << "1.875" << ",";
		outf << "2020/12/15" << ",";
		double mid;
		const double minincrement = 1.0 / 256.0;
		unsigned int  temp = rand() % 511 + 1;
		mid = minincrement*temp + 99;
		outf << mid << ",";
		outf << spread[(i % 2)];
		outf << endl;
		outf << flush;
	}

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283K4" << ",";
		outf << "CUSIP" << ",";
		outf << "5Y" << ",";
		outf << "2.00" << ",";
		outf << "2022/11/30" << ",";
		double mid;
		const double minincrement = 1.0 / 256.0;
		unsigned int  temp = rand() % 511 + 1;
		mid = minincrement*temp + 99;
		outf << mid << ",";
		outf << spread[(i % 2)];
		outf << endl;
		outf << flush;
	}

	for (int i = 0; i < N; ++i)
	{
		outf << "9128283J7" << ",";
		outf << "CUSIP" << ",";
		outf << "7Y" << ",";
		outf << "2.125" << ",";
		outf << "2024/11/30" << ",";
		double mid;
		const double minincrement = 1.0 / 256.0;
		unsigned int  temp = rand() % 511 + 1;
		mid = minincrement*temp + 99;
		outf << mid << ",";
		outf << spread[(i % 2)];
		if (i != N - 1)
			outf << endl;
		outf << flush;
	}

	outf.close();
}