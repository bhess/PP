/*
 * Dummy.h
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#ifndef DUMMY_H_
#define DUMMY_H_

#include "../../circuit/CircuitElement.h"

class Dummy: public CircuitElement {
public:
	Dummy(): CircuitElement(1) {}

	bool evaluate(vector<bool> in) {
		return in[0];
	}

	byte evalLambdas() { return 0x00; }

	int getArity() {
		return 1;
	}

	bool isHomomorphic() { return true; }
};

#endif /* DUMMY_H_ */
