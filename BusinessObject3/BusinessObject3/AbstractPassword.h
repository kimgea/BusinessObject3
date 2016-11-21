#pragma once
#include "BusinessColumnTypes.h"



class AbstractPassword : public AbstractBusinessObject
{
public:
	PassswordColumn Password;
	CharColumn PasswordHint;
	CharColumn PasswordSalt;

	AbstractPassword();
};
