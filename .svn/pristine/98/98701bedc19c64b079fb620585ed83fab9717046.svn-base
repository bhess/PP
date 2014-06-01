/*
 * player.cpp
 *
 *  Created on: Jul 7, 2009
 *      Author: bhess
 */

#include "player.h"
#include <iostream>
#include <assert.h>

using namespace std;

void Player::evaluateGarbledCircuit() {



	int inlength = 17 * 5;
	vector<GarbledOutput> invec = vector<GarbledOutput>(inlength);
	for (int i = 0; i < inlength; ++i) {
		GarbledOutput sad = getGO(garbledInput[i]);
		invec[i] = sad;
	}

	//eval = new Evaluation(circuit);
	eval->setGarbledEvaluator(n, k);
	CounterVisitor* cv = new CounterVisitor();
	eval->setVisitor(cv);
	vector<bool> sample = eval->evaluate(invec);
	cout << "[";
	for (unsigned int i = 0; i < sample.size(); ++i) {
		cout << (sample[i] ? "1" : "0") << ",";
	}
	cout << "]\n";
	cout << cv->cnt << " elements\n";
	//circuit->destruct();
	//cout << circuit->destructed << " destructed\n";
	delete circuit;
	delete eval;
	delete cv;
}

void Player::init(Player** otherPlayers) {
	this->otherPlayers = otherPlayers;

	CounterVisitor* cv = new CounterVisitor();
	eval->setVisitor(cv);
	eval->evaluate();
	gatesCount = cv->cnt;
	int dummiesCnt = cv->dummies;
	notHomomorphicGatesCount = cv->notHomomorphicCnt;
	delete cv;

	circuit->allElements = vector<CircuitElement*>(gatesCount);
	RegisterVisitor* rv = new RegisterVisitor(circuit, dummiesCnt);
	eval->setVisitor(rv);
	eval->evaluate();

	// eliminate the dummies...
	int dsize = rv->dummies.size();
	for (int ui = 0; ui < dsize; ++ui) {
		CircuitElement* el = rv->dummies[ui];
		CircuitElement* bef = el->inElements[0];
		int outsize = el->outElements.size();
		int oldsize = bef->outElements.size();
		bef->outElements.resize(oldsize + outsize - 1);
		for (int i = 0; i < outsize; ++i) {
			CircuitElement* next = el->outElements[i];
			for (int j = 0; j < (int)next->inElements.size(); ++j) {
				if (next->inElements[j] == el) {
					next->inElements[j] = bef;
				}
			}
			if (i == 0) {
				for (int j = 0; j < oldsize; ++j) {
					if (bef->outElements[j] == el) {
						bef->outElements[j] = next;
					}
				}
			} else {
				bef->outElements[i + oldsize - 1] = next;
			}

		}
		delete el;
	}

	delete rv;


	garbledInput = new GarbledInput[circuit->inGates.size()];

	for (int i = 0; i < gatesCount; ++i) {
		circuit->allElements[i]->tmpValues = new TemporaryValues;
	}
	/*
	for (int i = 0; i < n; ++i) {
		garbledInput[i].inSuperSeeds = new byte*[n];
	}
	*/

}

