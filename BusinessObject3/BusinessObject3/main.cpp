#include "stdafx.h"
//#include "AbstractPerson.h"
#include "user.h"





using namespace std;
int main()
{
	User person;
	person.FirstName = "Kim-Georg";
	person.LastName = "Aase";
	
	User person2;
	person2 = person;
	person2.FirstName = "Kim";
	person2.LastName = "Aase2";

	std::string pw = person.Password;
	std::string fullName = person.FullName();
	std::string sql = person.SqlCreate();
	
	std::string fullName2 = person2.FullName();
	std::string sql2 = person2.SqlCreate();

}