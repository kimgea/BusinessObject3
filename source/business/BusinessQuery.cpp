#include "stdafx.h"
#include "BusinessQuery.h"

Q::Q()
{
}
Query::Query(BusinessObjectBase & obj) : _obj(obj)
{
	_query = "SELECT * FROM " + obj.TableName();
}



std::string Query::All()
{
	return _query;
}

std::string Query::First()
{
	return _query + "\n LIMIT 1";
}

Query & Query::Filter(Q filter)
{
	_query += "\n WHERE ";
	for (auto itr = filter._and->begin(); itr != filter._and->end(); itr++)
	{
		_query += (*itr)->_column->ColumnName() + " = '" + (*itr)->_value + "'";
		if (itr != --filter._and->end())
			_query += " AND ";
	}
	//Q * and
	return *this;
}



/////////////////////////////////////////////////////////

Query QueryFunc(BusinessObjectBase & obj)
{
	return Query(obj);
}

////////////////////////////////////////////////////////

Q::Q(BusinessColumnBase * column)
{
	_column = column;
}
Q::Q(Q & q)
{
	*this = q;
}

Q operator&&(Q & lhs, Q  &rhs)
{
	if (lhs._and == nullptr)
		lhs._and = new std::vector<Q*>;
	if (rhs._and == nullptr)
		rhs._and = lhs._and;
	if (lhs._or == nullptr)
		lhs._or = new std::vector<Q*>;
	if (rhs._or == nullptr)
		rhs._or = lhs._or;

	if (std::find(rhs._and->begin(), rhs._and->end(), &rhs) == rhs._and->end())
		lhs._and->push_back(&rhs);
	if (std::find(rhs._and->begin(), rhs._and->end(), &lhs) == rhs._and->end())
		lhs._and->push_back(&lhs);
	return lhs;
}

Q operator==(BusinessColumnBase & column, const std::string & value)
{
	Q q(&column);
	q._value = value;
	return q;
}

/*Q * Q::operator==(const std::string & value)
{
	this->_value = value;
	return this;
}*/
/*Q Q::operator,(Q & rhs)
{
	// TODO: insert return statement here
	_comma = &rhs;
	return *this;
}*/