void Player::round1init() {

	r1.bw = getSharesID(myInput, n);

	byte*** toReveal = new byte**[n];
	byte** multGatesShares = new byte*[n];
	for (int i = 0; i < n; ++i) {
		toReveal[i] = new byte*[2 * gatesCount];
		multGatesShares[i] = new byte[notHomomorphicGatesCount];
	}

	for (int i = 0; i < (int)circuit->inGates.size(); ++i) {
		CircuitElement* el = circuit->inGates[i];
		//el->tmpValues = new TemporaryValues;

		el->tmpValues->sharedSeed1 = getRandomBlocks(n * k);
		el->tmpValues->sharedSeed2 = getRandomBlocks(n * k);
		byte* lambda = getRandomBlocks(1);
		el->tmpValues->sharedLambda = (lambda[0] & 0x00 ? 0x01 : 0x00);
	}

	int homoCnt = 0;
	for (int prtschg = 0; prtschg < gatesCount; ++prtschg) {
		// reveal the seeds to the players...
		CircuitElement* el = circuit->allElements[prtschg];

		el->tmpValues->sharedSeed1 = getRandomBlocks(n * k);
		el->tmpValues->sharedSeed2 = getRandomBlocks(n * k);
		byte* lambda = getRandomBlocks(1);
		el->tmpValues->sharedLambda = (lambda[0] & 0x00 ? 0xFF : 0x00);
		//delete [] lambda;
		for (int i = 0; i < n; ++i) {
			if (el->tmpValues->sharedLambda) {
				toReveal[i][2 * prtschg] = el->tmpValues->sharedSeed2 + i * k
						+ k;
				toReveal[i][2 * prtschg + 1] = el->tmpValues->sharedSeed1 + i
						* k;
			} else {
				toReveal[i][2 * prtschg] = el->tmpValues->sharedSeed1 + i * k;
				toReveal[i][2 * prtschg + 1] = el->tmpValues->sharedSeed2 + i
						* k + k;
			}
		}

		// reveal the shares of the multiplication
		if (!el->isHomomorphic()) {
			byte res = 0x0;
			byte l1 = el->inElements[0]->tmpValues->sharedLambda;
			byte l2 = el->inElements[1]->tmpValues->sharedLambda;
			res |= (l1 & l2 ? 0b1 : 0b0);
			res |= (l1 & !l2 ? 0b10 : 0b0);
			res |= (!l1 & l2 ? 0b100 : 0b0);
			res |= (!l1 & !l2 ? 0b1000 : 0b0);

			byte* shares = getSharesID(res, n);
			for (int i = 0; i < n; ++i) {
				multGatesShares[i][homoCnt] = shares[i];
			}
			//delete[] shares;
			++homoCnt;
		}
	}
	r1.revealedSeeds = toReveal;
	r1.multShares = multGatesShares;

	for (int i = 0; i < gatesCount; ++i) {
		CircuitElement* el = circuit->allElements[i];
		el->realF1 = new byte*[n];
		el->realF2 = new byte*[n];
		el->gateLabels.A = new byte[n*k];
		el->gateLabels.B = new byte[n*k];
		el->gateLabels.C = new byte[n*k];
		el->gateLabels.D = new byte[n*k];

		el->tmpValues->realSeed1 = new byte[k];
		el->tmpValues->realSeed2 = new byte[k];
		el->tmpValues->sharedMult = r1.multShares[me][i];
		for (int j = 0; j < k; ++j) {
			el->tmpValues->realSeed1[j] = 0x0;
			el->tmpValues->realSeed2[j] = 0x0;
		}
	}
}

void Player::round1snd() {
	int add = 0;

	for (int i = 0; i < n; ++i) {
		if (i != me) {
			struct msgr1 msg;
			msg.b = r1.bw[i - add];
			msg.bLength = myInput.size();
			msg.s = r1.revealedSeeds[i - add];
			msg.multShares = r1.multShares[i - add];
			otherPlayers[i]->round1rcv(msg, me);
		} else {
			add = 1;
		}
	}
}

void Player::round1rcv(struct msgr1 msg, int fromID) {
	// TODO: case with more bits per player
	garbledInput[fromID * msg.bLength].inBit = msg.b[0];

	for (int i = 0; i < gatesCount; ++i) {
		// TODO: check if not 2*i+lambda...
		CircuitElement* ce = circuit->allElements[i];
		bytewiseXor(msg.s[2*i], ce->tmpValues->realSeed1, k);
		bytewiseXor(msg.s[2*i + 1], ce->tmpValues->realSeed2, k);
		if (!ce->isHomomorphic()) {
			ce->tmpValues->sharedMult ^= msg.multShares[i];
		}
	}
	delete [] msg.s;
	return;
}

void Player::round1finalize() {
	for (int i = 0; i < gatesCount; ++i) {
		CircuitElement* el = circuit->allElements[i];

		ExpandedSeed es = expandSeed(k, n, el->tmpValues->realSeed1);
		el->realF1[me] = es.F;
		el->tmpValues->realG1 = es.G;
		el->tmpValues->realH1 = es.H;
		es = expandSeed(k, n, el->tmpValues->realSeed2);
		el->realF2[me] = es.F;
		el->tmpValues->realG2 = es.G;
		el->tmpValues->realH2 = es.H;
	}
}

