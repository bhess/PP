/*
 * NBitComp.cpp
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#include "NBitComp.h"
#include "Input2mux21.h"
#include "../gates/unary/Dummy.h"
#include "../gates/unary/Not.h"
#include "../gates/binary/And.h"
#include "../gates/binary/Or.h"

/**
 * Input:  a_size|b_size
 * Output: (a==b)|(a > b)
 */

CircuitComponent* NBitComp::createComponent(int startWire, int size) {
	this->globalIns = vector<CircuitElement*>(2 * size);
	//this->globalOuts = new CircuitElement[2];
	this->globSize = size;
	CircuitComponent* cc = buildRec(size);
	cc->inGates = globalIns;
	cc->outGates = globalOuts;

	return cc;
}

CircuitComponent* NBitComp::buildRec(int size) {
	CircuitComponent* cc = new CircuitComponent();
	if (size == 1) {
		cc->inGates = vector<CircuitElement*>(2);
		cc->outGates = vector<CircuitElement*>(2);
		cc->allElements = vector<CircuitElement*>(4);

		cc->inGates[0] = new Dummy();
		cc->inGates[1] = new Dummy();

		cc->allElements[0] = new And(1);
		cc->allElements[1] = new And(1);
		cc->allElements[2] = new Not(1);
		cc->allElements[3] = new Not(2);

		cc->outGates[0] = new Or();
		cc->outGates[1] = new And();

		cc->inGates[0]->setOutElementsCnt(3);
		cc->inGates[0]->addOutElement(cc->allElements[0]);
		cc->inGates[0]->addOutElement(cc->allElements[2]);
		cc->inGates[0]->addOutElement(cc->outGates[1]);
		//cc->inGates[0]->registerAtOutElements();

		cc->inGates[1]->setOutElementsCnt(2);
		cc->inGates[1]->addOutElement(cc->allElements[0]);
		cc->inGates[1]->addOutElement(cc->allElements[3]);
		//cc->inGates[1]->registerAtOutElements();

		cc->allElements[0]->setOutElementsCnt(1);
		cc->allElements[0]->addOutElement(cc->outGates[0]);
		//cc->allElements[0]->registerAtOutElements();

		cc->allElements[1]->setOutElementsCnt(1);
		cc->allElements[1]->addOutElement(cc->outGates[0]);
		//cc->allElements[1]->registerAtOutElements();

		cc->allElements[2]->setOutElementsCnt(1);
		cc->allElements[2]->addOutElement(cc->allElements[1]);
		//cc->allElements[2]->registerAtOutElements();

		cc->allElements[3]->setOutElementsCnt(2);
		cc->allElements[3]->addOutElement(cc->allElements[1]);
		cc->allElements[3]->addOutElement(cc->outGates[1]);
		//cc->allElements[3]->registerAtOutElements();

		globalIns[globalInsPos] = cc->inGates[0];
		globalIns[globalInsPos + globSize] = cc->inGates[1];
		++globalInsPos;
		if (size == globSize) {
			globalOuts = cc->outGates;
		}
	} else {
		CircuitComponent* cmp1 = buildRec(size / 2);
		CircuitComponent* cmp2 = buildRec(size / 2);
		CircuitComponent* mux = Input2mux21().createComponent(0, size);

		CircuitElement* nott = new Not(1);
		cmp1->outGates[0]->setOutElementsCnt(2);
		cmp1->outGates[0]->addOutElement(nott);
		cmp1->outGates[0]->addOutElement(mux->inGates[1]);
		//cmp1->outGates[0]->registerAtOutElements();

		nott->addOutElement(mux->inGates[0]);
		//nott->registerAtOutElements();

		cmp1->outGates[1]->setOutElementsCnt(1);
		cmp1->outGates[1]->addOutElement(mux->inGates[2]);
		//cmp1->outGates[1]->registerAtOutElements();

		cmp2->outGates[0]->setOutElementsCnt(1);
		cmp2->outGates[0]->addOutElement(mux->inGates[3]);
		//cmp2->outGates[0]->registerAtOutElements();

		cmp2->outGates[1]->setOutElementsCnt(1);
		cmp2->outGates[1]->addOutElement(mux->inGates[4]);
		//cmp2->outGates[1]->registerAtOutElements();

		cc->inGates = vector<CircuitElement*>(2 * size);
		for (int i = 0; i < size; ++i) {
			cc->inGates[i] = cmp1->inGates[i];
			cc->inGates[i + size] = cmp2->inGates[i];
		}
		cc->outGates = mux->outGates;
		if (size == globSize) {
			globalOuts = mux->outGates;
		}

		delete cmp1;
		delete cmp2;
		delete mux;
	}
	return cc;
}
