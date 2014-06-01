/*
 * Sorting.cpp
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#include "Sorting.h"
#include "PairwiseComparison.h"
#include "Permutation.h"
#include <cmath>
#include "../circuit/CircuitElement.h"

/**
 * Input format:  {{Timestamp}_t|{S,L}_e}_rep
 * Output format: {{S,L}_e}_rep (sorted by timestamp)
 */
CircuitComponent* Sorting::createComponent(int startWire, int t, int e, int rep) {
	CircuitComponent* c = new CircuitComponent();
	c->inGates = vector<CircuitElement*> (rep * (e + t));

	CircuitComponent* pairComp = PairwiseComparison().createComponent(
			startWire, t, rep);
	for (int i = 0; i < rep; ++i) {
		for (int j = 0; j < t; ++j) {
			c->inGates[i * (t + e) + j] = pairComp->inGates[i * t + j];
		}
	}

	int rank = (int) ceil(log((double)rep) / log((double)2));

	CircuitComponent* perm = Permutation().createComponent(0, e, rep);
	for (int i = 0; i < rep; ++i) {
		for (int j = 0; j < rank; ++j) {
			pairComp->outGates[i * rank + j]->setOutElementsCnt(1);
			pairComp->outGates[i * rank + j]->addOutElement(perm->inGates[i
					* (rank + e) + rank - j - 1]);
			//pairComp->outGates[i * rank + j]->registerAtOutElements();
		}
		for (int j = 0; j < e; ++j) {
			c->inGates[i * (t + e) + j + t] = perm->inGates[i * (rank + e) + j
					+ rank];
		}
	}
	c->outGates = perm->outGates;

	delete pairComp;
	delete perm;

	return c;
}
