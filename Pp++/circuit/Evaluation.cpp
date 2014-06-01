/*
 * Evaluation.cpp
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#include "Evaluation.h"
#include "../gates/unary/ResultElement.h"
#include "../gates/unary/FirstElement.h"

Evaluation::Evaluation(CircuitComponent* component) {
	this->component = component;
	this->results = new vector<bool>(component->outGates.size());
	for (unsigned int i = 0; i < component->outGates.size(); ++i) {
		component->outGates[i]->setOutElementsCnt(1);
		component->outGates[i]->addOutElement(new ResultElement(results, i));
	}
	for (unsigned int i = 0; i < component->inGates.size(); ++i) {
		FirstElement* fe = new FirstElement();
		fe->addOutElement(component->inGates[i]);
		component->inGates[i] = fe;
	}
}

vector<bool> Evaluation::evaluate(vector<bool> inputBits) {
	//cnt = 0;
	vector<CircuitElement*> inE = component->inGates;
	for (unsigned int i = 0; i < inputBits.size(); ++i) {
		inE[i]->addSignal(inputBits[i]);
		evaluate(inE[i]);
	}
	return *results;
}

vector<bool> Evaluation::evaluate(vector<GarbledOutput> inputBits) {
	//cnt = 0;
	applyGarbledInput(&inputBits);
	vector<CircuitElement*> inE = component->inGates;
	for (unsigned int i = 0; i < inputBits.size(); ++i) {
		inE[i]->addSignal(inputBits[i]);
		evaluatePrivate(inE[i]);
	}
	return *results;
}

void Evaluation::applyGarbledInput(vector<GarbledOutput>* input) {
	for (unsigned int i = 0; i < input->size(); ++i) {
		garbledEvaluation->baseStep(&((*input)[i]), component->inGates[i]);
	}
}

void Evaluation::evaluate() {
	vector<CircuitElement*> inE = component->inGates;
	for (unsigned int i = 0; i < inE.size(); ++i) {
		inE[i]->addSignal(false);
		evaluate(inE[i]);
	}
	return;
}

void Evaluation::evaluate(CircuitElement* c) {
	if (c->allSignalsSet()) {
		bool signal = c->evaluate();
		c->resetSignals();
		//if (dynamic_cast<ResultElement*>(c)) return;
		for (unsigned int i = 0; i < c->outElements.size(); ++i) {
			c->outElements[i]->addSignal(signal);
			evaluate(c->outElements[i]);
		}
		visitor->executeAction(c);
		//cnt++;
	}
}

void Evaluation::evaluatePrivate(CircuitElement* c) {
	if (c->allSignalsSet()) {
		GarbledOutput signal = garbledEvaluation->evaluate(c);
		c->resetSignals();
		//if (dynamic_cast<ResultElement*>(c)) return;
		for (unsigned int i = 0; i < c->outElements.size(); ++i) {
			c->outElements[i]->addSignal(signal);
			evaluatePrivate(c->outElements[i]);
		}
		visitor->executeAction(c);
		//cnt++;
	}
}
