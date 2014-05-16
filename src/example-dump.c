#include <stdio.h>
#undef __USE_BSD
#include <time.h>
#include <string.h>

#include "readreport.h"
#include "dumpmem.h"

#include <stdlib.h>

int main(int argc, char * argv[])
{
	FILE * report;
	FILE * dump;
	if(argc != 3)
	{
		printf("Syntax: %s report-file dump-file\n",argv[0]);
		exit(0);
	}
	report = fopen(argv[1],"r");
	dump = fopen(argv[2],"wb");
	pfhor(&report,&dump);
	fclose(report);
	fclose(dump);
	return 0;
}
