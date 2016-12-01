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
	friend class ForeignKey;
	
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

	std::string TableName();

	std::string Create();
	std::string Drop();
	
	std::string Read();
	std::string Insert();
	/*std::string Update();
	std::string Save();*/


};

/************************************************************************/


