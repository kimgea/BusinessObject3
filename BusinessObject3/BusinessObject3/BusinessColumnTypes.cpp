#include "stdafx.h"
#include "BusinessColumnTypes.h"




/**************************************************************
*
*		Base Columns types - usable
*
**************************************************************/

void CharColumn::Init(BusinessObjectBase * obj, std::string columnName, unsigned int MaxSize)
{
	BusinessColumnBase<std::string>::Init(obj, columnName);
	_maxSize = MaxSize;
}
void CharColumn::Init(BusinessObjectBase * obj, std::string columnName, unsigned int MaxSize, bool notNull, std::string defaultValue)
{
	BusinessColumnBase<std::string>::Init(obj, columnName, notNull, defaultValue);
	_maxSize = MaxSize;
}

CharColumn & CharColumn::operator=(const std::string & value)
{
	BusinessColumnBase<std::string>::operator=(value);
	return *this;
}

unsigned int CharColumn::GetMaxSize()
{
	return _maxSize;
}

std::string CharColumn::SqlCreatePart()
{
	std::string sql = _columnName + " VARCHAR(" + std::to_string(_maxSize) + ")";

	if (_notNull)
	{
		sql += "NOT NULL DEFAULT '" + _default + "'";
	}

	return sql;
}

std::string CharColumn::ToString() const
{
	if (_value.size() > 0)
		return _value;
	else if (_default.size() > 0)
		return _default;
	return "";
}


/**************************************************************
*
*
*
**************************************************************/

PassswordColumn & PassswordColumn::operator=(const std::string & value)
{
	CharColumn::operator=(value);
	return *this;
}























/**************************************************************
*
*		REST
*
**************************************************************/

/*

template<class TABLE>
IntegerColumn<TABLE>::IntegerColumn(TABLE & obj, std::string columnName) :
	BusinessColumnBase(obj, columnName)
{
}

template<class TABLE>
DoubleColumn<TABLE>::DoubleColumn(TABLE & obj, std::string columnName) :
	BusinessColumnBase(obj, columnName)
{
}




template<class TABLE>
DateTimeColumn<TABLE>::DateTimeColumn(TABLE & obj, std::string columnName) :
	BusinessColumnBase(obj, columnName)
{
}


template<class TABLE>
PasswordColumn<TABLE>::PasswordColumn(TABLE & obj, std::string columnName) :
	BusinessColumnBase(obj, columnName)
{
}
*/