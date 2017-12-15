/**
* algostreamervice.hpp
* Definition of AlgoStream and AlgoStreamService
*
* @author Sijia Liu
*/

#pragma once

#include <string>
#include <vector>
#include "soa.hpp"
#include"pricingservice.hpp"
#include"streamingservice.hpp"

/*
* AlgoStream class
* Used as value in AlgoStreamService
*/

template<typename T>
class AlgoStream
{
public://constructor
	//only construct when the algo starts and trades a new product
	//initialize with SIDE BID
	AlgoStream(const T &_product);
	AlgoStream() {}

	//get product
	const T& GetProduct() const;

	//get execution order
	PriceStream<T> GetPriceStream();

	//algo to generate price stream when a Price object update
	void algo(Price<T> &price);


private:
	T product;
	PriceStream<T> pricestream;
	int n;
};


template<typename T>
class AlgoStreamingService :Service<string, AlgoStream <T>>
{
public:
	//generate stream according to Price object
	virtual void GenerateStream(Price<T> &price) = 0;
};




template<typename T>
AlgoStream<T>::AlgoStream(const T &_product)
{
	product = _product;
	n = 0;
}

template<typename T>
const T& AlgoStream<T>::GetProduct() const
{
	return product;
}

template<typename T>
PriceStream<T> AlgoStream<T>::GetPriceStream()
{
	return pricestream;
}

template<typename T>
void AlgoStream<T>::algo(Price<T> &price) 
{
	PriceStreamOrder bid(price.GetMid() - price.GetBidOfferSpread() / 2, 1000000 * (++n % 2 + 1), 2000000 * (n % 2 + 1), BID);
	PriceStreamOrder offer(price.GetMid() + price.GetBidOfferSpread() / 2, 1000000 * (n % 2 + 1), 2000000 * (n % 2 + 1), OFFER);

	pricestream = PriceStream<T>(price.GetProduct(), bid, offer);

}