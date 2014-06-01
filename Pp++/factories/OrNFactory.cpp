/*
 * OrNFactory.cpp
 *
 *  Created on: Jul 10, 2009
 *      Author: bhess
 */

#include "OrNFactory.h"
#include "../gates/binary/Or.h"
#include "../gates/unary/Dummy.h"
#include <cmath>
#include <queue>

using namespace std;

CircuitComponent* OrNFactory::createComponent(int startWire, int arity) {
	CircuitComponent* comp = new CircuitComponent();
	comp->inGates = vector<CircuitElement*>(arity / 2 + (arity % 2));
	queue<CircuitElement*> outQueue;
	for (int i = 0; i < arity / 2; ++i) {
		comp->inGates[i] = new Or();
		outQueue.push(comp->inGates[i]);
	}
	if (arity % 2) {
		comp->inGates[comp->inGates.size() - 1] = new Dummy();
		//comp->inGates[comp->inGates.size() - 1]->setOutElementsCnt(1);
		outQueue.push(comp->inGates[comp->inGates.size() - 1]);
	}

	while(outQueue.size() > 1) {
		CircuitElement* in1 = outQueue.front();
		outQueue.pop();
		CircuitElement* in2 = outQueue.front();
		outQueue.pop();
		CircuitElement* out = new Or();

		in1->setOutElementsCnt(1);
		in1->addOutElement(out);
		in2->setOutElementsCnt(1);
		in2->addOutElement(out);

		outQueue.push(out);
	}

	comp->outGates = vector<CircuitElement*>(1);
	comp->outGates[0] = outQueue.front();
	outQueue.pop();
	return comp;
}
