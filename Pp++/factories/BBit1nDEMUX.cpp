/*
 * BBit1nDEMUX.cpp
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#include "BBit1nDEMUX.h"
#include <cmath>
#include "../gates/unary/Dummy.h"
#include "../gates/unary/Not.h"
#include "../gates/binary/And.h"

/**
 * Input format:  rank_n|{S,E}_b
 * Output format: {{S,E}_b}_2^n
 * @param startWire
 * @param b
 * @param n
 * @return
 */
CircuitComponent* BBit1nDEMUX::createComponent(int startWire, int b, int n) {
	this->globalOut = vector<CircuitElement*>(b * (int)pow((double)2, (double)n));
	this->globalIn = vector<CircuitElement*>(n + b);
	this->globalN = n;
	for (int i = 0; i < n; ++i) {
		this->globalIn[i] = new Dummy();
		this->globalIn[i]->setOutElementsCnt((int)pow((double)2, (double)i) * (b+1));
	}
	CircuitComponent* cc = buildRec(b, n);

	/*
	for (int i = 0; i < n; ++i) {
		this->globalIn[i]->registerAtOutElements();
	}
	*/

	cc->outGates = globalOut;
	cc->inGates = globalIn;
	return cc;
}

CircuitComponent* BBit1nDEMUX::buildRec(int b, int n) {
	if (n == 1) {
		CircuitComponent* cc = get12demux(b, n);
		for (unsigned int i = 0; i < cc->outGates.size(); ++i) {
			globalOut[globalOutPos++] = cc->outGates[i];
		}
		if (globalN == 1) {
			globalIn = cc->inGates;
		}
		return cc;
	} else {
		CircuitComponent* upper = get12demux(b, n);
		CircuitComponent* lowerLeft = buildRec(b, n - 1);
		CircuitComponent* lowerRight = buildRec(b, n - 1);
		for (int i = 0; i < b; ++i) {
			upper->outGates[i]->setOutElementsCnt(1);
			upper->outGates[i]->addOutElement(lowerLeft->inGates[i + 1]);
			//upper->outGates[i]->registerAtOutElements();

			upper->outGates[i + b]->setOutElementsCnt(1);
			upper->outGates[i + b]->addOutElement(lowerRight->inGates[i + 1]);
			//upper->outGates[i + b]->registerAtOutElements();
		}
		if (n == globalN) {
			for (int i = 0; i < b; ++i) {
				globalIn[i + n] = upper->inGates[i + 1];
			}
		}

		delete lowerLeft;
		delete lowerRight;

		return upper;

	}
}

CircuitComponent* BBit1nDEMUX::get12demux(int b, int level) {
	CircuitComponent* cc = new CircuitComponent();

	cc->inGates = vector<CircuitElement*> (b + 1);
	cc->outGates = vector<CircuitElement*> (2 * b);
	cc->allElements = vector<CircuitElement*> (1);

	for (unsigned int i = 0; i < cc->outGates.size(); ++i) {
		cc->outGates[i] = new And();
	}

	cc->allElements[0] = new Not(b);
	for (int i = 0; i < b; ++i) {
		cc->allElements[0]->addOutElement(cc->outGates[i]);
	}
	//cc->allElements[0]->registerAtOutElements();

	cc->inGates[0] = globalIn[globalN - level];
	//cc->inGates[0]->setOutElementsCnt(b + 1);
	cc->inGates[0]->addOutElement(cc->allElements[0]);
	for (int i = b; i < 2 * b; ++i) {
		cc->inGates[0]->addOutElement(cc->outGates[i]);
	}
	//cc->inGates[0]->registerAtOutElements();

	for (unsigned int i = 1; i < cc->inGates.size(); ++i) {
		cc->inGates[i] = new Dummy();
		cc->inGates[i]->setOutElementsCnt(2);
		cc->inGates[i]->addOutElement(cc->outGates[i - 1]);
		cc->inGates[i]->addOutElement(cc->outGates[b + i - 1]);
		//cc->inGates[i]->registerAtOutElements();
	}
	return cc;
}
