#pragma once
#include <string>
#include <memory>

#include "BusinessObject.h"




template<class VALUE>
class BusinessColumnTypeBase : public BusinessColumnBase
{
	friend class ForeignKey;
protected:

	VALUE _default;
	VALUE _value;
	//std::vector<VALUE> _values; // 

	void Init(BusinessObjectBase *obj, std::string columnName, bool notNull, VALUE defaultValue)
	{
		_notNull = notNull;
		_default = defaultValue;
		BusinessColumnBase::Init(obj, columnName);
	}

public:
	BusinessColumnTypeBase() : BusinessColumnBase()
	{
	}

	
	
	BusinessColumnTypeBase<VALUE>& operator=(const BusinessColumnTypeBase<VALUE> &rhs)
	{
		if (this != &rhs)
		{			
			_value = rhs._value;
			_hasValue = rhs._hasValue;
		}

		return *this;
	}
	
	BusinessColumnTypeBase<VALUE>& operator=(const VALUE &value)
	{
		_hasValue = true;
		_value = value;
		return *this;
	}

	friend VALUE operator+(
		const BusinessColumnTypeBase<VALUE>& lhs,
		const BusinessColumnTypeBase<VALUE>& rhs)
	{
		return lhs._value + rhs._value;
	}
	friend VALUE operator+(
		const BusinessColumnTypeBase<VALUE>& lhs,
		const VALUE& rhs)
	{
		return lhs._value + rhs;
	}
	friend VALUE operator+(
		const VALUE& lhs,
		const BusinessColumnTypeBase<VALUE>& rhs)
	{
		return lhs + rhs._value;
	}
};