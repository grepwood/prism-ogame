#include <stdio.h>
#undef __USE_BSD
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>

#include "grepline.h"

#include "readreport.h"

char * whosaidthat(FILE ** fp)
{
	char * line = NULL;
	static char snitch[21];
	char * ptr = NULL;
	size_t length = 0;
	memset(snitch,0,21);
	do
	{
		grepline(&line,&length,*fp);
	}
	while(strncmp(line,"To",2));
	length -= 6;
	if(length <= 20) {
		strncpy(snitch,line+5,length);
		ptr = snitch;
	}
	free(line);
	return ptr;
}

#if !defined LANGUAGE
    #error Language needs to be defined.
#endif

#if LANGUAGE == ENGLISH
    #define DOX_OFFSET 0x1E
#else
    #error Your language is not supported yet. Contact the developer team to resolve this.
#endif

uint8_t get_tango(FILE ** fp, struct Planet * sucker)
{
	char * line = NULL;
	uint8_t count1 = 0;
	uint8_t count2 = 0;
	uint8_t result = 0;
	static char BadGuy[21];
	size_t length = 0;
	memset(BadGuy,0,21);
	puts("Declared");
	do
	{
		grepline(&line,&length,*fp);
	}
	while(strncmp(line,"Subject",7));

	puts("Scanned");
	puts(line);
	for(count1 = DOX_OFFSET; line[count1] != ' ' && line[count1+1] != '['; ++count1, ++count2){}
	if(count2 <= 20) {
		memcpy(BadGuy,line+DOX_OFFSET,count2);
		sucker->Name = BadGuy;
	}
	result += count2;
	puts("Got name");

	for(count2 = 0, count1 = count1+2; line[count1+count2] != ':'; ++count2){}
	sucker->Galaxy = strtol(line+count1,NULL,10);
	result += count2;

	for(count1 = count1+count2+1, count2 = 0; line[count1+count2] != ':'; ++count2){}
	sucker->System = strtol(line+count1,NULL,10);
	result += count2;
	
	for(count1 = count1+count2+1, count2 = 0; line[count1+count2] != ']'; ++count2){}
	sucker->Position = strtol(line+count1,NULL,10);
	result += count2;

	free(line);
	return result;
}

time_t r_time(FILE ** fp)
{
	struct tm tm;
	char * line = NULL;
	size_t length;
	do
	{
		grepline(&line,&length,*fp);
	}
	while(strncmp(line,"Date",4));
	tm.tm_mday = strtol(line+7,NULL,10);
	tm.tm_mon = strtol(line+10,NULL,10)-1;
	tm.tm_year = strtol(line+13,NULL,10)-1900;
	tm.tm_hour = strtol(line+18,NULL,10);
	tm.tm_min = strtol(line+21,NULL,10);
	tm.tm_sec = strtol(line+24,NULL,10);
	tm.tm_isdst = -1;
	free(line);
	return mktime(&tm);
}

char * losersname(FILE ** fp, uint8_t offset)
{
	size_t length = 0;
	uint8_t count = 0;
	char * line = NULL;
	static char result[21];
	char * ptr = NULL;
	memset(result,0,21);
	do {
		grepline(&line,&length,*fp);
	} while(memcmp(line,"Resources on",12));
	grepline(&line,&length,*fp);
	while(line[offset+count] != ')' && line[offset+count+1] != ' '){
		++count;
	}
/* OGame doesn't allow usernames longer than 20 bytes */
	if(count <= 20) {
		strncpy(result,line+offset,count);
		ptr = result;
	}
	free(line);
	return ptr;
}

void booty(FILE ** fp, struct Resource * swag)
{
	size_t length = 0;
	char * line = NULL;
	uint8_t count;
	uint8_t dots;
	uint8_t offset = 7;
	uint8_t lastsize;
	char * number = NULL;
	do
	{
		grepline(&line,&length,*fp);
	}
	while(strncmp(line,"Metal:\t",offset));

	for(count = 0, dots = 0; line[offset+count] != ' ' && line[offset+count+1] != '\t'; ++count)
	{
		if(line[offset+count] != '.')
		{
			number = realloc(number,count+1-dots);
			number[count-dots] = line[offset+count];
		}
		else
		{
			++dots;
		}
	}
	lastsize = count-dots;
	number = realloc(number,lastsize+1);
	number[lastsize] = 0;
	swag->Metal = strtoul(number,NULL,10);
	memset(number,0,lastsize+1);

	for(offset = offset+count+dots+11, dots = 0, count = 0; line[offset+count] != '\n'; ++count)
	{
		if(line[offset+count] != '.')
		{
			if(count-dots == lastsize)
			{
				number = realloc(number,count+1-dots);
			}
			number[count-dots] = line[offset+count];
		}
		else
		{
			++dots;
		}
	}
	lastsize = count-dots;
	number = realloc(number,lastsize+1);
	number[lastsize] = 0;
	swag->Crystal = strtoul(number,NULL,10);
	memset(number,0,lastsize+1);

	grepline(&line,&length,*fp);

	for(offset = 11, dots = 0, count = 0; line[offset+count] != ' ' && line[offset+count+1] != '\t'; ++count)
	{
		if(line[offset+count] != '.')
		{
			if(count-dots == lastsize)
			{
				number = realloc(number,count+1-dots);
			}
			number[count-dots] = line[offset+count];
		}
		else
		{
			++dots;
		}
	}
	lastsize = count-dots;
	number = realloc(number,lastsize+1);
	number[lastsize] = 0;
	swag->Deuterium = strtoul(number,NULL,10);

	free(number);
	free(line);
}

