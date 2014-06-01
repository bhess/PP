/*
 * circuitvisitor.h
 *
 *  Created on: Jul 7, 2009
 *      Author: bhess
 */

#ifndef CIRCUITVISITOR_H_
#define CIRCUITVISITOR_H_

#include "CircuitElement.h"
#include "CircuitComponent.h"
#include "LastElement.h"
#include "../gates/unary/FirstElement.h"
#include "../gates/unary/Dummy.h"

class CircuitVisitor {
public:
	virtual void executeAction(CircuitElement* el) = 0;
};

class GarbledEvaluation: public CircuitVisitor {
public:
	GarbledEvaluation(int n, int k) {
		this->n = n;
		this->k = k;
		//this->garbledInput = garbledInput;
	}

	void baseStep(GarbledOutput* go, CircuitElement* el);

	void executeAction(CircuitElement* el) {}

	struct GarbledOutput evaluate(CircuitElement* el);

private:
	int n;
	int k;
	//byte** garbledInput;

	//byte* ev(byte* gateLabel, bool unary, int p, int q)
};

class CircuitDestructor: public CircuitVisitor {
public:
	void executeAction(CircuitElement* el) {
		delete el;
	}
};

/*
class SeedSetter: public CircuitVisitor {
public:
	SeedSetter(int k, int n, byte*** toReveal, byte** multShares) {
		this->k = k;
		this->n = n;
		this->toReveal = toReveal;
		this->multShares = multShares;
		cnt = 0;
	}

	void executeAction(CircuitElement* el);
private:
	int k, n;
	byte*** toReveal;
	byte** multShares;
	int cnt;
	int homoCnt;
};
*/
/*
class ExpandedSeedSharing: public CircuitVisitor {
public:
	ExpandedSeedSharing(int k, int n, ExpandedSeed** toShare, int me) {
		this->k = k;
		this->n = n;
		this->toShare = toShare;
		this->me = me;
		cnt = 0;
	}

	void executeAction(CircuitElement* el);
private:
	int k, n;
	ExpandedSeed** toShare;
	int cnt;
	int me;
};
*/
class RegisterVisitor: public CircuitVisitor {
public:
	RegisterVisitor(CircuitComponent* comp, int dummiesCnt) {
		this->comp = comp;
		cnt = 0;
		this->dummiesCnt = 0;
		this->notHomomorphicCnt = 0;
		dummies = vector<Dummy*>(dummiesCnt);
	}

	void executeAction(CircuitElement* el) {
		//el->tmpValues = new TemporaryValues();
		if (!dynamic_cast<Dummy*>(el)) {
			comp->allElements[cnt++] = el;
		} else {
			dummies[dummiesCnt++] = (Dummy*)el;
			// eliminate the dummies...
		}
	}

	vector<Dummy*> dummies;
	CircuitComponent* comp;
	int cnt;
	int dummiesCnt;
	int notHomomorphicCnt;
};

class CounterVisitor: public CircuitVisitor {
public:
	CounterVisitor() {
		reset();
	}

	void reset() {
		cnt = 0;
		notHomomorphicCnt = 0;
		dummies = 0;
	}

	void executeAction(CircuitElement* el) {
		if (!dynamic_cast<Dummy*>(el)) {
			++cnt;
			if (!el->isHomomorphic()) {
				++notHomomorphicCnt;
			}
		} else {
			++dummies;
		}
	}

	int cnt;
	int notHomomorphicCnt;
	int dummies;
};

/*
class RevealRound3: public CircuitVisitor {
public:
	RevealRound3(int k, int n, byte** revealedF, byte*** revealedGateLabels, int me) {
		this->k = k;
		this->n = n;
		this->revealedF = revealedF;
		this->revealedGateLabels = revealedGateLabels;
		this->me = me;
		cnt = 0;
	}

	void executeAction(CircuitElement* el);

private:
	int k;
	int n;
	byte** revealedF;
	byte*** revealedGateLabels;
	int cnt;
	int me;
};
*/

#endif /* CIRCUITVISITOR_H_ */
