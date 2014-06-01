/*
 * Xor.h
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#ifndef XOR_H_
#define XOR_H_

#include "../../circuit/CircuitElement.h"

class Xor: public CircuitElement {
public:
	Xor(int OutElementCnt) : CircuitElement(2, OutElementCnt) {}

	Xor() : CircuitElement(2) {}

	bool evaluate(vector<bool> in);

	byte evalLambdas();

	int getArity() {
		return 2;
	}

	bool isHomomorphic() { return true; }
};

#endif /* XOR_H_ */
