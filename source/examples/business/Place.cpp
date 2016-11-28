#include "stdafx.h"

#include "Place.h"


Place::Place()
{
	_tableName = "place";
	CharColumnMake(this, PlaceName, "place_name", 30);

}