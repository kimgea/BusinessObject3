#pragma once
 #include "BusinessColumnTypes.h"
//#include "temp.h"


class AbstractPerson : public AbstractBusinessObject
{
public:
	CharColumn FirstName;
	CharColumn LastName;
	

	AbstractPerson();
	std::string FullName();

};