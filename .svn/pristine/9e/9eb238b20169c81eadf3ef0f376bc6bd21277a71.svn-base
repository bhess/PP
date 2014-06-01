/*
 * FirstElement.h
 *
 *  Created on: Jul 20, 2009
 *      Author: bhess
 */

#ifndef FIRSTELEMENT_H_
#define FIRSTELEMENT_H_

class FirstElement: public CircuitElement {
public:
	FirstElement(): CircuitElement(1, 1) {}

	bool evaluate(vector<bool> in) {
		return in[0];
	}

	byte evalLambdas() { return 0x00; }

	int getArity() {
		return 1;
	}

	bool isFirst() { return true; }

	bool isHomomorphic() { return true; }
};

#endif /* FIRSTELEMENT_H_ */
