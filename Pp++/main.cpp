//============================================================================
// Name        : PpCpp.cpp
// Author      : Basil Hess
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include "circuit/CircuitComponent.h"
#include "factories/SortAndRuleCheck.h"
#include "factories/Sorting.h"
#include "circuit/Evaluation.h"

#include "protocol/player.h"

//#include "crypto/cryptoroutines.h"

using namespace std;

void printSample(vector<bool> sample) {
	cout << "[";
	for (unsigned int i = 0; i < sample.size(); ++i) {
		cout << (sample[i] ? "1" : "0") << ",";
	}
	cout << "]\n";
}

void example() {
	int time = 8;
	int rep = 3;
	/*
	 bool sampler[]={	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,1,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,1,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,1,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,
	 };
	 */

	bool sampler[] = {	0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,
						0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,
						0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,1,0,
						0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,

	};

	int secparam = 8;
	Player** players = new Player*[rep];
	bool in1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 };
	bool in2[] = { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
	bool in3[] = { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0 };
	bool in4[] = { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0 };
	for (int i = 0; i < rep; ++i) {
		players[i] = new Player(time, 9, rep, rep, i, secparam);
		//players[i]->setInput(vector<bool>(player))
	}
	for (int i = 0; i < rep; ++i) {
		players[i]->init(players);
	}
	//players[0]->setInput(vector<bool>(in1, in1 + sizeof(in1) / sizeof(bool)));
	//players[1]->setInput(vector<bool>(in1, in1 + sizeof(in1) / sizeof(bool)));
	//players[2]->setInput(vector<bool>(in1, in1 + sizeof(in1) / sizeof(bool)));
	//players[3]->setInput(vector<bool>(in4, in4 + sizeof(in4)));
	for (int i = 0; i < rep; ++i) {
		players[i]->round1init();
	}
	for (int i = 0; i < rep; ++i) {
		players[i]->round1snd();
	}
	for (int i = 0; i < rep; ++i) {
		players[i]->round1finalize();
	}
	for (int i = 0; i < rep; ++i) {
		players[i]->round2init();
	}
	for (int i = 0; i < rep; ++i) {
		players[i]->round2snd();
	}
	for (int i = 0; i < rep; ++i) {
		players[i]->round2finalize();
	}
	for (int i = 0; i < rep; ++i) {
		players[i]->round3init();
	}
	for (int i = 0; i < rep; ++i) {
		players[i]->round3snd();
	}
	for (int i = 0; i < rep; ++i) {
		players[i]->round3finalize();
	}

	for (int i = 0; i < rep; ++i) {
		players[i]->evaluateGarbledCircuit();
	}

	/*
	 vector<bool> sample = vector<bool> (sampler, sampler + sizeof(sampler)
	 / sizeof(bool));


	 CircuitComponent* c2 = SortAndRuleCheck().createComponent(0, time, 9, rep);
	 Evaluation* eval2 = new Evaluation(c2);
	 CounterVisitor* cv = new CounterVisitor();
	 eval2->setVisitor(cv);
	 vector<bool> evaled2 = eval2->evaluate(sample);
	 printSample(evaled2);
	 cout << cv->cnt << " elements\n";
	 c2->destruct();
	 cout << c2->destructed << " destructed\n";
	 delete c2;
	 delete eval2;
	 delete cv;

	 cv->reset();

	 //	sleep(5);

	 c2 = SortAndRuleCheck().createComponent(0, time, 9, rep);
	 eval2 = new Evaluation(c2);
	 cv = new CounterVisitor();
	 eval2->setVisitor(cv);
	 evaled2 = eval2->evaluate(sample);
	 printSample(evaled2);
	 cout << cv->cnt << " elements\n";
	 c2->destruct();
	 cout << c2->destructed << " destructed\n";
	 delete c2;
	 delete eval2;
	 delete cv;
	 */
}

int main(void) {
	int rep = 5;
	Player** players = new Player*[rep];

	bool in0[] = {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0};
	bool in1[] = {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0};
	bool in2[] = {0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,1,0};

	for (int i = 0; i < rep; ++i) {
		players[i] = new Player(8, 9, rep, rep, i, 32);
	}
	players[0]->setInput(vector<bool>(in0, in0 + sizeof(in0)));
	players[1]->setInput(vector<bool>(in1, in1 + sizeof(in1)));
	players[2]->setInput(vector<bool>(in2, in2 + sizeof(in2)));
	for (int i = 0; i < rep; ++i) {
		players[i]->init(players);
	}
	for (int i = 0; i < rep; ++i) {
		players[i]->round1init();
	}
	cout << "Round 1 init done\n";
	for (int i = 0; i < rep; ++i) {
		players[i]->round1snd();
	}
	cout << "Round 1 snd done\n";
	for (int i = 0; i < rep; ++i) {
		players[i]->round1finalize();
	}
	cout << "Round 1 final done\n";
	for (int i = 0; i < rep; ++i) {
		players[i]->round2init();
	}
	cout << "Round 2 init done\n";
	for (int i = 0; i < rep; ++i) {
		players[i]->round2snd();
	}
	cout << "Round 2 snd done\n";
	for (int i = 0; i < rep; ++i) {
		players[i]->round2finalize();
	}
	cout << "Round 2 final done\n";
	for (int i = 0; i < rep; ++i) {
		players[i]->round3init();
	}
	cout << "Round 3 init done\n";
	for (int i = 0; i < rep; ++i) {
		players[i]->round3snd();
	}
	cout << "Round 3 snd done\n";
	for (int i = 0; i < rep; ++i) {
		players[i]->round3finalize();
	}
	for (int i = 0; i < rep; ++i) {
		players[i]->evaluateGarbledCircuit();
	}

	/*
	for (int i = 0; i < rep; ++i) {
		printSample(players[i]->test());
	}
	*/



	//example();
	return 0;
}
