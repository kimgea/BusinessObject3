#include "stdafx.h"
#include <iostream>
//#include "AbstractPerson.h"
#include "user.h"





using namespace std;
int main()
{
	User person;
	person.FirstName = "Kim-Georg";
	person.LastName = "Aase";
	
	//person.PK1

	User person2;
	person2 = person;
	person2.FirstName = "Kim";
	person2.LastName = "Aase2";

	//AbstractPerson aPerson;
	//aPerson = person;

	std::string pw = person.Password;
	std::string fullName = person.FullName();
	std::string sql = person.Create();

	cout << sql << std::endl;
	
	std::string fullName2 = person2.FullName();
	std::string sql2 = person2.Create();

}