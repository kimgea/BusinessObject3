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

	sql += "\n";

	for (auto itr = _foreign_keys.begin(); itr != _foreign_keys.end(); itr++)
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

std::string BusinessObjectBase::Insert()
{
	// Check keys
	for (auto itr = _primary_keys.begin(); itr != _primary_keys.end(); itr++)
	{
		if (!(*itr)->HasValues())	// TODO: ignore autoincrement columns... those will not be made
			throw("PK required to have values");
	}
	std::string column_names = "";
	std::string column_values = "";

	for (auto itr = _columns.begin(); itr != _columns.end(); itr++)
	{
		if (!(*itr)->HasValue())
			continue;
		column_names += (*itr)->ColumnName() + ", ";
		column_values += (*itr)->ToSqlString() + ", ";
	}
	if (column_names.size() == 0)
		return "";

	column_names.pop_back();
	column_values.pop_back();

	std::string  sql = "INSERT INTO " + _tableName + " (" + column_names + ")\n";
	sql += "VALUES (" + column_values + ")";
	
	return sql;
}

std::string BusinessObjectBase::Read()
{
	return std::string();
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
