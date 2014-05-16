#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "readreport.h"

#if LANGUAGE == ENGLISH
#	define PLAYER_N 6
#else
#	error Define language.
#endif

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		puts("No file detected");
		exit(0);
	}
	FILE * fp;
	char * snitch = NULL;
	time_t tiem = 0;
	uint8_t verbosity = 0;
	uint8_t NameOffset = 9+PLAYER_N;
	struct Planet TheirPlanet = {NULL,NULL,0,0,0};
	struct Resource TheirResource = {0,0,0};
	struct Fleet TheirFleet = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	struct Defense TheirDefense = {0,0,0,0,0,0,0,0,0,0};
	struct Building TheirBuildings = {0,0,0,0,0,0,0,0};
	struct Research TheirResearch = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	fp = fopen(argv[1],"r");
	if(fp == NULL)
	{
		puts("Null or nonexistent file");
		exit(0);
	}

	whosaidthat(&fp, &snitch);
	get_tango(&fp, &TheirPlanet,&NameOffset);
	tiem = r_time(&fp);
	losersname(&fp,&TheirPlanet.Owner,NameOffset);
	booty(&fp, &TheirResource);
	verbosity = get_verbosity(&fp);
	if(verbosity == 1)
	{
		verbosity += dummies(&fp,&TheirFleet);
	}
	if(verbosity == 2)
	{
		verbosity += bunker(&fp,&TheirDefense);
	}
	if(verbosity == 3)
	{
		verbosity += shanty(&fp,&TheirBuildings);
	}
	if(verbosity == 4)
	{
		edumucation(&fp,&TheirResearch);
	}

/*	printf("Metal: %lu\nCrystal: %lu\nDeuterium: %lu\n",TheirResource.Metal,TheirResource.Crystal,TheirResource.Deuterium);
*/	printf("%llu\n",(long long)tiem);

	free(TheirPlanet.Owner);
	free(TheirPlanet.Name);
	free(snitch);
	fclose(fp);
	return 0;
}