void Player::round2init() {
	//expandedSeedsShare = shareExpandedSeeds();


	ExpandedSeed** toShare = new ExpandedSeed*[n];
	for (int i = 0; i < n; ++i) {
		toShare[i] = new ExpandedSeed[2 * gatesCount];
	}

	for (int cnt = 0; cnt < gatesCount; ++cnt) {
		CircuitElement* el = circuit->allElements[cnt];

		/*
		ExpandedSeed exs1 = expandSeed(k, n, el->tmpValues->realSeed1);
		el->realF1[me] = exs1.F;
		el->tmpValues->realG1 = exs1.G;
		el->tmpValues->realH1 = exs1.H;
		ExpandedSeed exs2 = expandSeed(k, n, el->tmpValues->realSeed2);
		el->realF2[me] = exs2.F;
		el->tmpValues->realG2 = exs2.G;
		el->tmpValues->realH2 = exs2.H;
		*/

		byte** fShare1 = getSharesID(vector<byte> (el->realF1[me],
				el->realF1[me] + k), n);
		byte** fShare2 = getSharesID(vector<byte> (el->realF2[me],
				el->realF2[me] + k), n);
		for (int i = 0; i < n; ++i) {
			if (!el->tmpValues->sharedLambda) {
				toShare[i][2 * cnt].F = fShare1[i];
				toShare[i][2 * cnt + 1].F = fShare2[i];
			} else {
				toShare[i][2 * cnt].F = fShare2[i];
				toShare[i][2 * cnt + 1].F = fShare1[i];
			}
		}
		//delete[] fShare1;
		//delete[] fShare2;

		byte** gShare1 = getSharesID(vector<byte> (el->tmpValues->realG1,
				el->tmpValues->realG1 + n * k), n);
		byte** gShare2 = getSharesID(vector<byte> (el->tmpValues->realG2,
				el->tmpValues->realG2 + n * k), n);
		for (int i = 0; i < n; ++i) {
			assert(gShare1[i] != NULL);
			assert(gShare2[i] != NULL);
			if (!el->tmpValues->sharedLambda) {
				toShare[i][2 * cnt].G = gShare1[i];
				toShare[i][2 * cnt + 1].G = gShare2[i];
			} else {
				toShare[i][2 * cnt].G = gShare2[i];
				toShare[i][2 * cnt + 1].G = gShare1[i];
			}
		}
		//delete[] gShare1;
		//delete[] gShare2;

		byte** hShare1 = getSharesID(vector<byte> (el->tmpValues->realH1,
				el->tmpValues->realH1 + n * k), n);
		byte** hShare2 = getSharesID(vector<byte> (el->tmpValues->realH2,
				el->tmpValues->realH2 + n * k), n);
		for (int i = 0; i < n; ++i) {
			if (!el->tmpValues->sharedLambda) {
				toShare[i][2 * cnt].H = hShare1[i];
				toShare[i][2 * cnt + 1].H = hShare2[i];
			} else {
				toShare[i][2 * cnt].H = hShare2[i];
				toShare[i][2 * cnt + 1].H = hShare1[i];
			}
		}
		//delete[] hShare1;
		//delete[] hShare2;
	}

	expandedSeedsShare = toShare;


	for (int i = 0; i < gatesCount; ++i) {
		CircuitElement* ce = circuit->allElements[i];
		ce->tmpValues->sharedG1 = new byte*[n];
		ce->tmpValues->sharedG2 = new byte*[n];
		ce->tmpValues->sharedH1 = new byte*[n];
		ce->tmpValues->sharedH2 = new byte*[n];
		ce->tmpValues->sharedG1[me] = expandedSeedsShare[me][2 * i].G;
		assert(expandedSeedsShare[me][2 * i].G != NULL);
		ce->tmpValues->sharedH1[me] = expandedSeedsShare[me][2 * i].H;
		ce->tmpValues->sharedG2[me] = expandedSeedsShare[me][2 * i + 1].G;
		ce->tmpValues->sharedH2[me] = expandedSeedsShare[me][2 * i + 1].H;
	}
}

void Player::round2snd() {
	int add = 0;
	for (int i = 0; i < n; ++i) {
		if (i != me) {
			struct msgr2 msg;
			msg.expSeed = expandedSeedsShare[i - add];
			otherPlayers[i]->round2rcv(msg, me);
		} else {
			add = 1;
		}
	}
}

