#include "stdafx.h"
#include "User.h"

User::User()
{
	_tableName = "user";
	UserName.Init(this, "last_name", 30);
}