#include "headers/adaship.h"


void common_randomseed() {
  //initialise random seed based on time
  srand (time(NULL));
}

int common_randomselect(int min, int max, bool reseed) {
	//returns a selected value (at random) based on (and including) the 'min' and 'max' values
	if(reseed) { //reseed if required
		common_randomseed();
	}
	return rand() % ((max+1) - min) + min;
}

