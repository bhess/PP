/*
 * OneBitAdderFactory.h
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#ifndef ONEBITADDERFACTORY_H_
#define ONEBITADDERFACTORY_H_

#include "../circuit/CircuitComponent.h"
#include "../circuit/CircuitElement.h"

class OneBitAdderFactory {
public:

	OneBitAdderFactory() {
		totalEl = 0;
	}

	CircuitComponent* createComponent(int startWire, int size);

private:

	void wire();

	CircuitComponent* component;

	vector<CircuitElement*> elements;

	vector<int> elPerStep, startIndex;

	int totalEl;

};

#endif /* ONEBITADDERFACTORY_H_ */
