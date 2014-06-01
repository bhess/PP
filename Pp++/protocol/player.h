/*
 * player.h
 *
 *  Created on: Jul 2, 2009
 *      Author: root
 */

#ifndef PLAYER_H_
#define PLAYER_H_

//
#include "../factories/SortAndRuleCheck.h"
#include "../crypto/cryptoroutines.h"
#include "../circuit/Evaluation.h"

using namespace std;

struct r1ds {
	byte** bw; // shared input bits for each player: n times i
	byte*** revealedSeeds; // revealed seeds for each player and each gate: n times 2W times k
	byte** multShares; // multiplication shares for each plyer and each non-homomorphic gate: n times W
};

struct r3ds {
	byte** garbledInput;
	GateLabels* gateLabels;
	byte** f;
	byte* lambdaRes;
};

struct GarbledInput {
	byte inBit;
	byte* inSuperSeeds;
};

class Player {
public:
	Player(int timeLength, int eventLength, int events, int n, int you, int k) {
		this->n = n;
		this->me = you;
		this->k = k;
		this->eventLength = eventLength;
		circuit = SortAndRuleCheck().createComponent(0, timeLength, eventLength, events);
		eval = new Evaluation(circuit);
	}

	vector<bool> test() {
		bool sampler[] = {	0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,
								0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,1,0,
			};
		vector<bool> sample = vector<bool> (sampler, sampler + sizeof(sampler)
			 / sizeof(bool));

		CounterVisitor* cv = new CounterVisitor();
		eval->setVisitor(cv);
		return eval->evaluate(sample);
	}

	void setInput(vector<bool> in) {
		myInput = vector<byte>(in.size());
		for (int i = 0; i < (int)in.size(); ++i) {
			myInput[i] = (byte)in[i];
		}
	}
	void init(Player** otherPlayers);

	void evaluateGarbledCircuit();

	struct r1ds r1;
	void round1init();
	void round1snd();
	void round1rcv(struct msgr1 msg, int fromID);
	void round1finalize();

	ExpandedSeed** expandedSeedsShare;
	void round2init();
	void round2snd();
	void round2rcv(struct msgr2 msg, int fromID);
	void round2finalize();

	struct r3ds r3;
	void round3init();
	void round3snd();
	void round3rcv(struct msgr3 msg, int fromID);
	void round3finalize();

private:

	struct GarbledOutput getGO(struct GarbledInput gi) {
		GarbledOutput go;
		//go.seed = new byte[n * k];
		go.seed = gi.inSuperSeeds;
		/*
		for (int i = 0; i < n; ++i) {
			byte* inss = gi.inSuperSeeds[i];
			memcpy(go.seed + i*k, inss, k);
		}
		*/
		return go;
	}
	//byte** garbledInput;
	GarbledInput* garbledInput;

	byte** shareInput();

	//struct ExpandedSeed** shareExpandedSeeds();

	byte** multShare();

	//byte*** revealF();
	//byte** revealGarbledInput();
	//byte*** revealGateLabels();

	vector<byte> myInput;

	//CryptoRoutines cr;
	CircuitComponent* circuit;
	Player** otherPlayers;
	int n;
	int me;
	int k;
	int eventLength;
	int gatesCount;
	int notHomomorphicGatesCount;
	Evaluation* eval;

};


#endif /* PLAYER_H_ */

