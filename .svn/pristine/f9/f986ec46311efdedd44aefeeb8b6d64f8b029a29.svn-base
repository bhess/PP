/*
 * CircuitElement.cpp
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#include "CircuitElement.h"
#include "LastElement.h"
#include "../gates/unary/ResultElement.h"
#include "../gates/unary/Terminator.h"

#include <iostream>

void CircuitElement::setOutElementsCnt(int outElementsCnt) {
	outElements = vector<CircuitElement*> (outElementsCnt);
}

/**
 * reset all input-signals if the circuit is evaluated
 */
void CircuitElement::resetSignals() {
	signalsSet = 0;
	/*
#if PRIVATE == 1
	for (unsigned int i = 0; i < inSuperSeeds.size(); ++i) {
		delete [] inSuperSeeds[i];
	}
#endif
	*/
}

/*
CircuitElement::~CircuitElement() {


}
*/

/**
 * Adds an input wire and the associated element.
 * @param wire
 * @param c
 */
void CircuitElement::addInWire(int wire, CircuitElement* c) {
	inWires[inWirePos] = wire;
	inElements[inWirePos++] = c;
}

/*
void CircuitElement::registerAtOutElements() {
	for (unsigned int i = 0; i < outElements.size(); ++i) {
		outElements[i]->addInWire(outWire, this);
	}
}
*/

/**
 * Specify the output-wire
 * @param wire
 */
void CircuitElement::addOutWire(int wire) {
	outWire = wire;
}

/**
 * Adds an element attached to the out-wire
 * @param e
 */
void CircuitElement::addOutElement(CircuitElement* e) {
	outElements[outWirePos] = e;
	outElements[outWirePos++]->addInWire(outWire, this);
}

/**
 * Adds a signal to the wire in the array with the given signal
 * @param index
 * @param signal
 */
void CircuitElement::addSignal(bool signal) {
	//assert (signalsSet >= 0);
	inSignals[signalsSet++] = signal;
	//signalsSet++;
}

void CircuitElement::addSignal(GarbledOutput signal) {
	inSuperSeeds[signalsSet] = signal.seed;
	addSignal(signal.value);
}

/**
 * Are all signals set?
 * @return
 */
bool CircuitElement::allSignalsSet() {
	return (unsigned int) signalsSet == inSignals.size();
}

/**
 * Evaluates the associated gate with the given inputs
 * @return
 */
bool CircuitElement::evaluate() {
	//signalsSet = 0;
	return evaluate(inSignals);
}

void CircuitElement::init(int inWireCnt) {
	inWires = vector<int> (inWireCnt);
	inElements = vector<CircuitElement*> (inWireCnt);
	inSignals = vector<bool> (inWireCnt);
	inSuperSeeds = vector<byte*> (inWireCnt);
	signalsSet = 0;
	inWirePos = 0;
	outWirePos = 0;
	//tmpValues = new struct TemporaryValues;
}
