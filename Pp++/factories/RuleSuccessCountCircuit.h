/*
 * RuleSuccessCountCircuit.h
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#ifndef RULESUCCESSCOUNTCIRCUIT_H_
#define RULESUCCESSCOUNTCIRCUIT_H_

#include "../circuit/CircuitComponent.h"

class RuleSuccessCountCircuit {
public:
	CircuitComponent* createComponent(int startWire, int bits, int events);
};

#endif /* RULESUCCESSCOUNTCIRCUIT_H_ */
