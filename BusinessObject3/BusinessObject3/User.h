#pragma once

#include "BusinessObject.h"
#include "BusinessColumn.h"
#include "AbstractPerson.h"
#include "AbstractCommonDates.h"
#include "AbstractPassword.h"
 

class User : public AbstractPerson, public AbstractPassword, public BusinessObject
{
public:
	CharColumn UserName;

	User();
};
