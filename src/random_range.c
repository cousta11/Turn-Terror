#include <stdlib.h>

#include "random_range.h"

int random_range(int min, int max)
{
	return min + rand()%(max - min + 1);
}
