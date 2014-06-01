/*
 * ResultElement.h
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#ifndef RESULTELEMENT_H_
#define RESULTELEMENT_H_

//#include "../../circuit/CircuitElement.h"
#include "../../circuit/LastElement.h"

class ResultElement: public LastElement {
public:
	ResultElement(vector<bool> *resultArray, int positionInArray, bool lambdaRes): LastElement(1) {
		this->resultArray = resultArray;
		this->positionInArray = positionInArray;
		this->lambdaRes = lambdaRes;
	}

	ResultElement(vector<bool> *resultArray, int positionInArray): LastElement(1) {
		this->resultArray = resultArray;
		this->positionInArray = positionInArray;
		this->lambdaRes = false;
	}

	bool evaluate(vector<bool> in) {
		(*resultArray)[positionInArray] = in[0] != lambdaRes;
		return in[0];
	}

	byte evalLambdas() { return 0x00; }

	int getArity() {
		return 1;
	}

	bool isHomomorphic() { return true; }

	bool lambdaRes;

private:
	vector<bool> *resultArray;
	int positionInArray;
};

#endif /* RESULTELEMENT_H_ */
