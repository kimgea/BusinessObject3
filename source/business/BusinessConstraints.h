#pragma once

#include "BusinessObject.h"



class KeyBase
{
	friend class BusinessObjectBase;

protected:
	BusinessObjectBase *_obj;
	std::string _key_name;


	virtual std::string SqlCreatePart() { return std::string(); }

public:
	KeyBase() {}
	virtual ~KeyBase() {}
};

/************************************************************************
*			PrimaryKey
************************************************************************/

class PrimaryKey : public KeyBase
{
	friend class PrimaryKeyBuilder;
	friend class BusinessObjectBase;

protected:
	Columns  _columns;

	std::string SqlCreatePart();

public:
	PrimaryKey() {}

	bool HasValues();
};


/************************************************************************
*			ForeignKey
************************************************************************/

class ForeignKey : public KeyBase
{
	friend class ForeignKeyBuilder;
	friend class BusinessObjectBase;

protected:
	typedef std::vector<std::pair<BusinessColumnBase*, BusinessColumnBase*>> ColumnsRelations;
	ColumnsRelations  _column_relations;

	std::string SqlCreatePart();

public:
	ForeignKey() {}

	template<class TABLE, class COLUMN>
	TABLE * RelatedTable()
	{
		for (auto itr = _column_relations.begin(); itr != _column_relations.end(); itr++)
		{
			COLUMN *c1 = dynamic_cast<COLUMN*>(itr->second);
			COLUMN *c2 = dynamic_cast<COLUMN*>(itr->first);
			*c1 = *c2;
		}
		return static_cast<TABLE*>(_column_relations.front().second->_obj);
	}
};

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

void PrimaryKeyConstraint(BusinessObjectBase *obj, BusinessColumnBase &column);
void PrimaryKeyConstraint(BusinessObjectBase *obj, BusinessColumnBase &column, std::string name);

void PrimaryKeyConstraint(BusinessObjectBase *obj,
	BusinessColumnBase &column1, BusinessColumnBase &column2);
void PrimaryKeyConstraint(BusinessObjectBase *obj,
	BusinessColumnBase &column1, BusinessColumnBase &column2,
	std::string name);

/*******************************************************************/

class PrimaryKeyBuilder
{
	friend class PrimaryKey;
	friend class BusinessObjectBase;

protected:
	Columns  _columns;

public:
	PrimaryKeyBuilder();

	void AddColumn(BusinessColumnBase * column);

	void Build(BusinessObjectBase *obj);
	void Build(BusinessObjectBase *obj, std::string name);
};

/************************************************************************
*			ForeignKeyBuilder - ForeignKeyConstraint
************************************************************************/

void ForeignKeyConstraint(BusinessObjectBase *obj, BusinessColumnBase &columnKey, BusinessColumnBase &columnReference);
void ForeignKeyConstraint(BusinessObjectBase *obj, BusinessColumnBase &columnKey, BusinessColumnBase &columnReference, std::string name);
void ForeignKeyConstraint(BusinessObjectBase *obj,
	BusinessColumnBase &columnKey1, BusinessColumnBase &columnReference1,
	BusinessColumnBase &columnKey2, BusinessColumnBase &columnReference2);
void ForeignKeyConstraint(BusinessObjectBase *obj,
	BusinessColumnBase &columnKey1, BusinessColumnBase &columnReference1,
	BusinessColumnBase &columnKey2, BusinessColumnBase &columnReference2,
	std::string name);

class ForeignKeyBuilder
{
	friend class ForeignKey;
	friend class BusinessObjectBase;

protected:
	typedef std::vector<std::pair<BusinessColumnBase*, BusinessColumnBase*>> ColumnsRelations;
	ColumnsRelations  _column_relations;

public:
	ForeignKeyBuilder();

	void AddRelation(BusinessColumnBase * columnKey, BusinessColumnBase * columnReference);

	void Build(BusinessObjectBase *obj);
	void Build(BusinessObjectBase *obj, std::string name);
};


/************************************************************************
*
*
*
*
*
*
*
************************************************************************/
