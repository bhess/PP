/*
 * RuleCheckArrayCircuit.cpp
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#include "RuleCheckArrayCircuit.h"
#include "../circuit/CircuitElement.h"
#include "../gates/unary/Dummy.h"
#include "RuleCheckCircuit.h"

/**
	 * Creates an array of rulecheck circuits (event times)
	 * @param startWire
	 * @param bits
	 * @param events
	 * @return
	 */
CircuitComponent* RuleCheckArrayCircuit::createComponent(int startWire, int bits, int events) {
		CircuitComponent* res = new CircuitComponent();
		int eventSize = bits + 1, totalBits = eventSize * events;

		vector<CircuitComponent*> ruleCheckComponents = vector<CircuitComponent*>(events - 1);
		res->outGates = vector<CircuitElement*>(events - 1);
		for (int i = 0; i < events - 1; ++i) {
			ruleCheckComponents[i] = RuleCheckCircuit().createComponent(0, bits);
			res->outGates[i] = ruleCheckComponents[i]->outGates[0];
		}

		res->inGates = vector<CircuitElement*>(totalBits);

		for (int i = 0; i < eventSize; ++i) {
			res->inGates[i] = new Dummy();
			res->inGates[i]->setOutElementsCnt(1);
			res->inGates[i]->addOutElement(ruleCheckComponents[0]->inGates[i]);
			//res->inGates[i]->registerAtOutElements();
		}
		for (int i = 1; i < events - 1; ++i) {
			int pos = i*eventSize;
			for (int j = 0; j < eventSize; ++j) {
				res->inGates[pos + j] = new Dummy();
				res->inGates[pos + j]->setOutElementsCnt(2);
				res->inGates[pos + j]->addOutElement(ruleCheckComponents[i-1]->inGates[eventSize+j]);
				res->inGates[pos + j]->addOutElement(ruleCheckComponents[i]->inGates[j]);
				//res->inGates[pos + j]->registerAtOutElements();
			}
		}
		int pos = (events - 1) * eventSize;
		for (int i = 0; i < eventSize; ++i) {
			res->inGates[pos + i] = new Dummy();
			res->inGates[pos + i]->setOutElementsCnt(1);
			res->inGates[pos + i]->addOutElement(ruleCheckComponents[events - 2]->inGates[eventSize+i]);
			//res->inGates[pos + i]->registerAtOutElements();
		}

		return res;
	}
