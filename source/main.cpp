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
	//person2.LastName = "Aase2";

	//AbstractPerson aPerson;
	//aPerson = person;
	
	std::string pw = person.Password;
	std::string fullName = person.FullName();
	std::string sql = person.Create();

	cout << sql << std::endl;
	
	std::string fullName2 = person2.FullName();
	std::string sql2 = person2.Create();

	person.BirthPlace = "Earth";
	Place *place = person.BirthPlaceFK(); // place should idealy get filled with the correct fk values. Skipping this as current structur dos not easely supprt it.
	Place *place2 = person.BirthPlace.FK<Place, CharColumn>();	// Template should be hiddewn shome how... but probablyt not going to bother with it.
}