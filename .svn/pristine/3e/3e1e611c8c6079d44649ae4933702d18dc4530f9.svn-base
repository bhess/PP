/*
 * BBit1nDEMUX.h
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#ifndef BBIT1NDEMUX_H_
#define BBIT1NDEMUX_H_

#include <vector>
#include "../circuit/CircuitComponent.h"
#include "../circuit/CircuitElement.h"

class BBit1nDEMUX {
public:
	BBit1nDEMUX() {
		globalOutPos = 0;
	}

	/**
	 * Input format:  rank_n|{S,E}_b
	 * Output format: {{S,E}_b}_2^n
	 * @param startWire
	 * @param b
	 * @param n
	 * @return
	 */
	CircuitComponent* createComponent(int startWire, int b, int n);

private:
	std::vector<CircuitElement*> globalOut, globalIn;
	int globalOutPos, globalN;

	CircuitComponent* buildRec(int b, int n);

	CircuitComponent* get12demux(int b, int level);
};

#endif /* BBIT1NDEMUX_H_ */