uint8_t get_verbosity(FILE ** fp)
{
	size_t length = 0;
	char * line = NULL;
	do
	{
		grepline(&line,&length,*fp);
	}
	while(strncmp("fleets\n",line,7) && strncmp("Chance of counter-espionage:",line,28));
	if(!strncmp("fleets\n",line,7))
	{
		length = 1;
	}
	if(!strncmp("Chance of counter-espionage:",line,28))
	{
		length = 0;
	}
	free(line);
	return length;
}

uint64_t readfield(char * pattern, char * source)
{
	uint8_t size = strlen(pattern); /* We don't need to pass this as an argument */
	uint8_t comparison = strncmp(pattern,source,size);
	uint64_t result = 0;
	uint8_t limit = 0;
	if(!comparison)
	{
		result = strtoull(source+size+1,NULL,10);
	}
	else
	{
		for(limit = strlen(source); comparison && result+size+1 <= limit; ++result)
		{
			comparison = strncmp(pattern,source+result+1,size);
		}
		if(!comparison)
		{
			result = strtoull(source+result+size+1,NULL,10);
		}
		else
		{
			result = 0;
		}
	}
	return result;
}

uint64_t handle64ktab(char * pattern, char * source, uint16_t * offset, uint8_t last)
{
	uint64_t result = 0;
	uint8_t count = 0;
	for(; !result && count < last; ++count)
	{
		result = readfield(pattern,source+offset[count]);
	}
	return result;
}

uint8_t dummies(FILE ** house, struct Fleet * lapdog)
{
	uint16_t * offset = NULL;
	uint8_t last = 0;
	uint8_t count = 0;
	uint8_t result = 0;
	size_t length = 0;
	char * line = NULL;
	char * buf = NULL;
	do
	{
		grepline(&buf,&length,*house);
		if(strncmp(buf,"Defense\n",8) && strncmp(buf,"Chance of counter-espionage:",28))
		{
			offset = realloc(offset,2*(last+1));
			if(last)
			{
				offset[last] = offset[last-1]+count+1;
			}
			else
			{
				offset[last] = 0;
			}
			line = realloc(line,length+offset[last]+1);
			memset(line+offset[last],0,length+1);
			strncpy(line+offset[last],buf,length);
			++last;
			count = length;
		}
		else
		{
			if(!strncmp(buf,"Defense\n",8))
			{
				result = 1;
			}
			if(!strncmp(buf,"Chance of counter-espionage:",28))
			{
				result = 2;
			}
		}
	}
	while(!result);

	if(last)
	{
/* Combat ships */
		lapdog->LF = handle64ktab("Light Fighter", line, offset, last);
		lapdog->HF = handle64ktab("Heavy Fighter", line, offset, last);
		lapdog->Cr = handle64ktab("Cruiser", line, offset, last);
		lapdog->Bs = handle64ktab("Battleship", line, offset, last);
		lapdog->Bc = handle64ktab("Battlecruiser", line, offset, last);
		lapdog->Bo = handle64ktab("Bomber", line, offset, last);
		lapdog->Dr = handle64ktab("Destroyer", line, offset, last);
		lapdog->DS = handle64ktab("Death Star", line, offset, last);
/* Civilian ships */
		lapdog->SC = handle64ktab("Small Cargo", line, offset, last);
		lapdog->LC = handle64ktab("Large Cargo", line, offset, last);
		lapdog->CS = handle64ktab("Colony Ship", line, offset, last);
		lapdog->Rc = handle64ktab("Recycler", line, offset, last);
		lapdog->EP = handle64ktab("Espionage Probe", line, offset, last);
		lapdog->SS = handle64ktab("Solar Satellite", line, offset, last);
	}
	free(offset);
	free(buf);
	free(line);
	return result%2;
}

