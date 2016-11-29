#pragma once
#include <vector>
#include <functional>
#include <memory>

class ForeignKey;
class PrimaryKey;
class PrimaryKeyBuilder;
class ForeignKeyBuilder;
class BusinessColumnBase;


typedef std::vector<BusinessColumnBase*> Columns;
typedef Columns::iterator ColumnItr;
typedef Columns::const_iterator ColumnConstItr;

typedef std::vector<std::unique_ptr<PrimaryKey>> PrimaryKeys;
typedef PrimaryKeys::iterator PrimaryKeyItr;

typedef std::vector<std::unique_ptr<ForeignKey>> ForeignKeys;
typedef ForeignKeys::iterator ForeignKeyItr;



/************************************************************************
*
*
*
*		Table
*
*
*
************************************************************************/

class BusinessObjectBase 
{
	friend class PrimaryKeyBuilder;
	friend class ForeignKeyBuilder;
	friend class BusinessColumnBase;
	
private:
	Columns _columns;
	PrimaryKeys _primary_keys;
	ForeignKeys _foreign_keys;

protected:	
	std::string _tableName;	
		
	void AddPrimaryKey(std::unique_ptr<PrimaryKey> &&primary_key);
	void AddForeignKey(std::unique_ptr<ForeignKey> &&foreign_key);
	void AddColumn(BusinessColumnBase *column);

public:
	BusinessObjectBase();
	virtual ~BusinessObjectBase() {};	

	// TODO: WARNING: This one is currently not safe
	BusinessObjectBase& operator=(const BusinessObjectBase &rhs);	

	std::string Create();
	std::string Drop();
	
	/*std::string Insert();
	std::string Update();
	std::string Save();*/


};

/************************************************************************/





/************************************************************************
*
*
*
*			Column
*		
*
*
************************************************************************/


class BusinessColumnBase
{
	friend class BusinessObjectBase;

protected:
	BusinessObjectBase *_obj;
	std::string _columnName;
	bool _notNull;
	bool _hasValue;

	void Init(BusinessObjectBase *obj, std::string columnName);

	virtual std::string SqlCreatePart();

public:
	BusinessColumnBase();		

	virtual std::string ToString() const;	
	
	std::string ColumnName();

	operator std::string() const;	

	bool HasValue();
	
};


/************************************************************************
*
*
*
*		KEYS  (Primary and Foreign)
*
*
*
************************************************************************/

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