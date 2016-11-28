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
	Columns  _columns;

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
	Columns  _reference_columns;

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


class KeyBuilderBase
{
protected:
	Columns  _columns;

public:
	KeyBuilderBase();

	void AddColumn(BusinessColumnBase * column);

	virtual void Build(BusinessObjectBase *obj) = 0;
	virtual void Build(BusinessObjectBase *obj, std::string name) = 0;
};

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

class PrimaryKeyBuilder : public KeyBuilderBase
{
	friend class PrimaryKey;
	friend class BusinessObjectBase;
	
public:
	PrimaryKeyBuilder();

	void Build(BusinessObjectBase *obj);
	void Build(BusinessObjectBase *obj, std::string name);
};

/************************************************************************
*			ForeignKeyBuilder - ForeignKeyConstraint
************************************************************************/

/*void ForeignKeyConstraint(BusinessObjectBase *obj, BusinessColumnBase &column);
void ForeignKeyConstraint(BusinessObjectBase *obj, BusinessColumnBase &column, std::string name);
void ForeignKeyConstraint(BusinessObjectBase *obj,
	BusinessColumnBase &column1, BusinessColumnBase &column2);
void ForeignKeyConstraint(BusinessObjectBase *obj,
	BusinessColumnBase &column1, BusinessColumnBase &column2,
	std::string name);*/

class ForeignKeyBuilder : public KeyBuilderBase
{
	friend class ForeignKey;
	friend class BusinessObjectBase;

public:
	ForeignKeyBuilder();

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