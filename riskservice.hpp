/**
 * riskservice.hpp
 * Defines the data types and Service for fixed income risk.
 *
 * @author Breman Thuraisingham
 */
#ifndef RISK_SERVICE_HPP
#define RISK_SERVICE_HPP

#include "soa.hpp"
#include"products.hpp"
#include "positionservice.hpp"

/**
 * PV01 risk.
 * Type T is the product type.
 */
template<typename T>
class PV01
{

public:

  // ctor for a PV01 value
  PV01(const T &_product, double _pv01, long _quantity);
  PV01() {}

  // Get the product on this PV01 value
  const T& GetProduct() const;

  // Get the PV01 value
  double GetPV01() const;

  // Get the quantity that this risk value is associated with
  long GetQuantity() const;

  //Update the quantity when the position is updated
  void SetQuantity(long quant);

private:
  T product;
  double pv01;
  long quantity;

};

/**
 * A bucket sector to bucket a group of securities.
 * We can then aggregate bucketed risk to this bucket.
 * Type T is the product type.
 */
template<typename T>
class BucketedSector
{

public:

  // ctor for a bucket sector
  BucketedSector(const vector<T> &_products, string _name);

  // Get the products associated with this bucket
  const vector<T>& GetProducts() const;

  // Get the name of the bucket
  const string& GetName() const;

private:
  vector<T> products;
  string name;

};

Bond y10("9128283F5", CUSIP, "10Y", 2.25, date(2027 / 11 / 15));
Bond y2("9128283H1", CUSIP, "2Y", 1.75, date(2019 / 11 / 30));
Bond y30("912810RZ3", CUSIP, "30Y", 2.75, date(2047 / 11 / 15));
Bond y3("9128283L2", CUSIP, "3Y", 1.875, date(2020 / 12 / 15));
Bond y5("9128283K4", CUSIP, "5Y", 2.00, date(2022 / 11 / 30));
Bond y7("9128283J7", CUSIP, "7Y", 2.125, date(2024 / 11 / 30));

vector<Bond> front{ y2,y3 };
vector<Bond> bel{ y5,y7,y10 };
vector<Bond> longe{ y30 };

BucketedSector<Bond> FrontEnd(front, "FrontEnd");
BucketedSector<Bond> Belly(bel, "Belly");
BucketedSector<Bond> LongEnd(longe, "LongEnd");

/**
 * Risk Service to vend out risk for a particular security and across a risk bucketed sector.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class RiskService : public Service<string,PV01 <T> >
{

public:

  // Add a position that the service will risk
  virtual void AddPosition(Position<T> &position) = 0;

  // Get the bucketed risk for the bucket sector
  virtual const PV01< BucketedSector<T>> GetBucketedRisk(const BucketedSector<T> &sector) = 0;

};

template<typename T>
PV01<T>::PV01(const T &_product, double _pv01, long _quantity) :
  product(_product)
{
  pv01 = _pv01;
  quantity = _quantity;
}

template<typename T>
const T& PV01<T>::GetProduct() const
{
	return product;
}

template<typename T>
double PV01<T>::GetPV01() const
{
	return pv01;
}

template<typename T>
long PV01<T>::GetQuantity() const
{
	return quantity;
}

template<typename T>
void PV01<T>::SetQuantity(long quant)
{
	quantity = quant;
}

template<typename T>
BucketedSector<T>::BucketedSector(const vector<T>& _products, string _name) :
  products(_products)
{
  name = _name;
}

template<typename T>
const vector<T>& BucketedSector<T>::GetProducts() const
{
  return products;
}

template<typename T>
const string& BucketedSector<T>::GetName() const
{
  return name;
}

#endif
