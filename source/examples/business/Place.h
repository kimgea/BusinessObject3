#pragma once
#include "BusinessTable.h"
#include "BusinessColumnTypes.h"

class Place : public BusinessObjectBase
{

public:

	CharColumn PlaceName;

	Place();
};