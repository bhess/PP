/*
 * OneBitAdderFactory.cpp
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#include "OneBitAdderFactory.h"
#include <cmath>
#include "../gates/unary/Dummy.h"
#include "../gates/binary/And.h"
#include "../gates/binary/Xor.h"

CircuitComponent* OneBitAdderFactory::createComponent(int startWire, int size) {

	component = new CircuitComponent();

	if (size == 1) {
		component->inGates = vector<CircuitElement*> (1);
		component->inGates[0] = new Dummy();
		component->outGates = component->inGates;
		return component;
	}

	elPerStep = vector<int> (size - 1);
	startIndex = vector<int> (size - 1);
	int inBits = 1;
	int outBits;
	// calculate the number of gates per step
	for (int i = 1; i < size; ++i, inBits = outBits) {
		// int blocks = inBits;
		outBits = (int) ceil(log((double)(i + 2)) / log((double)2));
		elPerStep[i - 1] = (inBits == outBits ? 2 * inBits - 1 : 2 * inBits);
		totalEl += elPerStep[i - 1];
	}

	component->allElements = vector<CircuitElement*> (totalEl + size);
	component->outGates = vector<CircuitElement*> ((int) ceil(log((double)(size + 1))
			/ log((double)2)));
	elements = component->allElements;
	int count = 0;

	// create the gates
	for (unsigned int c = 0; c < elPerStep.size(); count += elPerStep[c], ++c) {
		startIndex[c] = count;
	}

	for (unsigned int c = 0; c < elPerStep.size() - 1; ++c) {
		int el = elPerStep[c];
		bool odd = (el % 2 == 1);
		int blocks = (odd ? el - 1 : el - 2);
		for (int i = 0; i < blocks; i += 2) {
			elements[startIndex[c] + i] = new Xor(2);
			elements[startIndex[c] + i + 1] = (i + 3 < el ? new And(2)
					: new And(1));
		}

		elements[startIndex[c] + blocks] = (!(elPerStep[c + 1] % 2 == 1
				&& elPerStep[c] % 2 == 1) ? new Xor(2) : new Xor(1));

		//elements[startIndex[c] + blocks] = new Xor(2);
		if (!odd) {
			elements[startIndex[c] + blocks + 1] = new And(1);
		}

	}
	// special for the last step
	int c = elPerStep.size() - 1;
	int el = elPerStep[c];
	bool odd = (el % 2 == 1);
	int blocks = (odd ? el - 1 : el - 2);
	for (int i = 0; i < blocks; i += 2) {
		elements[startIndex[c] + i] = new Xor();
		elements[startIndex[c] + i + 1]
				= (i + 3 < el ? new And(2) : new And(1));// new And();
	}
	elements[startIndex[c] + blocks] = new Xor();
	if (!odd) {
		elements[startIndex[c] + blocks + 1] = new And();
	}
	//

	wire();

	// input-gates->->->
	vector<CircuitElement*> tmpelements = vector<CircuitElement*> (2 * (size
			- 1));
	for (unsigned int i = 0; i < startIndex.size(); ++i) {
		tmpelements[2 * i] = elements[startIndex[i]];
		tmpelements[2 * i + 1] = elements[startIndex[i] + 1];
	}

	component->inGates = vector<CircuitElement*> (size);
	component->inGates[0] = new Dummy();
	component->inGates[1] = new Dummy();
	component->inGates[0]->setOutElementsCnt(2);
	component->inGates[0]->addOutElement(tmpelements[0]);
	component->inGates[0]->addOutElement(tmpelements[1]);
	//component->inGates[0]->registerAtOutElements();
	component->allElements[totalEl] = component->inGates[0];
	component->inGates[1]->setOutElementsCnt(2);
	component->inGates[1]->addOutElement(tmpelements[0]);
	component->inGates[1]->addOutElement(tmpelements[1]);
	//component->inGates[1]->registerAtOutElements();
	component->allElements[totalEl + 1] = component->inGates[1];

	for (int i = 2; i < size; ++i) {
		component->inGates[i] = new Dummy();
		component->inGates[i]->setOutElementsCnt(2);
		component->inGates[i]->addOutElement(tmpelements[2 * (i - 1)]);
		component->inGates[i]->addOutElement(tmpelements[2 * (i - 1) + 1]);
		//component->inGates[i]->registerAtOutElements();
		component->allElements[totalEl + i] = component->inGates[i];
	}

	// checkConsistency();

	return component;
}

void OneBitAdderFactory::wire() {
	for (unsigned int c = 0; c < elPerStep.size() - 1; ++c) {
		int el = elPerStep[c];
		bool odd = (el % 2 == 1);
		int blocks = (odd ? el - 1 : el - 2);
		for (int i = 0; i < blocks; i += 2) {
			CircuitElement* toWire = elements[startIndex[c] + i];
			toWire->addOutElement(elements[startIndex[c + 1] + i]);
			toWire->addOutElement(elements[startIndex[c + 1] + i + 1]);
			//toWire->registerAtOutElements();

			toWire = elements[startIndex[c] + i + 1];
			toWire->addOutElement(elements[startIndex[c] + i + 2]);
			if (i + 3 < el) {
				toWire->addOutElement(elements[startIndex[c] + i + 3]);
			}
			//toWire->registerAtOutElements();
		}
		CircuitElement* toWire = elements[startIndex[c] + blocks];
		toWire->addOutElement(elements[startIndex[c + 1] + blocks]);
		if (!(elPerStep[c + 1] % 2 == 1 && elPerStep[c] % 2 == 1)) {
			toWire->addOutElement(elements[startIndex[c + 1] + blocks + 1]);
		}
		//toWire->registerAtOutElements();
		if (!odd) {
			toWire = elements[startIndex[c] + blocks + 1];
			toWire->addOutElement(elements[startIndex[c + 1] + blocks + 2]);
			//toWire->registerAtOutElements();
		}

	}

	int outGa = 0;

	int c = elPerStep.size() - 1;
	int el = elPerStep[c];
	bool odd = (el % 2 == 1);
	int blocks = (odd ? el - 1 : el - 2);
	for (int i = 0; i < blocks; i += 2) {
		CircuitElement* toWire = elements[startIndex[c] + i];
		component->outGates[outGa++] = toWire;

		toWire = elements[startIndex[c] + i + 1];
		toWire->addOutElement(elements[startIndex[c] + i + 2]);
		if (i + 3 < el) {
			toWire->addOutElement(elements[startIndex[c] + i + 3]);
		}
		//toWire->registerAtOutElements();
	}
	CircuitElement* toWire = elements[startIndex[c] + blocks];
	component->outGates[outGa++] = toWire;
	if (!odd) {
		toWire = elements[startIndex[c] + blocks + 1];
		component->outGates[outGa] = toWire;
	}

}
