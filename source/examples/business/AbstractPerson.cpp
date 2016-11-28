#include "stdafx.h"
#include "AbstractPerson.h"


AbstractPerson::AbstractPerson()
{
	
	// TODO: ?? Do not init in abstract classes, do it from concreat table mapped classes instead. 
	//			Thath way it will be more flexible in case of different column requirments.
	CharColumnMake(this, FirstName, "first_name", 30);
	CharColumnMake(this, LastName, "last_name", 30);
}


std::string AbstractPerson::FullName()
{
	return FirstName + " " + LastName; 
}
