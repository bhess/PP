/*
 * CircuitComponent.h
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#ifndef CIRCUITCOMPONENT_H_
#define CIRCUITCOMPONENT_H_


#include <vector>
#include "CircuitElement.h"
#include "LastElement.h"

class CircuitComponent {
public:
	std::vector<CircuitElement*> inGates;
	std::vector<CircuitElement*> outGates;
	std::vector<CircuitElement*> allElements;

	void destruct() {
		destructed = 0;
		//allElements = vector<CircuitElement*>(cnt);
		for (unsigned int i = 0; i < inGates.size(); ++i) {
			inGates[i]->addSignal(false);
			destructRec(inGates[i]);
		}
	}

	int destructed;

private:
	void destructRec(CircuitElement* c) {
		if (c->allSignalsSet()) {
			//if (!dynamic_cast<LastElement*>(c)) {
				for (unsigned int i = 0; i < c->outElements.size(); ++i) {
					c->outElements[i]->addSignal(false);
					destructRec(c->outElements[i]);
				}
			//}
			destructed++;
			delete c;
		}
	}


};

#endif /* CIRCUITCOMPONENT_H_ */
