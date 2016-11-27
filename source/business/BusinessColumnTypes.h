#pragma once
#include "BusinessColumn.h"



/**************************************************************
*
*		Base Columns types - usable
*
**************************************************************/
/*
	TODO:
		- Make naming optional
*/
class CharColumn : public BusinessColumnTypeBase<std::string>
{
protected:
	unsigned int _maxSize;

	std::string SqlCreatePart();

public:
	CharColumn() : BusinessColumnTypeBase<std::string>() {}

	void Init(BusinessObjectBase *obj, std::string columnName, unsigned int MaxSize);
	void Init(BusinessObjectBase *obj, std::string columnName, unsigned int MaxSize, bool notNull, std::string defaultValue);

	// TODO: Is it possible to avoid adding this line all column types?
	CharColumn& operator=(const std::string &value);

	unsigned int GetMaxSize();

	std::string ToString() const;


	
};


/**************************************************************
*
*
*
**************************************************************/
class PassswordColumn : public CharColumn
{
public:
	PassswordColumn() : CharColumn() {}

	// TODO: Is it possible to avoid adding this line all column types?
	PassswordColumn& operator=(const std::string &value);

};



/**************************************************************
*
*		Specialiced columns derived from one of the Base Columns types - usable
*
**************************************************************/























/*
template<class TABLE>
class IntegerColumn : public BusinessColumnBase<TABLE,int>
{
public:
IntegerColumn() {}
IntegerColumn(TABLE &obj, std::string columnName);
};
*/
/*class BigIntColumn : public BusinessColumnBase<long long>
{
public:
BigIntColumn(BusinessObject &obj, std::string columnName);
};*/

/*
template<class TABLE>
class DoubleColumn : public BusinessColumnBase<TABLE, double>
{
public:
DoubleColumn() {}
DoubleColumn(TABLE &obj, std::string columnName);
};
*/
/*class TextColumn : public BusinessColumnBase<std::string>
{
public:
TextColumn(BusinessObject &obj, std::string columnName);
};*/

/*
template<class TABLE>
class DateTimeColumn : public BusinessColumnBase<TABLE, int> // TODO: DateTime
{
public:
DateTimeColumn() {}
DateTimeColumn(TABLE &obj, std::string columnName);
};
*/

//////

/*
template<class TABLE>
class PasswordColumn : public BusinessColumnBase<TABLE, std::string>
{
public:
PasswordColumn() {}
PasswordColumn(TABLE &obj, std::string columnName);
};
*/




/*class EnumColumn : public BusinessColumnBase
{	// HOW????
public:
EnumColumn(BusinessObject &obj, std::string columnName);
};*/

