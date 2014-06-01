/*
 * PairwiseComparison.cpp
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#include "PairwiseComparison.h"
#include "../circuit/CircuitElement.h"
#include <cmath>
#include <vector>
#include "../gates/unary/Dummy.h"
#include "../gates/unary/Not.h"
#include "../gates/unary/Terminator.h"
#include "NBitComp.h"
#include "OneBitAdderFactory.h"

/**
 * Input format:  {timestamp_b}_n
 * Output format: {rank_logn}_n
 * @param startWire
 * @param b
 * @param n
 * @return
 */
CircuitComponent* PairwiseComparison::createComponent(int startWire, int b,
		int n) {
	CircuitComponent* cc = new CircuitComponent();

	int logn = (int) ceil(log((double)n) / log((double)2));

	cc->inGates = vector<CircuitElement*> (b * n);
	for (int i = 0; i < b * n; ++i) {
		cc->inGates[i] = new Dummy();
		cc->inGates[i]->setOutElementsCnt(n - 1);
	}

	vector<vector<CircuitElement*> > comps(n, vector<CircuitElement*> (n - 1));

	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			CircuitComponent* comp = NBitComp().createComponent(0, b);
			comp->outGates[0]->setOutElementsCnt(1);
			comp->outGates[0]->addOutElement(new Terminator());
			//comp->outGates[0]->registerAtOutElements();

			comps[i][j - 1] = comp->outGates[1];
			comps[j][i] = comp->outGates[1];
			comp->outGates[1]->setOutElementsCnt(2);
			int pos = 0;
			for (int k = i * b; k < (i + 1) * b; ++k) {
				cc->inGates[k]->addOutElement(comp->inGates[pos++]);
			}
			for (int k = j * b; k < (j + 1) * b; ++k) {
				cc->inGates[k]->addOutElement(comp->inGates[pos++]);
			}

			delete comp;
		}
	}

	cc->outGates = vector<CircuitElement*> (n * logn);
	int outGatePos = 0;
	for (int i = 0; i < n; ++i) {
		CircuitComponent* rank = OneBitAdderFactory().createComponent(0, n - 1);
		for (int j = 0; j < n - 1; ++j) {
			if (i > j) {
				CircuitElement* nott = new Not(1);
				comps[i][j]->addOutElement(nott);
				nott->addOutElement(rank->inGates[j]);
				//nott->registerAtOutElements();
			} else {
				comps[i][j]->addOutElement(rank->inGates[j]);
			}
		}
		for (int j = 0; j < logn; ++j) {
			cc->outGates[outGatePos++] = rank->outGates[j];
		}

		delete rank;
	}

	/*
	for (int i = 0; i < b * n; ++i) {
		cc->inGates[i]->registerAtOutElements();
	}
	*/

	return cc;
}
