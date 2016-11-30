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
	// A perfect solution should try to remove the templates, they should happend in the background without the user neading to use it.
	return BirthPlace.FK<Place, CharColumn>();	// Currently FK and reference column must be of the same column type
}