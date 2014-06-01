/*
 * RuleSuccessCountCircuit.cpp
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#include "RuleSuccessCountCircuit.h"
#include "RuleCheckArrayCircuit.h"
#include "OneBitAdderFactory.h"

CircuitComponent* RuleSuccessCountCircuit::createComponent(int startWire,
		int bits, int events) {
	CircuitComponent* rcarray = RuleCheckArrayCircuit().createComponent(
			startWire, bits, events);
	CircuitComponent* oba = OneBitAdderFactory().createComponent(startWire,
			rcarray->outGates.size());
	for (unsigned int i = 0; i < rcarray->outGates.size(); ++i) {
		rcarray->outGates[i]->setOutElementsCnt(1);
		rcarray->outGates[i]->addOutElement(oba->inGates[i]);
		//rcarray->outGates[i]->registerAtOutElements();
	}
	rcarray->outGates = oba->outGates;

	delete oba;

	return rcarray;
}
