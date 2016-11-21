#pragma once
#include <string>

class IBusinessColumn
{
public:
	virtual ~IBusinessColumn() {};

	virtual std::string SqlCreatePart() = 0;
};

/*
class IBusinessObject
{
public:
	virtual ~IBusinessObject() {};

	virtual void AddColumn(IBusinessColumn *column) = 0;
};
*/



