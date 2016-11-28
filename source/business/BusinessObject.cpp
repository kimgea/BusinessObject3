#include "stdafx.h"
#include "BusinessObject.h"

BusinessObjectBase::BusinessObjectBase()
{
}

BusinessObjectBase & BusinessObjectBase::operator=(const BusinessObjectBase & rhs)
{
	if (this != &rhs)
	{
		ColumnItr litr = _columns.begin();
		for (ColumnConstItr ritr = rhs._columns.begin(); ritr != rhs._columns.end(); ritr++)
		{
			(*litr) = (*ritr);
		}
	}
	return *this;
}

std::string BusinessObjectBase::Create()
{
	if (_tableName.size() == 0)
		return "";

	std::string sql;

	sql = "CREATE TABLE " + _tableName + "\n(\n";

	for (ColumnItr itr = _columns.begin(); itr != _columns.end(); itr++)
	{
		sql += (*itr)->SqlCreatePart() + ",\n";		// TODO: nead to find out the speed of this
	}

	sql += "\n";

	for (PrimaryKeyItr itr = _primary_keys.begin(); itr != _primary_keys.end(); itr++)
	{
		sql += (*itr)->SqlCreatePart() + ",\n";		// TODO: nead to find out the speed of this
	}

	// TODO: add other requirements and stuff'

	sql.pop_back();
	sql.pop_back();
	sql += "\n)";

	return sql;
}
std::string BusinessObjectBase::Drop()
{
	return "DROP TABLE " + _tableName;
}

void BusinessObjectBase::AddColumn(BusinessColumnBase *column)
{
	_columns.push_back(column);
}
void BusinessObjectBase::AddPrimaryKey(std::unique_ptr<PrimaryKey> &&primary_key)
{
	_primary_keys.push_back(std::move(primary_key));
}
void BusinessObjectBase::AddForeignKey(std::unique_ptr<ForeignKey>&& foreign_key)
{
	_foreign_keys.push_back(std::move(foreign_key));
}
