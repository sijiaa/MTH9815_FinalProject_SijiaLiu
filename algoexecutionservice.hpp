/**
* algoexecutionservice.hpp
* Definition of AlgoExecution and AlgoExecutionService
*
* @author Sijia Liu
*/
#pragma once

#include <string>
#include <vector>
#include "soa.hpp"
#include "executionservice.hpp"


/*
* AlgoExecution class
* Used as value in AlgoExecutionService
*/

template<typename T>
class AlgoExecution
{
public:
	//constructor
	//only construct when the algo starts and trades a new product
	//initialize with SIDE BID
	AlgoExecution(const T &_product);
	AlgoExecution() {}

	//get product
	const T& GetProduct() const;

	//get execution order
	ExecutionOrder<T> GetExecutionOrder();

	//get next side of order
	PricingSide GetNextSide();

	//algo to generate an order with a given updated orderbook
	//will be called everytime when new marketdata come in from SL of marketdataservice
	//In our algo we aggress the top of the book when the spread is at its tightest 
	//and alternating between bid and offer
	//return if we place an order on this orderbook
	bool algo(OrderBook <Bond> &book);

private:
	T product;
	PricingSide nextside;
	ExecutionOrder<T> order;
	int n;
	
};


/**
* Algo Execution Service to .
* Keyed on product identifier.
* Type T is the product type.
*/
template<typename T>
class AlgoExecutionService :public Service<string, AlgoExecution <T> >
{
public:
	//when a new orderbook come in, generate on order base on the orderbook
	virtual void GenerateOrder(OrderBook <T> &book) = 0;

};


template<typename T>
AlgoExecution<T>::AlgoExecution(const T &_product)
	:product(_product)
{
	nextside = BID;
	n = 0;
}

template<typename T>
const T& AlgoExecution<T>::GetProduct() const
{
	return product;
}

template<typename T>
ExecutionOrder<T> AlgoExecution<T>::GetExecutionOrder()
{
	return order;
}


template<typename T>
PricingSide AlgoExecution<T>::GetNextSide()
{
	return  nextside;
}

template<typename T>
bool AlgoExecution<T>::algo(OrderBook <Bond> &book)
{
	Order bidOrder = book.GetBidStack()[0];
	Order offerOrder = book.GetOfferStack()[0];
	
	if (offerOrder.GetPrice() - bidOrder.GetPrice() == (1.0 / 128))
	{
		//generate order id
		string orderid = "execcutionorder" + to_string(++n);
		if (nextside == BID)
		{
			order = ExecutionOrder<T>(product, BID, orderid,
				MARKET, bidOrder.GetPrice(), bidOrder.GetQuantity(), bidOrder.GetQuantity()*2, "none", false);
		}
		else
		{
			order = ExecutionOrder<T>(product, OFFER, orderid,
				MARKET, offerOrder.GetPrice(), offerOrder.GetQuantity(), offerOrder.GetQuantity()*2, "none", false);
		}

		//update next side. will be the opposite side
		nextside = (nextside == BID) ? OFFER : BID;
		
		return true;
	}

	return false;
}