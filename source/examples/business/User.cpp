#include "stdafx.h"
#include "User.h"


User::User()
{
	_tableName = "user";
	UserName.Init(this, "last_name", 30);

	PrimaryKeyConstraint(this, &UserName, _tableName + "_PK1");
	PrimaryKeyConstraint(this, &FirstName, &LastName, _tableName + "_PK1");
		
	// ForeignKeyConstraint
	// Work with either input from reference table and its column, or a string describing its db name
}