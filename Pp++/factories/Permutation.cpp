/*
 * Permutation.cpp
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#include "Permutation.h"
#include <cmath>
//#include "../gates/nary/OrN.h"
#include "../gates/unary/Terminator.h"
#include "BBit1nDEMUX.h"
#include "OrNFactory.h"

CircuitComponent* Permutation::createComponent(int startWire, int b, int n) {
	int logn = (int) ceil(log((double)n) / log((double)2));
	CircuitComponent* res = new CircuitComponent();

	res->outGates = vector<CircuitElement*> (n * b);
	res->inGates = vector<CircuitElement*> (n * (b + logn));
	int inPos = 0;

	vector<CircuitComponent*> ornC = vector<CircuitComponent*>(n * b);
	for (int i = 0; i < n * b; ++i) {
		ornC[i] = OrNFactory().createComponent(startWire, n);
		//res->outGates[i] = new OrN(n);
		res->outGates[i] = ornC[i]->outGates[0];
	}

	for (int i = 0; i < n; ++i) {
		CircuitComponent* c = BBit1nDEMUX().createComponent(startWire, b, logn);
		for (int j = 0; j < b + logn; ++j) {
			res->inGates[inPos++] = c->inGates[j];
		}
		for (unsigned int j = 0; j < res->outGates.size(); ++j) {
			c->outGates[j]->setOutElementsCnt(1);
			//c->outGates[j]->addOutElement(res->outGates[j]);
			c->outGates[j]->addOutElement(ornC[j]->inGates[i / 2]);
			//c->outGates[j]->registerAtOutElements();
		}
		for (unsigned int j = res->outGates.size(); j < c->outGates.size(); ++j) {
			c->outGates[j]->setOutElementsCnt(1);
			c->outGates[j]->addOutElement(new Terminator());
			//c->outGates[j]->registerAtOutElements();
		}
	}

	for (int i = 0; i < (int)ornC.size(); ++i) {
		delete ornC[i];
	}

	return res;
}
