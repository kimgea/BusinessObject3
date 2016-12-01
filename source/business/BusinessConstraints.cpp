#include "stdafx.h"
#include "BusinessObject.h"



/************************************************************************
*
*
*
*		KEYS  (Primary and Foreign)
*
*
*
************************************************************************/


/************************************************************************
*			PrimaryKey
************************************************************************/

std::string PrimaryKey::SqlCreatePart()
{
	bool has_name = (_key_name.size() > 0);
	bool is_one = (_columns.size() == 1);

	if (!has_name && is_one)
		return "PRIMARY KEY (" + _columns.front()->ColumnName() + ")";

	else if (has_name && is_one)
		return "CONSTRAINT " + _key_name + " PRIMARY KEY (" + _columns.front()->ColumnName() + ")";

	std::string primary_columns = _columns.front()->ColumnName() + ",";
	for (ColumnItr itr = ++_columns.begin(); itr != _columns.end(); itr++)
	{
		primary_columns += (*itr)->ColumnName() + ",";
	}
	primary_columns.pop_back();
	return "CONSTRAINT " + _key_name + " PRIMARY KEY (" + primary_columns + ")";
}

bool PrimaryKey::HasValues()
{
	for (ColumnItr itr = ++_columns.begin(); itr != _columns.end(); itr++)
	{
		if (!(*itr)->HasValue())
			return false;
	}
	return true;
}



/************************************************************************
*			ForeignKey
************************************************************************/

std::string ForeignKey::SqlCreatePart()
{
	bool has_name = (_key_name.size() > 0);
	bool is_one = (_column_relations.size() == 1);

	if (!has_name && is_one)
		return "FOREIGN KEY (" + _column_relations.front().first->ColumnName() + ") REFERENCES " + _column_relations.front().second->_obj->_tableName + "(" + _column_relations.front().second->ColumnName() + ")";

	else if (has_name && is_one)
		return "CONSTRAINT " + _key_name + " FOREIGN KEY (" + _column_relations.front().first->ColumnName() + ") REFERENCES " + _column_relations.front().second->_obj->_tableName + "(" + _column_relations.front().second->ColumnName() + ")";
	return "";
	/*std::string primary_columns = _columns.front()->ColumnName() + ",";
	for (ColumnItr itr = ++_columns.begin(); itr != _columns.end(); itr++)
	{
		primary_columns += (*itr)->ColumnName() + ",";
	}
	primary_columns.pop_back();
	return "CONSTRAINT " + _key_name + " PRIMARY KEY (" + primary_columns + ")";*/
}




/************************************************************************
*
*
*
*			KEY BUILDERS
*
*
*
************************************************************************/



/************************************************************************
*			PrimaryKeyBuilder - PrimaryKeyConstraint
************************************************************************/

void PrimaryKeyConstraint(BusinessObjectBase * obj, BusinessColumnBase &column)
{
	PrimaryKeyBuilder builder;
	builder.AddColumn(&column);
	builder.Build(obj);
}

void PrimaryKeyConstraint(BusinessObjectBase * obj, BusinessColumnBase &column, std::string name)
{
	PrimaryKeyBuilder builder;
	builder.AddColumn(&column);
	builder.Build(obj, name);
}


void PrimaryKeyConstraint(BusinessObjectBase * obj,
	BusinessColumnBase &column1, BusinessColumnBase &column2)
{
	PrimaryKeyBuilder builder;
	builder.AddColumn(&column1);
	builder.AddColumn(&column2);
	builder.Build(obj);
}

void PrimaryKeyConstraint(BusinessObjectBase * obj,
	BusinessColumnBase &column1, BusinessColumnBase &column2, 
	std::string name)
{
	PrimaryKeyBuilder builder;
	builder.AddColumn(&column1);
	builder.AddColumn(&column2);
	builder.Build(obj, name);
}

/*******************************************************************/

PrimaryKeyBuilder::PrimaryKeyBuilder()
{
}

void PrimaryKeyBuilder::AddColumn(BusinessColumnBase * column)
{
	_columns.push_back(column);
}

void PrimaryKeyBuilder::Build(BusinessObjectBase *obj, std::string name)
{
	std::unique_ptr<PrimaryKey> pk;
	pk = std::make_unique<PrimaryKey>();
	pk->_key_name = name;
	pk->_obj = obj;
	pk->_columns = _columns;
	obj->AddPrimaryKey(std::move(pk));	// Must be friend
	_columns.clear();
}
void PrimaryKeyBuilder::Build(BusinessObjectBase *obj)
{

	PrimaryKeyBuilder::Build(obj, "");
}


/************************************************************************
*			ForeignKeyBuilder - ForeignKeyConstraint
************************************************************************/

void ForeignKeyConstraint(BusinessObjectBase * obj, BusinessColumnBase &columnKey, BusinessColumnBase &columnReference)
{
	ForeignKeyBuilder builder;
	builder.AddRelation(&columnKey, &columnReference);
	builder.Build(obj);
}

void ForeignKeyConstraint(BusinessObjectBase * obj, BusinessColumnBase &columnKey, BusinessColumnBase &columnReference, std::string name)
{
	ForeignKeyBuilder builder;
	builder.AddRelation(&columnKey, &columnReference);
	builder.Build(obj, name);
}

void ForeignKeyConstraint(BusinessObjectBase * obj,
	BusinessColumnBase &columnKey1, BusinessColumnBase &columnReference1,
	BusinessColumnBase &columnKey2, BusinessColumnBase &columnReference2)
{
	ForeignKeyBuilder builder;
	builder.AddRelation(&columnKey1, &columnReference1);
	builder.AddRelation(&columnKey2, &columnReference2);
	builder.Build(obj);
}

void ForeignKeyConstraint(BusinessObjectBase * obj,
	BusinessColumnBase &columnKey1, BusinessColumnBase &columnReference1,
	BusinessColumnBase &columnKey2, BusinessColumnBase &columnReference2,
	std::string name)
{
	ForeignKeyBuilder builder;
	builder.AddRelation(&columnKey1, &columnReference1);
	builder.AddRelation(&columnKey2, &columnReference2);
	builder.Build(obj, name);
}

/*******************************************************************/

ForeignKeyBuilder::ForeignKeyBuilder()
{
}

void ForeignKeyBuilder::AddRelation(BusinessColumnBase * columnKey, BusinessColumnBase * columnReference)
{
	_column_relations.push_back(std::make_pair(columnKey, columnReference));
}

void ForeignKeyBuilder::Build(BusinessObjectBase *obj, std::string name)
{
	std::unique_ptr<ForeignKey> pk;
	pk = std::make_unique<ForeignKey>();
	pk->_key_name = name;
	pk->_obj = obj;
	pk->_column_relations = _column_relations;
	for (auto itr = pk->_column_relations.begin(); itr != pk->_column_relations.end(); itr++)
		itr->first->_foreignKey = pk.get();
	obj->AddForeignKey(std::move(pk));	// Must be friend
	_column_relations.clear();
}
void ForeignKeyBuilder::Build(BusinessObjectBase *obj)
{

	ForeignKeyBuilder::Build(obj, "");
}



/************************************************************************
*
************************************************************************/