void Player::round2rcv(struct msgr2 msg, int fromID) {
	for (int i = 0; i < gatesCount; ++i) {
		CircuitElement* ce = circuit->allElements[i];
		// TODO: maybe wrong...
		ce->tmpValues->sharedG1[fromID] = msg.expSeed[2 * i].G;
		//assert(ce->tmpValues->sharedG1[fromID] != NULL);
		ce->tmpValues->sharedH1[fromID] = msg.expSeed[2 * i].H;
		ce->tmpValues->sharedG2[fromID] = msg.expSeed[2 * i + 1].G;
		ce->tmpValues->sharedH2[fromID] = msg.expSeed[2 * i + 1].H;
	}
}

void Player::round2finalize() {
	/*
	for (int i = 0; i < 2 * gatesCount; ++i) {
		delete [] expandedSeedsShare[i];
	}
	*/
	// compute the gate labels
	//delete [] expandedSeedsShare;

	for (int i = 0; i < gatesCount; ++i) {
		CircuitElement* el = circuit->allElements[i];

		if (el->isFirst() || el->isLast()) {
			continue;
		}

		el->gateLabels.A = new byte[n*k];
		el->gateLabels.B = new byte[n*k];
		if (el->inElements.size() == 2) {
			el->gateLabels.C = new byte[n*k];
			el->gateLabels.D = new byte[n*k];
			CircuitElement* ina = el->inElements[0];
			CircuitElement* inb = el->inElements[1];
			for (int j = 0; j < n*k; ++j) {
				el->gateLabels.A[j] = 0x00;
				el->gateLabels.B[j] = 0x00;
				el->gateLabels.C[j] = 0x00;
				el->gateLabels.D[j] = 0x00;
			}
			for (int j = 0; j < n; ++j) {
				bytewiseXor(ina->tmpValues->sharedG1[j], el->gateLabels.A, n*k);
				bytewiseXor(inb->tmpValues->sharedG1[j], el->gateLabels.A, n*k);

				bytewiseXor(ina->tmpValues->sharedH1[j], el->gateLabels.B, n*k);
				bytewiseXor(inb->tmpValues->sharedG2[j], el->gateLabels.B, n*k);

				bytewiseXor(ina->tmpValues->sharedG2[j], el->gateLabels.C, n*k);
				bytewiseXor(inb->tmpValues->sharedH1[j], el->gateLabels.C, n*k);

				bytewiseXor(ina->tmpValues->sharedH2[j], el->gateLabels.D, n*k);
				bytewiseXor(inb->tmpValues->sharedH2[j], el->gateLabels.D, n*k);
			}

			byte lam = el->tmpValues->sharedLambda;
			lam |= lam << 1;
			lam |= lam << 2;
			lam ^= el->evalLambdas();
			bytewiseXor((lam & 0b1    ? el->tmpValues->sharedSeed2 : el->tmpValues->sharedSeed1), el->gateLabels.A, n*k);
			bytewiseXor((lam & 0b10   ? el->tmpValues->sharedSeed2 : el->tmpValues->sharedSeed1), el->gateLabels.B, n*k);
			bytewiseXor((lam & 0b100  ? el->tmpValues->sharedSeed2 : el->tmpValues->sharedSeed1), el->gateLabels.C, n*k);
			bytewiseXor((lam & 0b1000 ? el->tmpValues->sharedSeed2 : el->tmpValues->sharedSeed1), el->gateLabels.D, n*k);
		} else if (el->inElements.size() == 1) {
			CircuitElement* ina = el->inElements[0];
			for (int j = 0; j < n*k; ++j) {
				el->gateLabels.A[j] = 0x00;
				el->gateLabels.B[j] = 0x00;
			}
			for (int j = 0; j < n; ++j) {
				bytewiseXor(ina->tmpValues->sharedG1[j], el->gateLabels.A, n * k);

				bytewiseXor(ina->tmpValues->sharedG2[j], el->gateLabels.B, n * k);
			}
			byte lam = el->tmpValues->sharedLambda;
			lam |= lam << 1;
			lam ^= el->evalLambdas();
			bytewiseXor((lam & 0b1 ? el->tmpValues->sharedSeed2 : el->tmpValues->sharedSeed1), el->gateLabels.A, n * k);
			bytewiseXor((lam & 0b10 ? el->tmpValues->sharedSeed2 : el->tmpValues->sharedSeed1), el->gateLabels.B, n * k);
		}
	}
}

