#ifndef HAVE_STRUCTS
#define HAVE_STRUCTS
#include "planet.h"
#include "resource.h"
#include "fleet.h"
#include "defense.h"
#include "buildings.h"
#include "research.h"
#endif

void dumpPlanet(FILE ** dump, struct Planet * planet);
void pfhor(FILE ** dox, FILE ** dump);
