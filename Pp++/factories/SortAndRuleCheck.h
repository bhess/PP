/*
 * SortAndRuleCheck.h
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#ifndef SORTANDRULECHECK_H_
#define SORTANDRULECHECK_H_

#include "../circuit/CircuitComponent.h"

class SortAndRuleCheck {
public:
	/**
	 * Input format:  {{Timestamp}_t|{S,L}_e}_rep
	 * Output format: {RuleSuccess}_log(rep)
	 */
	CircuitComponent* createComponent(int startWire, int t, int e, int rep);

};

#endif /* SORTANDRULECHECK_H_ */
