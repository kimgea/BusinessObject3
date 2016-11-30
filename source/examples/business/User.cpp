#include "stdafx.h"
#include "User.h"


User::User()
{
	_tableName = "user";
	CharColumnMake(this, UserName, "last_name", 30);
	CharColumnMake(this, BirthPlace, "birth_place", 30);

	PrimaryKeyConstraint(this, UserName, _tableName + "_PK1");
	PrimaryKeyConstraint(this, FirstName, LastName, _tableName + "_PK1");
	
	// Hmm... look for a better way to get reference table and column.	
	ForeignKeyConstraint(this, BirthPlace, place.PlaceName, _tableName + "_FK1");
}


Place * User::BirthPlaceFK()
{
	return static_cast<Place*>(BirthPlace.FK());
}