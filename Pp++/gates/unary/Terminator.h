/*
 * Terminator.h
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#ifndef TERMINATOR_H_
#define TERMINATOR_H_

#include "../../circuit/LastElement.h"

class Terminator: public LastElement {
public:
	Terminator(): LastElement(1) {}

	bool evaluate(vector<bool> in) {
		return in[0];
	}

	byte evalLambdas() { return 0x00; }

	int getArity() {
		return 1;
	}

	bool isHomomorphic() { return true; }

};

#endif /* TERMINATOR_H_ */