void Player::round3init() {

	r3.f = new byte*[2 * gatesCount];
	// TODO: n is here the number of events
	int inElCnt = circuit->inGates.size();
	r3.garbledInput = new byte*[inElCnt];
	r3.gateLabels = new GateLabels[gatesCount];

	// reveal the lambda-res...
	byte* res = new byte[circuit->outGates.size()];
	for (int i = 0; i < (int)circuit->outGates.size(); ++i) {
		//res[i] = circuit->outGates[i]->lambda;
		res[i] = circuit->outGates[i]->tmpValues->sharedLambda;
	}
	r3.lambdaRes = res;
	for (int i = 0; i < inElCnt; ++i) {
		//r3->f[i] = new byte*[gatesCount];
		CircuitElement* in = circuit->inGates[i];
		//r3.garbledInput[i] = new byte[n];
		r3.garbledInput[i] = (garbledInput[i].inBit
				!= in->tmpValues->sharedLambda ? in->tmpValues->sharedSeed2
				: in->tmpValues->sharedSeed1);
	}

	// reveal the f values and the gate labels to the players
	for (int cnt = 0; cnt < gatesCount; ++cnt) {
		CircuitElement* el = circuit->allElements[cnt];
		r3.f[2 * cnt + (el->tmpValues->sharedLambda ? 1 : 0)] = el->realF1[me];
		r3.f[2 * cnt + (el->tmpValues->sharedLambda ? 0 : 1)] = el->realF2[me];
		r3.gateLabels[cnt] = el->gateLabels;
	}


	// todo: garbled input
	for (int i = 0; i < inElCnt; ++i) {
		garbledInput[i].inSuperSeeds = r3.garbledInput[i];
		/*
		for (int j = 0; j < n; ++j) {
			garbledInput[i].inSuperSeeds[j] = r3.garbledInput[i] + j*k;
		}
		garbledInput[i].inSuperSeeds[me] = r3.garbledInput[me];
		*/
	}

	for (int i = 0; i < (int) circuit->outGates.size(); ++i) {
		circuit->outGates[i]->lambdaRes
				= circuit->outGates[i]->tmpValues->sharedLambda;
	}


}

void Player::round3snd() {
	int add = 0;
	for (int i = 0; i < n; ++i) {
		if (i != me) {
			struct msgr3 msg;
			msg.garbledInput = r3.garbledInput;//[i - add];
			msg.gateLabels = r3.gateLabels;//[i - add];
			msg.f = r3.f;
			msg.lambdaRes = r3.lambdaRes;
			otherPlayers[i]->round3rcv(msg, me);
		} else {
			add = 1;
		}
	}
}

void Player::round3rcv(struct msgr3 msg, int fromID) {
	for (int i = 0; i < n; ++i) {
		// TODO: not only one input...
		bytewiseXor(msg.garbledInput[i], garbledInput[i].inSuperSeeds, n*k);
		//garbledInput[i].inSuperSeeds[fromID] = msg.garbledInput;
	}

	for (int i = 0; i < gatesCount; ++i) {
		CircuitElement* ce = circuit->allElements[i];
		// TODO: maybe wrong...
		ce->realF1[fromID] = msg.f[2 * i];
		ce->realF2[fromID] = msg.f[2 * i + 1];
		bytewiseXor(msg.gateLabels[i].A, ce->gateLabels.A, n*k);
		bytewiseXor(msg.gateLabels[i].B, ce->gateLabels.B, n*k);
		bytewiseXor(msg.gateLabels[i].C, ce->gateLabels.C, n*k);
		bytewiseXor(msg.gateLabels[i].D, ce->gateLabels.D, n*k);
		//ce->gateLabels[fromID] = msg.gateLabels[i];

		//msg.
	}

	for (int i = 0; i < (int)circuit->outGates.size(); ++i) {
		circuit->outGates[i]->lambdaRes ^= msg.lambdaRes[i];
	}
}

void Player::round3finalize() {

}
