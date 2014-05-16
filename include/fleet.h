#include <stdint.h>

struct Fleet
{
	uint64_t LF;	/*Light Fighter*/
	uint64_t HF;	/*Heavy Fighter*/
	uint64_t Cr;	/*Cruiser*/
	uint64_t Bs;	/*Battleship*/
	uint64_t Bc;	/*Battlecruiser*/
	uint64_t Bo;	/*Bomber*/
	uint64_t Dr;	/*Destroyer*/
	uint64_t DS;	/*Death Star*/

	uint64_t SC;	/*Small Cargo*/
	uint64_t LC;	/*Large Cargo*/
	uint64_t CS;	/*Colony Ship*/
	uint64_t Rc;	/*Recycler*/
	uint64_t EP;	/*Espionage Probe*/
	uint64_t SS;	/*Solar Satellite*/
};
