#pragma once
#include <string>
#include <memory>
//#include "BusinessInterfaces.h"
#include "BusinessObject.h"
//#include "BusinessObject.h"

/*
	TODO:		
			- Must be able to se if value is set or not. IsEmpty()...
			- 
*/



template<class VALUE>
class BusinessColumnBase : public IBusinessColumn
{
protected:
	BusinessObjectBase *_obj;

	std::string _columnName;

	bool _notNull;
	VALUE _default;

	VALUE _value;

	bool _hasValue;


public:
	BusinessColumnBase()
	{
		_hasValue = false;
	}

	void Init(BusinessObjectBase *obj, std::string columnName)
	{
		_obj = obj;
		_columnName = columnName;
		obj->AddColumn(static_cast<IBusinessColumn*>(this));
	}
	void Init(BusinessObjectBase *obj, std::string columnName, bool notNull, VALUE defaultValue)
	{
		_notNull = notNull;
		_default = defaultValue;
		Init(obj, columnName);
	}

	/*BusinessColumnBase<VALUE>& operator=(const BusinessColumnBase<VALUE> &rhs)
	{
		if (this != &rhs)
		{
			_hasValue = rhs._hasValue;
			_notNull = rhs._notNull;
			_default = rhs._default;
			_value = rhs._value;
			_obj = rhs._obj;
			_columnName = rhs._columnName;
		}

		return *this;
	}*/
	BusinessColumnBase<VALUE>& operator=(const VALUE &value)
	{
		_hasValue = true;
		_value = value;
		return *this;
	}

	friend VALUE operator+(
		const BusinessColumnBase<VALUE>& lhs,
		const BusinessColumnBase<VALUE>& rhs)
	{
		return lhs._value + rhs._value;
	}
	friend VALUE operator+(
		const BusinessColumnBase<VALUE>& lhs,
		const VALUE& rhs)
	{
		return lhs._value + rhs;
	}
	friend VALUE operator+(
		const VALUE& lhs,
		const BusinessColumnBase<VALUE>& rhs)
	{
		return lhs + rhs._value;
	}

	virtual std::string ToString() const 
	{ 
		return ""; 
	}

	operator std::string() const 
	{ 
		return ToString(); 
	}

	bool HasValue()
	{
		return _hasValue;
	}


};