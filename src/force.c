#include <stdlib.h>
#include <math.h>
#include "force.h"

double force_calculate_magnitude(double x1, double y1, double x2, double y2) {
	   return sqrt(pow(x1 - x2,2.0) + pow(y1 - y2,2.0));
}
