/*
 * And.cpp
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#include "And.h"

bool And::evaluate(vector<bool> in) {
	return in[0] & in[1];
}

byte And::evalLambdas() {
	return tmpValues->sharedMult;
}
