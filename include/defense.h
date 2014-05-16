#include <stdint.h>

struct Defense
{
	uint64_t	RL;		/*Rocket Launcher*/
	uint64_t	LL;		/*Light Laser*/
	uint64_t	HL;		/*Heavy Laser*/
	uint64_t	GC;		/*Gauss Cannon*/
	uint64_t	IC;		/*Ion Cannon*/
	uint64_t	PT;		/*Plasma Turret*/
#if __STDC_VERSION < 199901L
	uint8_t		SSD;	/*Small Shield Dome*/
	uint8_t		LSD;	/*Large Shield Dome*/
#else
#	include <stdbool.h>
	bool		SSD;
	bool		LSD;
#endif /*__STDC_VERSION*/
	uint16_t	ABM;	/*Anti-Ballistic Missile*/
	uint16_t	IPBM;	/*Inter-Planetary Ballistic Missile*/
};
