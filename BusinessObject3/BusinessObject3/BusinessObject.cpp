#include "stdafx.h"
#include "BusinessObject.h"



std::string BusinessObjectBase::SqlCreate()
{
	if (_tableName.size() == 0)
		return "";

	std::string sql;

	sql = "CREATE TABLE " + _tableName + "\n(\n";

	for (ColumnItr itr = _columns.begin(); itr != _columns.end(); itr++)
	{
		sql += (*itr)->SqlCreatePart() + ",\n";
	}

	// TODO: add other requirements and stuff'

	sql += ")";

	return sql;
}
std::string BusinessObjectBase::SqlDrop()
{
	return "DROP TABLE " + _tableName;
}

void BusinessObjectBase::AddColumn(IBusinessColumn *column)
{
	_columns.push_back(column);
}