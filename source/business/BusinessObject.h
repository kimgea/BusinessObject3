#pragma once
#include <vector>
#include <functional>
#include <memory>

class ForeignKey;
class PrimaryKey;
class PrimaryKeyBuilder;
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
*
*
*
*
************************************************************************/

class BusinessObjectBase 
{
	friend class PrimaryKeyBuilder;
	friend class BusinessColumnBase;
	
private:
	Columns _columns;
	PrimaryKeys _primary_keys;
	ForeignKeys _foreign_keys;

protected:	
	std::string _tableName;	
		
	void AddPrimaryKey(PrimaryKey *primary_key);
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
*
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

	virtual std::string SqlCreatePart();

public:
	BusinessColumnBase();	

	void Init(BusinessObjectBase *obj, std::string columnName);

	virtual std::string ToString() const;	
	
	std::string ColumnName();

	operator std::string() const;	

	bool HasValue();
	

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

class PrimaryKey 
{
	friend class PrimaryKeyBuilder;
	friend class BusinessObjectBase;

protected:
	BusinessObjectBase *_obj;
	std::string _key_name;
	Columns  _columns;

	std::string SqlCreatePart();
	
public:
	PrimaryKey() {}	
};


/************************************************************************/

class ForeignKey
{
	friend class PrimaryKeyBuilder;
	friend class BusinessObjectBase;

protected:
	BusinessObjectBase *_obj;
	std::string _key_name;
	//Columns  _columns;

	//std::string SqlCreatePart();

public:
	ForeignKey() {}
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

void PrimaryKeyConstraint(BusinessObjectBase *obj, BusinessColumnBase * column);
void PrimaryKeyConstraint(BusinessObjectBase *obj, BusinessColumnBase * column, std::string name);

void PrimaryKeyConstraint(BusinessObjectBase *obj,
	BusinessColumnBase * column1, BusinessColumnBase * column2);
void PrimaryKeyConstraint(BusinessObjectBase *obj,
	BusinessColumnBase * column1, BusinessColumnBase * column2, 
	std::string name);

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

/************************************************************************/

/*class ForeignKeyBuilder
{
	//friend class PrimaryKeyBuilder;
	friend class BusinessObjectBase;

protected:
	BusinessObjectBase *_obj;
	std::string _key_name;
	//Columns  _columns;

	//std::string SqlCreatePart();

public:
	ForeignKey() {}
};*/