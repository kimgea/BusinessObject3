#include "stdafx.h"
#include <iostream>
//#include "AbstractPerson.h"
#include "user.h"

#include "BusinessQuery.h"




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

	// Select dos not support picking which fields to select. Will not be added
	// But could be added like current version. person.FirstName.Select()
	std::string ReadSql = person.Read();	

	cout << "CREATE SQL" << std::endl;
	cout << sql << std::endl << std::endl << std::endl;

	person.Password = "";
	cout << "INSERT SQL" << std::endl;
	cout << person.Insert() << std::endl << std::endl << std::endl;
	
	std::string fullName2 = person2.FullName();
	std::string sql2 = person2.Create();

	person.BirthPlace = "Earth";
	Place *place = person.BirthPlaceFK(); // place should idealy get filled with the correct fk values. Skipping this as current structur dos not easely supprt it.
	Place *place2 = person.BirthPlace.FK<Place, CharColumn>();	// Template should be hiddewn shome how... but probablyt not going to bother with it.
	std::string ReadPlaceSQL = place2->Read();


	/////

	std::string squery1 = QueryFunc(person).All();
	std::string squery2 = QueryFunc(person).First();

	std::string squery3 = QueryFunc(person).Filter( 
		person.LastName == "Aase" && person.FirstName == "Kim").All();
	

}