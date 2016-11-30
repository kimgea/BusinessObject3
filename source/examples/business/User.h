#pragma once
#include "BusinessTable.h"

#include "AbstractPerson.h"
#include "AbstractPassword.h"
#include "Place.h"

class User : public AbstractPerson, public AbstractPassword, public BusinessObject
{

protected:
	Place place;	// Foregin relation.... must find a better way to do this

public:	

	CharColumn UserName;
	CharColumn BirthPlace;

	Place* BirthPlaceFK();

	User();
};