uint8_t bunker(FILE ** hood, struct Defense * fence)
{
	uint16_t * offset = NULL;
	uint8_t last = 0;
	uint8_t count = 0;
	uint8_t result = 0;
	size_t length = 0;
	char * line = NULL;
	char * buf = NULL;
	do
	{
		grepline(&buf,&length,*hood);
		if(strncmp(buf,"Building\n",9) && strncmp(buf,"Chance of counter-espionage:",28))
		{
			offset = realloc(offset,2*(last+1));
			if(last)
			{
				offset[last] = offset[last-1]+count+1;
			}
			else
			{
				offset[last] = 0;
			}
			line = realloc(line,length+offset[last]+1);
			memset(line+offset[last],0,length+1);
			strncpy(line+offset[last],buf,length);
			++last;
			count = length;
		}
		else
		{
			if(!strncmp(buf,"Building\n",9))
			{
				result = 1;
			}
			if(!strncmp(buf,"Chance of counter-espionage:",28))
			{
				result = 2;
			}
		}
	}
	while(!result);

	if(last)
	{
		fence->RL = handle64ktab("Rocket Launcher", line, offset, last);
		fence->LL = handle64ktab("Light Laser", line, offset, last);
		fence->HL = handle64ktab("Heavy Laser", line, offset, last);
		fence->GC = handle64ktab("Gauss Cannon", line, offset, last);
		fence->IC = handle64ktab("Ion Cannon", line, offset, last);
		fence->PT = handle64ktab("Plasma Turret", line, offset, last);
		fence->SSD = handle64ktab("Small Shield Dome", line, offset, last);
		fence->LSD = handle64ktab("Large Shield Dome", line, offset, last);
		fence->ABM = handle64ktab("Anti-Ballistic Missiles", line, offset, last);
		fence->IPBM = handle64ktab("Interplanetary Missiles", line, offset, last);
	}
	free(offset);
	free(buf);
	free(line);
	return result%2;
}

uint8_t shanty(FILE ** bangla, struct Building * shack)
{
	uint16_t * offset = NULL;
	uint8_t last = 0;
	uint8_t count = 0;
	uint8_t result = 0;
	size_t length = 0;
	char * line = NULL;
	char * buf = NULL;
	do
	{
		grepline(&buf,&length,*bangla);
		if(strncmp(buf,"Research\n",9) && strncmp(buf,"Chance of counter-espionage:",28))
		{
			offset = realloc(offset,2*(last+1));
			if(last)
			{
				offset[last] = offset[last-1]+count+1;
			}
			else
			{
				offset[last] = 0;
			}
			line = realloc(line,length+offset[last]+1);
			memset(line+offset[last],0,length+1);
			strncpy(line+offset[last],buf,length);
			++last;
			count = length;
		}
		else
		{
			if(!strncmp(buf,"Research\n",9))
			{
				result = 1;
			}
			if(!strncmp(buf,"Chance of counter-espionage:",28))
			{
				result = 2;
			}
		}
	}
	while(!result);

	if(last)
	{
		shack->MetalMine = handle64ktab("Metal Mine", line, offset, last);
		shack->CrystalMine = handle64ktab("Crystal Mine", line, offset, last);
		shack->DeutSynth = handle64ktab("Deuterium Synthesizer", line, offset, last);
		shack->SolarPlant = handle64ktab("Solar Plant", line, offset, last);
		shack->FusionReactor = handle64ktab("Fusion Reactor", line, offset, last);
		shack->MetalStor = handle64ktab("Metal Storage", line, offset, last);
		shack->CrystalStor = handle64ktab("Crystal Storage", line, offset, last);
		shack->DeutTank = handle64ktab("Deuterium Tank", line, offset, last);
	}
	free(offset);
	free(buf);
	free(line);
	return result%2;
}

void edumucation(FILE ** artcollege, struct Research * grade)
{
	uint16_t * offset = NULL;
	uint8_t last = 0;
	uint8_t count = 0;
	uint8_t result = 0;
	size_t length = 0;
	char * line = NULL;
	char * buf = NULL;
	do
	{
		grepline(&buf,&length,*artcollege);
		if(strncmp(buf,"Chance of counter-espionage:",28))
		{
			offset = realloc(offset,2*(last+1));
			if(last)
			{
				offset[last] = offset[last-1]+count+1;
			}
			else
			{
				offset[last] = 0;
			}
			line = realloc(line,length+offset[last]+1);
			memset(line+offset[last],0,length+1);
			strncpy(line+offset[last],buf,length);
			++last;
			count = length;
		}
		else
		{
			result = 1;
		}
	}
	while(!result);

	if(last)
	{
		grade->EnT = handle64ktab("Energy Technology", line, offset, last);
		grade->LT = handle64ktab("Laser Technology", line, offset, last);
		grade->IT = handle64ktab("Ion Technology", line, offset, last);
		grade->HT = handle64ktab("Hyperspace Technology", line, offset, last);
		grade->PT = handle64ktab("Plasma Technology", line, offset, last);
		grade->EsT = handle64ktab("Espionage Technology", line, offset, last);
		grade->CT = handle64ktab("Computer Technology", line, offset, last);
		grade->AP = handle64ktab("Astrophysics", line, offset, last);
		grade->IGRN = handle64ktab("Intergalactic Research Network", line, offset, last);
		grade->GT = handle64ktab("Graviton Technology", line, offset, last);
		grade->CD = handle64ktab("Combustion Drive", line, offset, last);
		grade->ID = handle64ktab("Impulse Drive", line, offset, last);
		grade->HD = handle64ktab("Hyperspace Drive", line, offset, last);
		grade->WT = handle64ktab("Weapons Technology", line, offset, last);
		grade->ST = handle64ktab("Shielding Technology", line, offset, last);
		grade->AT = handle64ktab("Armour Technology", line, offset, last);
	}
	free(offset);
	free(buf);
	free(line);
}

