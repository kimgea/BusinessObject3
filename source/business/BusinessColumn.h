#pragma once
#include <string>
#include <memory>

#include "BusinessObject.h"
#include "BusinessConstraints.h"


class ForeignKey;
class PrimaryKey;
class PrimaryKeyBuilder;
class ForeignKeyBuilder;
class BusinessColumnBase;


class BusinessColumnBase
{
	friend class BusinessObjectBase;
	friend class ForeignKeyBuilder;
	friend class ForeignKey;

protected:
	BusinessObjectBase *_obj;
	std::string _columnName;
	bool _notNull;
	bool _hasValue;

	ForeignKey * _foreignKey;

	void Init(BusinessObjectBase *obj, std::string columnName);

	virtual std::string SqlCreatePart();

public:
	BusinessColumnBase();

	virtual std::string ToString() const;
	virtual std::string ToSqlString() const;

	// Need to input values from fk columns from this table into the related columns in the refference table. Probasbly never going to do it.
	template<class TABLE, class COLUMN>
	TABLE * FK()
	{
		if (_foreignKey == nullptr)
			return nullptr;
		return _foreignKey->RelatedTable<TABLE, COLUMN>();
	}

	std::string ColumnName();

	operator std::string() const;

	bool HasValue();

};



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