#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readreport.h"
#include "pog-endian.h" /* DO NOT CALL IT endian.h !!! */

#if LANGUAGE == ENGLISH
#	define PLAYER_N 5
#else
#	error Define language.
#endif

#ifndef HAVE_STRUCTS
#define HAVE_STRUCTS
#include "planet.h"
#include "resource.h"
#include "fleet.h"
#include "defense.h"
#include "buildings.h"
#include "research.h"
#endif

char * magic = "MDGWPOG1";

void dumpPlanet(FILE ** dump, struct Planet * planet)
{
	fwrite(planet->Name,20,1,*dump);
	fwrite(planet->Owner,20,1,*dump);
	fputc(planet->Galaxy,*dump);
	fwrite(&planet->System,2,1,*dump);
	fputc(planet->Position,*dump);
}

void dumpResource(FILE ** dump, struct Resource * resource)
{
	fwrite(&resource->Metal,4,1,*dump);
	fwrite(&resource->Crystal,4,1,*dump);
	fwrite(&resource->Deuterium,4,1,*dump);
}

void dumpFleet(FILE ** dump, struct Fleet * fleet)
{	/* Combat ships */
	fwrite(&fleet->LF,8,1,*dump);
	fwrite(&fleet->HF,8,1,*dump);
	fwrite(&fleet->Cr,8,1,*dump);
	fwrite(&fleet->Bs,8,1,*dump);
	fwrite(&fleet->Bc,8,1,*dump);
	fwrite(&fleet->Bo,8,1,*dump);
	fwrite(&fleet->Dr,8,1,*dump);
	fwrite(&fleet->DS,8,1,*dump);
/* Civilian ships */
	fwrite(&fleet->SC,8,1,*dump);
	fwrite(&fleet->LC,8,1,*dump);
	fwrite(&fleet->CS,8,1,*dump);
	fwrite(&fleet->Rc,8,1,*dump);
	fwrite(&fleet->EP,8,1,*dump);
	fwrite(&fleet->SS,8,1,*dump);
}

void dumpDefense(FILE ** dump, struct Defense * def)
{
	fwrite(&def->RL,8,1,*dump);
	fwrite(&def->LL,8,1,*dump);
	fwrite(&def->HL,8,1,*dump);
	fwrite(&def->GC,8,1,*dump);
	fwrite(&def->IC,8,1,*dump);
	fwrite(&def->PT,8,1,*dump);
	fputc(def->SSD,*dump);
	fputc(def->LSD,*dump);
	fwrite(&def->ABM,2,1,*dump);
	fwrite(&def->IPBM,2,1,*dump);
}

void dumpBuildings(FILE ** dump, struct Building * b)
{
	fputc(b->MetalMine,*dump);
	fputc(b->CrystalMine,*dump);
	fputc(b->DeutSynth,*dump);
	fputc(b->SolarPlant,*dump);
	fputc(b->FusionReactor,*dump);
	fputc(b->MetalStor,*dump);
	fputc(b->CrystalStor,*dump);
	fputc(b->DeutTank,*dump);
}

void dumpResearch(FILE ** dump, struct Research * r)
{
	fputc(r->EnT,*dump);
	fputc(r->LT,*dump);
	fputc(r->IT,*dump);
	fputc(r->HT,*dump);
	fputc(r->PT,*dump);
	fputc(r->EsT,*dump);
	fputc(r->CT,*dump);
	fputc(r->AT,*dump);
	fputc(r->IGRN,*dump);
	fputc(r->GT,*dump);

	fputc(r->CD,*dump);
	fputc(r->ID,*dump);
	fputc(r->HD,*dump);
	fputc(r->WT,*dump);
	fputc(r->ST,*dump);
	fputc(r->AT,*dump);
}

void pfhor(FILE ** report, FILE ** dump)
{
/* Initialize memory */
	char * snitch;
	time_t tiem = 0;
	uint8_t verbosity = 0;
	uint8_t NameOffset = 9+PLAYER_N; /* Recycled into various values later on */
	struct Planet TheirPlanet = {NULL,NULL,0,0,0};
	struct Resource TheirResource = {0,0,0};
	struct Fleet TheirFleet = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	struct Defense TheirDefense = {0,0,0,0,0,0,0,0,0,0};
	struct Building TheirBuildings = {0,0,0,0,0,0,0,0};
	struct Research TheirResearch = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
/* Time to read */
	snitch = whosaidthat(report);
	NameOffset += get_tango(report, &TheirPlanet);
	tiem = r_time(report);
	TheirPlanet.Owner = losersname(report,NameOffset);
	booty(report, &TheirResource);
	verbosity = get_verbosity(report);
/* We can start dropping while still collecting */
	NameOffset = is_big_endian();	/* What is my endianess? */
	fputs(magic,*dump);		/* prism-ogame dump signature, aka magic number */
	fputc(NameOffset,*dump);		/* writing localhost endianess */
/* The following parts depend on the report's verbosity */
	if(verbosity == 1)
	{
		verbosity += dummies(report,&TheirFleet);
	}
	if(verbosity == 2)
	{
		verbosity += bunker(report,&TheirDefense);
	}
	if(verbosity == 3)
	{
		verbosity += shanty(report,&TheirBuildings);
	}
	if(verbosity == 4)
	{
		edumucation(report,&TheirResearch);
	}
	fputc(verbosity,*dump);				/* verbosity definitely established */
	NameOffset = sizeof(time_t);
	fputc(NameOffset,*dump);			/* writing down time size because this is variable although IT SHOULDN'T */
	fwrite(&tiem,NameOffset,1,*dump);
	fwrite(snitch,20,1,*dump);			/* who said that */
	dumpPlanet(dump,&TheirPlanet);		/* dumping planet struct */
	dumpResource(dump,&TheirResource);	/* dumping booty */
/* We may begin dumping the juicy bits */
	if(verbosity > 0)
	{
		dumpFleet(dump,&TheirFleet);
	}
	if(verbosity > 1)
	{
		dumpDefense(dump,&TheirDefense);
	}
	if(verbosity > 2)
	{
		dumpBuildings(dump,&TheirBuildings);
	}
	if(verbosity > 3)
	{
		dumpResearch(dump,&TheirResearch);
	}
}
