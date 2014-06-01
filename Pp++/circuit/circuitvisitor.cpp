/*
 * circuitvisitor.cpp
 *
 *  Created on: Jul 7, 2009
 *      Author: bhess
 */
#include "circuitvisitor.h"
#include "../crypto/cryptoroutines.h"
#include "../gates/unary/Dummy.h"
#include "../circuit/LastElement.h"

void GarbledEvaluation::baseStep(GarbledOutput* go, CircuitElement* el) {
	byte* expF = expandSeedF(k, go->seed);
	go->value = !bytewiseComparison(expF, el->realF1[0], k);
	delete [] expF;
}

struct GarbledOutput GarbledEvaluation::evaluate(CircuitElement* el) {
	GarbledOutput go;
	if (dynamic_cast<LastElement*>(el)) {
		go.value = el->evaluate();
		go.seed = new byte[k*n];
		//el->inSuperSeeds[0] = go.seed;
		memcpy(go.seed, el->inSuperSeeds[0], k*n);
		return go;
	}

	byte* res;

	if (el->inSignals.size() == 1) {
		res = expandSeedG(k, n, el->inSuperSeeds[0]);
		for (int i = 1; i < n; ++i) {
			byte* tmpp = expandSeedG(k, n, el->inSuperSeeds[0] + k * i);
			bytewiseXor(tmpp, res, n * k);
			delete[] tmpp;
		}
		if (el->inSignals[0]) {
			bytewiseXor(el->gateLabels.B, res, n * k);
		} else {
			bytewiseXor(el->gateLabels.A, res, n * k);
		}
	} else {
		if (el->inSignals[0] == 0 && el->inSignals[1] == 0) {
			res = expandSeedG(k, n, el->inSuperSeeds[0]);
			byte* tmpp = expandSeedG(k, n, el->inSuperSeeds[1]);
			bytewiseXor(tmpp, res, n*k);
			delete [] tmpp;
			for (int i = 1; i < n; ++i) {
				byte* tmpp = expandSeedG(k, n, el->inSuperSeeds[0] + k*i);
				bytewiseXor(tmpp, res, n*k);
				delete [] tmpp;
				tmpp = expandSeedG(k, n, el->inSuperSeeds[1] + k*i);
				bytewiseXor(tmpp, res, n*k);
				delete [] tmpp;
			}
			bytewiseXor(el->gateLabels.A, res, n*k);
		} else if (el->inSignals[0] == 0 && el->inSignals[1] == 1) {
			res = expandSeedH(k, n, el->inSuperSeeds[0]);
			byte* tmpp = expandSeedG(k, n, el->inSuperSeeds[1]);
			bytewiseXor(tmpp, res, n * k);
			delete[] tmpp;
			for (int i = 1; i < n; ++i) {
				byte* tmpp = expandSeedH(k, n, el->inSuperSeeds[0] + k * i);
				bytewiseXor(tmpp, res, n * k);
				delete[] tmpp;
				tmpp = expandSeedG(k, n, el->inSuperSeeds[1] + k * i);
				bytewiseXor(tmpp, res, n * k);
				delete[] tmpp;
			}
			bytewiseXor(el->gateLabels.B, res, n * k);
		} else if (el->inSignals[0] == 1 && el->inSignals[1] == 0) {
			res = expandSeedG(k, n, el->inSuperSeeds[0]);
			byte* tmpp = expandSeedH(k, n, el->inSuperSeeds[1]);
			bytewiseXor(tmpp, res, n * k);
			delete[] tmpp;
			for (int i = 1; i < n; ++i) {
				byte* tmpp = expandSeedG(k, n, el->inSuperSeeds[0] + k * i);
				bytewiseXor(tmpp, res, n * k);
				delete[] tmpp;
				tmpp = expandSeedH(k, n, el->inSuperSeeds[1] + k * i);
				bytewiseXor(tmpp, res, n * k);
				delete[] tmpp;
			}
			bytewiseXor(el->gateLabels.C, res, n * k);
		} else {
			res = expandSeedH(k, n, el->inSuperSeeds[0]);
			byte* tmpp = expandSeedH(k, n, el->inSuperSeeds[1]);
			bytewiseXor(tmpp, res, n * k);
			delete[] tmpp;
			for (int i = 1; i < n; ++i) {
				byte* tmpp = expandSeedH(k, n, el->inSuperSeeds[0] + k * i);
				bytewiseXor(tmpp, res, n * k);
				delete[] tmpp;
				tmpp = expandSeedH(k, n, el->inSuperSeeds[1] + k * i);
				bytewiseXor(tmpp, res, n * k);
				delete[] tmpp;
			}
			bytewiseXor(el->gateLabels.D, res, n * k);
		}
	}

	go.seed = res;
	baseStep(&go, el);
	return go;

}
