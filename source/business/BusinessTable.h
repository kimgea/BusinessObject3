#pragma once
#include "BusinessObject.h"




/************************************************************************
*
*
*
*
*
*
*
************************************************************************/

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