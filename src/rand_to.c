#include <stdlib.h>

#include "rand_to.h"

int rand_to(int min, int max)
{
	return min + rand()%(max - min + 1);
}
