/*
 * SortAndRuleCheck.cpp
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#include "SortAndRuleCheck.h"
#include "Sorting.h"
#include "RuleSuccessCountCircuit.h"

#include <iostream>

/**
 * Input format:  {{Timestamp}_t|{S,L}_e}_rep
 * Output format: {RuleSuccess}_log(rep)
 */
CircuitComponent* SortAndRuleCheck::createComponent(int startWire, int t,
		int e, int rep) {
	CircuitComponent* sort = Sorting().createComponent(0, t, e, rep);
	CircuitComponent* ruleCheck = RuleSuccessCountCircuit().createComponent(0,
			e - 1, rep);

	//System.out.println(sort.outGates.length == ruleCheck.inGates.length);

	for (unsigned int i = 0; i < sort->outGates.size(); ++i) {
		sort->outGates[i]->setOutElementsCnt(1);
		sort->outGates[i]->addOutElement(ruleCheck->inGates[i]);
		//sort->outGates[i]->registerAtOutElements();
	}

	CircuitComponent* res = new CircuitComponent();
	res->inGates = sort->inGates;
	res->outGates = ruleCheck->outGates;

	delete sort;
	delete ruleCheck;

	return res;
}
