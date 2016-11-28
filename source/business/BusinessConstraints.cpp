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



/************************************************************************
*			ForeignKey
************************************************************************/

std::string ForeignKey::SqlCreatePart()
{
	return std::string();
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

KeyBuilderBase::KeyBuilderBase()
{
}

void KeyBuilderBase::AddColumn(BusinessColumnBase * column)
{
	_columns.push_back(column);
}


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

/*void ForeignKeyConstraint(BusinessObjectBase * obj, BusinessColumnBase &column)
{
	ForeignKeyBuilder builder;
	builder.AddColumn(&column);
	builder.Build(obj);
}

void ForeignKeyConstraint(BusinessObjectBase * obj, BusinessColumnBase &column, std::string name)
{
	ForeignKeyBuilder builder;
	builder.AddColumn(&column);
	builder.Build(obj, name);
}

void ForeignKeyConstraint(BusinessObjectBase * obj,
	BusinessColumnBase &column1, BusinessColumnBase &column2)
{
	PrimaryKeyBuilder builder;
	builder.AddColumn(&column1);
	builder.AddColumn(&column2);
	builder.Build(obj);
}

void ForeignKeyConstraint(BusinessObjectBase * obj,
	BusinessColumnBase &column1, BusinessColumnBase &column2,
	std::string name)
{
	PrimaryKeyBuilder builder;
	builder.AddColumn(&column1);
	builder.AddColumn(&column2);
	builder.Build(obj, name);
}*/

/*******************************************************************/

ForeignKeyBuilder::ForeignKeyBuilder()
{
}

void ForeignKeyBuilder::Build(BusinessObjectBase *obj, std::string name)
{
	std::unique_ptr<ForeignKey> pk;
	pk = std::make_unique<ForeignKey>();
	pk->_key_name = name;
	pk->_obj = obj;
	pk->_columns = _columns;
	obj->AddForeignKey(std::move(pk));	// Must be friend
	_columns.clear();
}
void ForeignKeyBuilder::Build(BusinessObjectBase *obj)
{

	ForeignKeyBuilder::Build(obj, "");
}



/************************************************************************
*
************************************************************************/

