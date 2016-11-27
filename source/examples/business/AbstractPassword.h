#pragma once
#include "BusinessTable.h"
#include "BusinessColumnTypes.h"



class AbstractPassword : public AbstractBusinessObject
{
public:
	PassswordColumn Password;
	CharColumn PasswordHint;
	CharColumn PasswordSalt;

	AbstractPassword();
};
