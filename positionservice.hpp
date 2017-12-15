/**
 * positionservice.hpp
 * Defines the data types and Service for positions.
 *
 * @author Breman Thuraisingham
 */
#ifndef POSITION_SERVICE_HPP
#define POSITION_SERVICE_HPP

#include <string>
#include <map>
#include "soa.hpp"
#include "tradebookingservice.hpp"

using namespace std;

/**
 * Position class in a particular book.
 * Type T is the product type.
 */
template<typename T>
class Position
{

public:

  // ctor for a position
  Position(const T &_product);
  Position() {}

  // Get the product
  const T& GetProduct() const;

  // Get the position quantity
  long GetPosition(const string &book);

  // Get the aggregate position
  long GetAggregatePosition();

  // Set a new book
  void AddBook(const string &book);

  // Set a new position, with new quantity
  void UpdatePosition(const string &book, long quantity, Side side);


private:
  T product;
  map<string,long> positions;

};

/**
 * Position Service to manage positions across multiple books and secruties.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class PositionService : public Service<string,Position <T> >
{

public:

  // Add a trade to the service
  virtual void AddTrade(Trade<T> &trade) = 0;

};

template<typename T>
Position<T>::Position(const T &_product) :
  product(_product)
{
}

template<typename T>
const T& Position<T>::GetProduct() const
{
  return product;
}

template<typename T>
long Position<T>::GetPosition(const string &book)
{
  return positions[book];
}

template<typename T>
long Position<T>::GetAggregatePosition()
{
  // No-op implementation - should be filled out for implementations
	long sum = 0;
	for (auto it = positions.begin(); it != positions.end(); ++it)
	{
		sum += it->second;
	}
    return sum;
}

template<typename T>
void Position<T>::AddBook(const string &book)
{
	positions[book] = 0;
}

template<typename T>
void Position<T>::UpdatePosition(const string &book,long quantity,Side side)
{
	if (side == BUY) 
	{
		positions[book] += quantity;
	}
	else
	{
		positions[book] -= quantity;
	}
	
}

#endif
