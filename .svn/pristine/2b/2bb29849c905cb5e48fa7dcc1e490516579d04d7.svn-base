/*
 * Or.h
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#ifndef OR_H_
#define OR_H_

#include "../../circuit/CircuitElement.h"

class Or: public CircuitElement {
public:
	Or(int OutElementCnt): CircuitElement(2, OutElementCnt) {}

	Or(): CircuitElement(2) {}

	bool evaluate(vector<bool> in);

	byte evalLambdas();

	int getArity() {
		return 2;
	}

	bool isHomomorphic() { return false; }
};

#endif /* OR_H_ */
