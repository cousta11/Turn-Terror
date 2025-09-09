#include <stdlib.h>

#include "random_range.h"

int random_range(const int min, const int max)
{
	return min + rand()%(max - min + 1);
}
