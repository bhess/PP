/*
 * Evaluation.h
 *
 *  Created on: Jun 25, 2009
 *      Author: bhess
 */

#ifndef EVALUATION_H_
#define EVALUATION_H_

#include "CircuitComponent.h"
#include "CircuitElement.h"
#include "circuitvisitor.h"

class Evaluation {
public:

	/**
	 * Initializing an Evaluation with an
	 * associated component
	 */
	Evaluation(CircuitComponent* component);

	/**
	 * Sets a Visitor which is executed upon the
	 * traversal of the circuit
	 */
	void setVisitor(CircuitVisitor* visit) {
		this->visitor = visit;
	}

	/*
	void deleteVisitor() {
		delete visitor;
	}
	*/

	/**
	 * The results of the circuit evaluation
	 */
	vector<bool> *results;


	/**
	 * Evaluates the circuit in non privacy-preserving mode
	 * by supplying the input bits
	 */
	vector<bool> evaluate(vector<bool> inputBits);

	/**
	 * Evaluates the circuit in privacy-preserving mode
	 * by supplying the garbled input:
	 * s_i^1|..|s_i^n
	 * -> without an external value
	 */
	vector<bool> evaluate(vector<GarbledOutput> inputBits);

	/**
	 * Traverses the Circuit using the same algorithm as in
	 * the circuit evaluation.
	 *
	 * Can be used with attaching a visitor to do some pre-
	 * processing.
	 */
	void evaluate();

	void setGarbledEvaluator(int n, int k) {
		this->garbledEvaluation = new GarbledEvaluation(n, k);
	}

private:

	/**
	 * Assigns to the garbled inputs for each wire the
	 * external values by expanding the seeds and compare
	 * it with the f walue
	 */
	void applyGarbledInput(vector<GarbledOutput>* input);

	/**
	 * The associated Circuit
	 */
	CircuitComponent* component;

	/**
	 * The associated Visitor while traversing
	 */
	CircuitVisitor* visitor;

	/**
	 * Special visitor for privacy preserving evaluation
	 */
	GarbledEvaluation* garbledEvaluation;

	/**
	 * Evaluation recursively called
	 */
	void evaluate(CircuitElement* c);

	/**
	 * The privacy preserving equivalent
	 */
	void evaluatePrivate(CircuitElement* c);
};

#endif /* EVALUATION_H_ */
