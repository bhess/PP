/*
 * Input2mux21.h
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#ifndef INPUT2MUX21_H_
#define INPUT2MUX21_H_

#include "../circuit/CircuitComponent.h"

#define INWIRES 5
#define OUTWIRES 2
#define MIDDLEWIRES 1

class Input2mux21 {
public:

	/**
	 * Input: s|a11|a12|b11|b12
	 * Output: s=1 -> a11|a12, s=1 -> b11|b12
	 */
	CircuitComponent* createComponent(int startWire, int size);
};

#endif /* INPUT2MUX21_H_ */
