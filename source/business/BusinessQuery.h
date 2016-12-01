#pragma once
#include "BusinessObject.h"
#include "BusinessColumn.h"

/*

		WARNING    Here there be POINTER MONSTERS.

		Dis not bother making safe pointers just for this excperiment. Juswt mashed it together without thinking to much
		Want to start coding something else, just need to try some thing here first.

*/

class Q;



class Query
{
protected:

	BusinessObjectBase & _obj;
	std::string _query;

public:
	Query(BusinessObjectBase & obj);
	
	std::string All();
	std::string First();

	Query& Filter(Q filter);

	//unsigned int Count();


};

Query QueryFunc(BusinessObjectBase & obj);

class Q
{
public:
	std::vector<Q*> *_and;
	std::vector<Q*> *_or;
	std::string _value;
	BusinessColumnBase * _column;
	Q();
	Q(BusinessColumnBase * column);
	Q(Q &q);

	friend Q operator &&(Q & lhs, Q  &rhs);
	friend Q operator==(BusinessColumnBase& column, const std::string & value);
	//Q* operator==(const std::string & value);
	//Q operator,(Q &rhs);

};