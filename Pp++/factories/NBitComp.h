/*
 * NBitComp.h
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#ifndef NBITCOMP_H_
#define NBITCOMP_H_
#include <vector>
#include "../circuit/CircuitComponent.h"

class NBitComp {
public:
	NBitComp() {
		globalInsPos = 0;
	}

	/**
	 * Input:  a_size|b_size
	 * Output: (a==b)|(a > b)
	 */
	CircuitComponent* createComponent(int startWire, int size);

private:
	vector<CircuitElement*> globalIns, globalOuts;

	int globSize, globalInsPos;

	CircuitComponent* buildRec(int size);
};

#endif /* NBITCOMP_H_ */
