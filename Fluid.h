#include <iostream>
#include "FluidDB.h"

#ifndef FLUID_H
#define FLUID_H

class Fluid
{
public:
	// Sets the name of the database
	fluid(string dbname);
	// Appends to the end of a certain boat
	add(json addition);

private:
	string databasename;
};

#endif