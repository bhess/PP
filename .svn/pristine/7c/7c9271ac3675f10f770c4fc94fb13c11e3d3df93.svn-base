/*
 * CircuitElement.h
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#ifndef CIRCUITELEMENT_H_
#define CIRCUITELEMENT_H_

#define PRIVATE 1

#include <vector>
#include "../protocol/message.h"
using namespace std;

/**
 * Garbled output of a Gate in the circuit,
 * consists of:
 * - Superseed (corresponding to 0/1)
 * - external/masked 'value' lambda_i xor b_i
 */
struct GarbledOutput {
	bool value;
	byte* seed;
};

struct GateLabels {
	byte* A;
	byte* B;
	byte* C;
	byte* D;
};

struct TemporaryValues {
	byte* sharedSeed1; // of each player -> n times k
	byte* sharedSeed2; // of each player -> n times k
	byte* realSeed1; // real seed1 -> k;
	byte* realSeed2; // real seed2 -> k;
	byte sharedLambda;
	byte sharedMult; // binary: l_a op l_b, l_a op ~l_b, ~l_a op l_b, ~l_a op ~l_b
	byte** sharedG1; // of each player -> n times n*k
	byte** sharedG2; // of each player -> n times n*k
	byte** sharedH2; // of each player -> n times n*k
	byte** sharedH1; // of each player -> n times n*k
	byte* realG1; // real g -> n*k
	byte* realG2; // real g -> n*k
	byte* realH1; // real h -> n*k
	byte* realH2; // real h -> n*k


};

/**
 * Class that represents a single Circuit Element / Gate
 */
class CircuitElement {
public:

		/**
		 * initialize with the associated gate, the number of input wires
		 * and the number of output elements
		 * @param gate
		 * @param inWireCnt
		 * @param outElementsCnt
		 */
		CircuitElement(int inWireCnt, int outElementsCnt) {
			init(inWireCnt);
			setOutElementsCnt(outElementsCnt);
		}

		/**
		 * Initialization as above but letting the FANOUT open
		 */
		CircuitElement(int inWireCnt) {
			init(inWireCnt);
		}

		/**
		 * Sets the number of out-elements (FANOUT)
		 */
		void setOutElementsCnt(int outElementsCnt);

		/**
		 * reset all input-signals if the circuit is evaluated
		 */
		void resetSignals();

		/**
		 * Adds an input wire and the associated element.
		 * @param wire
		 * @param c
		 */
		void addInWire(int wire, CircuitElement* c);

		/**
		 * Specify the output-wire
		 * @param wire
		 */
		void addOutWire(int wire);

		/**
		 * Adds an element attached to the out-wire
		 * @param e
		 */
		void addOutElement(CircuitElement* e);

		/**
		 * Adds a signal to the wire in the array with the given signal
		 * @param index
		 * @param signal
		 */
		void addSignal(bool signal);
		void addSignal(GarbledOutput signal);

		/**
		 * Are all signals set?
		 * @return
		 */
		bool allSignalsSet();

		/**
		 * Evaluates the associated gate with the given inputs
		 * @return
		 */
		bool evaluate();

		/*
		 * Starting with LSB:
		 * 0:  l_a op  l_b == l_c
		 * 1:  l_a op ~l_b == l_c
		 * 2: ~l_a op  l_b == l_c
		 * 3: ~l_1 op ~l_b == l_c
		 */
		virtual byte evalLambdas() = 0;

		/**
		 * Is the element evaluable homomorphically, means:
		 * sh(x) op sh(y) = sh(x op y)
		 */
		virtual bool isHomomorphic() = 0;

		virtual bool isFirst() { return false; }
		virtual bool isLast() { return false; }

		// delete...
		vector<int> inWires;
		int outWire;
		//...

		/**
		 * The input and the output elements of a Gate
		 */
		vector<CircuitElement*> inElements, outElements;

		/**
		 * The two expanded seeds attached to a wire
		 */
		//ExpandedSeed exs1, exs2;

		/**
		 * the two seeds attached to a wire
		 */
		//byte* seed1;
		//byte* seed2;

		/**
		 * The gate labels Ag, Bg, ...
		 */
		GateLabels gateLabels;
		//byte** gateLabels; // binary: 4 times n*k
		byte** realF1; // of each player -> n*k
		byte** realF2; // of each player -> n*k
		byte* garbledValue; // value during evaluation -> n*k;
		// TODO: move to ResultElement
		byte lambdaRes; // revealed labmda (only result ones)

		TemporaryValues* tmpValues;
		/**
		 * The lambda value attached to a wire
		 */
		//bool lambda;

		/**
		 * evaluating with input-bits
		 * in_1 op in_2...
		 */
		virtual bool evaluate(vector<bool> in) = 0;

		//bool evaluateGarbled(vector<bool> in);

		/**
		 * The boolean input signals
		 */
		vector<bool> inSignals;

		/**
		 * The garbled input super-seeds in privacy-preserving mode
		 */
		vector<byte*> inSuperSeeds;


private:
		/**
		 * the number of signals set:
		 * = arity-> all are set
		 */
		int signalsSet;
		int inWirePos, outWirePos;
		void init(int inWireCnt);

		//void registerAtOutElements();
protected:

		virtual int getArity() = 0;
};

#endif /* CIRCUITELEMENT_H_ */
