/*
 * message.h
 *
 *  Created on: Jul 6, 2009
 *      Author: bhess
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <cryptopp/cryptlib.h>

using namespace std;
/*
 * Message for Round 1
 */

struct ExpandedSeed {
	byte* seed;
	byte* F;
	byte* G;
	byte* H;
};

struct msgr1 {
	// bit shares and its indices
	byte* b;
	int bLength;

	// seeds for each wire
	byte** s;
	byte* multShares;
};

/*
 * Message for Round 2
 */
struct msgr2 {
	ExpandedSeed* expSeed;
	//ExpandedSeed* expSeed2;
};

/*
 * Message for Round 3
 */
struct msgr3 {
	byte* lambdaRes;

	byte** f;
	//byte*** gateLabels;
	struct GateLabels* gateLabels;
	byte** garbledInput;
};



#endif /* MSGR1_H_ */
