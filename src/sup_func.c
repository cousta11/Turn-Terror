#include "../include/sup_func.h"

int rand_to(int min, int max)
{
	return min + rand()%(max - min + 1);
}
