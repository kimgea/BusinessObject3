#include "stdafx.h"
#include "AbstractPassword.h"


AbstractPassword::AbstractPassword()
{
	CharColumnMake(this, Password, "password", 30, true, "********");
	CharColumnMake(this, PasswordHint, "password_hint", 30, true, "");
	CharColumnMake(this, PasswordSalt, "salt", 30, true, "");
}