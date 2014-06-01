/*
 * RuleCheckCircuit.cpp
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#include "RuleCheckCircuit.h"
#include "NBitComp.h"
#include "../gates/unary/Dummy.h"
#include "../gates/unary/Not.h"
#include "../gates/unary/Terminator.h"
#include "../gates/binary/And.h"
#include "../gates/binary/Or.h"

/**
 * Input: S_i(1)|L_i(size)|S_i+1(1)|L_i+1(size)
 */
CircuitComponent* RuleCheckCircuit::createComponent(int startWire, int size) {
	CircuitComponent* res = new CircuitComponent();
	CircuitComponent* comp = NBitComp().createComponent(startWire, size);
	comp->outGates[1]->setOutElementsCnt(1);
	comp->outGates[1]->addOutElement(new Terminator());
	//comp->outGates[1]->registerAtOutElements();
	comp->outGates[0]->setOutElementsCnt(2);

	res->allElements = vector<CircuitElement*> (7 + (2 * size) + 2);
	res->inGates = vector<CircuitElement*> ((2 * size) + 2);
	res->outGates = vector<CircuitElement*> (1);
	res->allElements[0] = new Not(1);
	res->allElements[1] = comp->outGates[0];
	//res->allElements[1] = new EqualityTwo(2 * size, 2);
	res->allElements[2] = new Not(1);
	//res->allElements[3] = new AndTri(1);
	//res->allElements[4] = new AndTri(1);
	res->allElements[3] = new And(1);
	res->allElements[4] = new And(1);
	res->allElements[5] = new Not(1);
	res->allElements[6] = new Or();

	CircuitElement* alland3 = new And(1);
	alland3->addOutElement(res->allElements[3]);
	CircuitElement* alland4 = new And(1);
	alland4->addOutElement(res->allElements[4]);

	res->outGates[0] = res->allElements[6];

	//res->allElements[0]->addOutElement(res->allElements[4]);
	res->allElements[0]->addOutElement(alland4);
	//res->allElements[1]->addOutElement(res->allElements[3]);.
	res->allElements[1]->addOutElement(alland3);
	res->allElements[1]->addOutElement(res->allElements[5]);
	//res->allElements[2]->addOutElement(res->allElements[3]);
	res->allElements[2]->addOutElement(alland3);
	res->allElements[3]->addOutElement(res->allElements[6]);
	res->allElements[4]->addOutElement(res->allElements[6]);
	//res->allElements[5]->addOutElement(res->allElements[4]);
	res->allElements[5]->addOutElement(alland4);

	/*
	for (int i = 0; i < 6; ++i) {
		res->allElements[i]->registerAtOutElements();
	}
	*/

	// adding input dummies
	int i = 7;
	res->allElements[i] = new Dummy();
	res->allElements[i]->setOutElementsCnt(2);
	res->allElements[i]->addOutElement(res->allElements[0]);
	res->allElements[i]->addOutElement(res->allElements[3]);
	//res->allElements[i]->registerAtOutElements();
	++i;
	for (; i < 8 + size; ++i) {
		/*
		 res->allElements[i] = new Dummy();
		 res->allElements[i]->setOutElementsCnt(1);
		 res->allElements[i]->addOutElement(res->allElements[1]);
		 res->allElements[i]->registerAtOutElements();
		 */
		res->allElements[i] = comp->inGates[i - 8];
	}
	res->allElements[i] = new Dummy();
	res->allElements[i]->setOutElementsCnt(2);
	res->allElements[i]->addOutElement(res->allElements[2]);
	res->allElements[i]->addOutElement(res->allElements[4]);
	//res->allElements[i]->registerAtOutElements();
	++i;
	for (int z = 0; i < (int) res->allElements.size(); ++i, ++z) {
		/*
		 res->allElements[i] = new Dummy();
		 res->allElements[i]->setOutElementsCnt(1);
		 res->allElements[i]->addOutElement(res->allElements[1]);
		 res->allElements[i]->registerAtOutElements();
		 */
		res->allElements[i] = comp->inGates[z + size];
	}

	for (i = 7; i < (int) res->allElements.size(); ++i) {
		res->inGates[i - 7] = res->allElements[i];
	}

	delete comp;

	return res;
}
