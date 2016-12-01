#include "stdafx.h"
#include "BusinessObject.h"


BusinessColumnBase::BusinessColumnBase()
{
	_hasValue = false;
}

void BusinessColumnBase::Init(BusinessObjectBase * obj, std::string columnName)
{
	_obj = obj;
	_columnName = columnName;
	obj->AddColumn(static_cast<BusinessColumnBase*>(this));
}

std::string BusinessColumnBase::ToString() const
{
	return "";
}
std::string BusinessColumnBase::ToSqlString() const
{
	return "";
}
std::string BusinessColumnBase::SqlCreatePart()
{
	return std::string();
}

BusinessColumnBase::operator std::string() const
{
	return ToString();
}

bool BusinessColumnBase::HasValue()
{
	return _hasValue;
}

std::string BusinessColumnBase::ColumnName()
{
	return _columnName;
}