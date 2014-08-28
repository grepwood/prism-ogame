#include <stdint.h>
#include <time.h>

#ifndef HAVE_STRUCTS
#define HAVE_STRUCTS
#include "planet.h"
#include "resource.h"
#include "fleet.h"
#include "defense.h"
#include "buildings.h"
#include "research.h"
#endif

char * whosaidthat(FILE ** fp);
uint8_t get_tango(FILE ** fp, struct Planet * sucker);
time_t r_time(FILE ** fp);
char * losersname(FILE ** fp, uint8_t offset);
void booty(FILE ** fp, struct Resource * swag);
uint8_t get_verbosity(FILE ** fp);
uint64_t readfield(char * pattern, char * source);
uint64_t handle64ktab(char * pattern, char * source, uint16_t * offset, uint8_t last);
uint8_t dummies(FILE ** house, struct Fleet * lapdog);
uint8_t bunker(FILE ** hood, struct Defense * fence);
uint8_t shanty(FILE ** bangla, struct Building * shack);
void edumucation(FILE ** artcollege, struct Research * grade);
