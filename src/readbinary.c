#include 

char isitreport(FILE * lel)
{
	char result = 0;
	char string[9] = {{0}};
	memset(string,0,9);
	fgets(string,8,lel);
	result = strcmp(string,"MDGWPOG1");
	return result;
}

/* 0 - little
   1 - big */
char RBEndianess(FILE * kek)
{
	return fgetc(kek);
}

/* native is for same endianess
   alien is for other endianess */
void readreport_native(FILE * lel)
{
	char buffer[9] = {{0}};
	char verbosity = fgetc(lel);
	char timesize = fgetc(lel);
	time_t tiem = 0;
	char Snitch[21] = {{0}};
	struct Planet TheirPlanet = {{0},{0},0,0,0};
	struct Resource TheirResource = {0,0,0};
	struct Fleet TheirFleet = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	struct Defense TheirDefense = {0,0,0,0,0,0,0,0,0,0};
	struct Building TheirBuildings = {0,0,0,0,0,0,0,0};
	struct Research TheirResearch = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	fread(buffer,timesize,1,lel);
	memcpy(&tiem,buffer,timesize);
	fread(Snitch,20,1,lel);
/* Planet struct */
	fread(TheirPlanet.Name,20,1,lel);
	fread(TheirPlanet.Owner,20,1,lel);
	TheirPlanet.Galaxy = fgetc(lel);
	fread(&TheirPlanet.System,2,1,lel);
	TheirPlanet.Position = fgetc(lel);
/* Resource struct */
	fread(&TheirResource.Metal,4,1,lel);
	fread(&TheirResource.Crystal,4,1,lel);
	fread(&TheirResource.Deuterium,4,1,lel);
/* Verbose structs */
	if(verbosity)
	{
/* Fleet struct */	/* Combat */
		fread(&TheirFleet.LF,8,1,lel);
		fread(&TheirFleet.HF,8,1,lel);
		fread(&TheirFleet.Cr,8,1,lel);
		fread(&TheirFleet.Bs,8,1,lel);
		fread(&TheirFleet.Bc,8,1,lel);
		fread(&TheirFleet.Bo,8,1,lel);
		fread(&TheirFleet.Dr,8,1,lel);
		fread(&TheirFleet.DS,8,1,lel);
					/* Civilian */
		fread(&TheirFleet.SC,8,1,lel);
		fread(&TheirFleet.LC,8,1,lel);
		fread(&TheirFleet.CS,8,1,lel);
		fread(&TheirFleet.Rc,8,1,lel);
		fread(&TheirFleet.EP,8,1,lel);
		fread(&TheirFleet.SS,8,1,lel);
	}
/* Defense struct */
	if(verbosity > 1)
	{
		fread(&TheirDefense.RL,8,1,lel);
		fread(&TheirDefense.LL,8,1,lel);
		fread(&TheirDefense.HL,8,1,lel);
		fread(&TheirDefense.GC,8,1,lel);
		fread(&TheirDefense.IC,8,1,lel);
		fread(&TheirDefense.PT,8,1,lel);
		fgetc(TheirDefense.SSD,lel);
		fgetc(TheirDefense.LSD,lel);
		fread(&TheirDefense.ABM,2,1,lel);
		fread(&TheirDefense.IPBM,2,1,lel);
	}
/* Building struct */
	if(verbosity > 2)
	{
		fgetc(TheirBuilding.MetalMine,lel);
		fgetc(TheirBuilding.CrystalMine,lel);
		fgetc(TheirBuilding.DeutSynth,lel);
		fgetc(TheirBuilding.SolarPlant,lel);
		fgetc(TheirBuilding.FusionReactor,lel);
		fgetc(TheirBuilding.MetalStor,lel);
		fgetc(TheirBuilding.CrystalStor,lel);
		fgetc(TheirBuilding.DeutTank,lel);
	}
/* Research struct */
	if(verbosity > 3)
	{
		fgetc(TheirResearch.EnT,lel);
		fgetc(TheirResearch.LT,lel);
		fgetc(TheirResearch.IT,lel);
		fgetc(TheirResearch.HT,lel);
		fgetc(TheirResearch.PT,lel);
		fgetc(TheirResearch.EsT,lel);
		fgetc(TheirResearch.CT,lel);
		fgetc(TheirResearch.AT,lel);
		fgetc(TheirResearch.IGRN,lel);
		fgetc(TheirResearch.GT,lel);

		fgetc(TheirResearch.CD,lel);
		fgetc(TheirResearch.ID,lel);
		fgetc(TheirResearch.HD,lel);
		fgetc(TheirResearch.WT,lel);
		fgetc(TheirResearch.ST,lel);
		fgetc(TheirResearch.AT,lel);
	}
}

void

void readreport_alien(FILE * lel)
{
	char buffer[9] = {{0}};
	char verbosity = fgetc(lel);
	char timesize = fgetc(lel);
	char count = timesize;
	time_t tiem = 0;
	char Snitch[21] = {{0}};
	struct Planet TheirPlanet = {{0},{0},0,0,0};
	struct Resource TheirResource = {0,0,0};
	struct Fleet TheirFleet = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	struct Defense TheirDefense = {0,0,0,0,0,0,0,0,0,0};
	struct Building TheirBuildings = {0,0,0,0,0,0,0,0};
	struct Research TheirResearch = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	fread(buffer,timesize,1,lel);
	for(; count > 0; --count)
	{
		(&tiem)+(timesize-count) = buffer[count-1];
	}
	memset(buffer,0,9);
	fread(Snitch,20,1,lel);
/* Planet struct */
	fread(TheirPlanet.Name,20,1,lel);
	fread(TheirPlanet.Owner,20,1,lel);
	TheirPlanet.Galaxy = fgetc(lel);
	fread(buffer,2,1,lel);
	for(count = 2; count > 0; --count)
	{
		(&TheirPlanet.System)+(2-count) = buffer[count-1];
	}
	memset(buffer,0,2);
	TheirPlanet.Position = fgetc(lel);
/* Resource struct */
	fread(buffer,4,1,lel);
	for(count = 4; count > 0; --count)
	{
		(&TheirResource.Metal)+(4-count) = buffer[count-1];
	}
	memset(buffer,0,4);
	fwrite(&resource->Crystal,4,1,*dump);
	fread(buffer,4,1,lel);
	for(count = 4; count > 0; --count)
	{
		(&TheirResource.Crystal)+(4-count) = buffer[count-1];
	}
	memset(buffer,0,4);
	fread(buffer,4,1,lel);
	for(count = 4; count > 4; --count)
	{
		(&TheirResource.Deuterium)+(4-count) = buffer[count-1];
	}
	memset(buffer,0,4);
/* Verbose structs */
}
