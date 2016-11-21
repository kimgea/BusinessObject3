#pragma once
#include <vector>
#include <functional>

#include "BusinessInterfaces.h"

class BusinessObjectBase// : public IBusinessObject
{
private:

protected:
	typedef std::vector<IBusinessColumn*> Columns;
	typedef Columns::iterator ColumnItr;
	Columns _columns;


public:
	std::string _tableName;


	BusinessObjectBase() {}
	virtual ~BusinessObjectBase() {};

	void AddColumn(IBusinessColumn *column);

	std::string SqlCreate();
	std::string SqlDrop();
	


};




class AbstractBusinessObject : public virtual BusinessObjectBase
{
public:
	AbstractBusinessObject() {}
	virtual ~AbstractBusinessObject() {};
};

class BusinessObject : virtual BusinessObjectBase
{
public:
	BusinessObject() {}
	virtual ~BusinessObject() {};
};
