/*
 * And.h
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#ifndef AND_H_
#define AND_H_

#include "../../circuit/CircuitElement.h"

class And: public CircuitElement {
public:
	And(int OutElementCnt): CircuitElement(2, OutElementCnt) {}

	And(): CircuitElement(2) {}

	bool evaluate(vector<bool> in);

	byte evalLambdas();

	int getArity() {
		return 2;
	}

	bool isHomomorphic() { return false; }
};

#endif /* AND_H_ */
