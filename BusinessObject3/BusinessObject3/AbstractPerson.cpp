#include "stdafx.h"
#include "AbstractPerson.h"


AbstractPerson::AbstractPerson()
{
	//_tableName = "abstractPerson";	// NB: temp. should not be set in abstract
	
	FirstName.Init(this, "first_name", 30);
	LastName.Init(this, "last_name", 30);	
}


std::string AbstractPerson::FullName()
{
	return FirstName + " " + LastName; 
}
