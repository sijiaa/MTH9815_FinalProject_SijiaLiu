/**
* gui.hpp
* Definition of GUIService
*
* @author Sijia Liu
*/
#pragma once

#include"soa.hpp"
#include"pricingservice.hpp"

/*
* GUIService ia a GUI component outputing data on a certain interval
* Keyed on product identifier.
* with a price object
* Type T is the product type.
*/

template<typename T>
class GuiService :public Service<string, Price <T> >
{

};
