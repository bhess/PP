/*
 * Sorting.h
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#ifndef SORTING_H_
#define SORTING_H_

#include "../circuit/CircuitComponent.h"

class Sorting {
public:
	CircuitComponent* createComponent(int startWire, int t, int e, int rep);
};

#endif /* SORTING_H_ */
