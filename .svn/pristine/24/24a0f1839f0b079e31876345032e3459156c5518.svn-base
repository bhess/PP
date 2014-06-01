/*
 * Not.h
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#ifndef NOT_H_
#define NOT_H_

#include "../../circuit/CircuitElement.h"

class Not: public CircuitElement {
public:
	Not(int outElementsCnt): CircuitElement(1, outElementsCnt) {}

	bool evaluate(vector<bool> in) {
		return !in[0];
	}

	byte evalLambdas() {
		byte res = inElements[0]->tmpValues->sharedLambda & 0b1;
		return res | (!res << 1);
	}

	int getArity() {
		return 1;
	}

	bool isHomomorphic() { return true; }
};

#endif /* NOT_H_ */
