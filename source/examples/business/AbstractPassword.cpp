#include "stdafx.h"
#include "AbstractPassword.h"


AbstractPassword::AbstractPassword()
{
	Password.Init(this, "password", 30, true, "********");
	PasswordHint.Init(this, "last_name", 30, true, "");
	PasswordSalt.Init(this, "last_name", 30, true, "");	

}