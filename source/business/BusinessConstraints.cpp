#include "stdafx.h"
#include "BusinessObject.h"



KeyBuilderBase::KeyBuilderBase()
{
}

void KeyBuilderBase::AddColumn(BusinessColumnBase * column)
{
	_columns.push_back(column);
}


/*******************************************************************/

void PrimaryKeyConstraint(BusinessObjectBase * obj, BusinessColumnBase * column)
{
	PrimaryKeyBuilder builder;
	builder.AddColumn(column);
	builder.Build(obj);
}

void PrimaryKeyConstraint(BusinessObjectBase * obj, BusinessColumnBase * column, std::string name)
{
	PrimaryKeyBuilder builder;
	builder.AddColumn(column);
	builder.Build(obj, name);
}


void PrimaryKeyConstraint(BusinessObjectBase * obj,
	BusinessColumnBase * column1, BusinessColumnBase * column2)
{
	PrimaryKeyBuilder builder;
	builder.AddColumn(column1);
	builder.AddColumn(column2);
	builder.Build(obj);
}

void PrimaryKeyConstraint(BusinessObjectBase * obj,
	BusinessColumnBase * column1, BusinessColumnBase * column2, 
	std::string name)
{
	PrimaryKeyBuilder builder;
	builder.AddColumn(column1);
	builder.AddColumn(column2);
	builder.Build(obj, name);
}

/*******************************************************************/
PrimaryKeyBuilder::PrimaryKeyBuilder()
{
}

void PrimaryKeyBuilder::Build(BusinessObjectBase *obj, std::string name)
{
	//std::shared_ptr<PrimaryKey> pk(new PrimaryKey);
	PrimaryKey *pk = new PrimaryKey;
	pk->_key_name = name;
	pk->_obj = obj;
	pk->_columns = _columns;
	obj->AddPrimaryKey(pk);	// Must be friend
	_columns.clear();
}
void PrimaryKeyBuilder::Build(BusinessObjectBase *obj)
{

	PrimaryKeyBuilder::Build(obj, "");
}

/*******************************************************************/

/*******************************************************************/

ForeignKeyBuilder::ForeignKeyBuilder()
{
}

void ForeignKeyBuilder::Build(BusinessObjectBase *obj, std::string name)
{
	
}
void ForeignKeyBuilder::Build(BusinessObjectBase *obj)
{

	ForeignKeyBuilder::Build(obj, "");
}

/************************************************************************
*
************************************************************************/



std::string PrimaryKey::SqlCreatePart()
{
	bool has_name = (_key_name.size() > 0);
	bool is_one = (_columns.size() == 1);

	if (!has_name && is_one)
		return "PRIMARY KEY (" + _columns.front()->ColumnName() + ")";
	else if (has_name && is_one)
		return "CONSTRAINT " + _key_name + " PRIMARY KEY (" + _columns.front()->ColumnName()  + ")";
	
	std::string primary_columns = _columns.front()->ColumnName() + ",";
	for (ColumnItr itr = ++_columns.begin(); itr != _columns.end(); itr++)
	{
		primary_columns += (*itr)->ColumnName() + ",";
	}
	primary_columns.pop_back();
	return "CONSTRAINT " + _key_name + " PRIMARY KEY (" + primary_columns + ")";
}



/*******************************************************************/

std::string ForeignKey::SqlCreatePart()
{
	return std::string();
}

/************************************************************************
*
************************************************************************/

