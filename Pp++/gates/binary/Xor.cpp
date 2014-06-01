/*
 * Xor.cpp
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#include "Xor.h"

bool Xor::evaluate(vector<bool> in) {
	return in[0] != in[1];
}

byte Xor::evalLambdas() {
	byte la = inElements[0]->tmpValues->sharedLambda & 0b1;
	byte lb = inElements[0]->tmpValues->sharedLambda & 0b1;

	byte xors = 0x00;
	xors |= la ^ lb;
	xors |= (la ^ !lb) << 1;
	xors |= (!la ^ lb) << 2;
	xors |= (!la ^ !lb) << 3;
	return xors;
}
