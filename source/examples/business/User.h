#pragma once
#include "BusinessTable.h"

#include "AbstractPerson.h"
#include "AbstractPassword.h"


class User : public AbstractPerson, public AbstractPassword, public BusinessObject
{

public:	

	CharColumn UserName;

	CharColumn BirthPlace;

	User();
};
