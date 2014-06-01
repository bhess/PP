/*
 * cryptoroutines.cpp
 *
 *  Created on: Jul 1, 2009
 *      Author: bhess
 */

#include "cryptoroutines.h"
#include "randpoolold.h"


byte* getRandomBlocks(int blocks) {
	//AutoSeededRandomPool asrng;
	byte* randBlocks = new byte[blocks];
	asrng.GenerateBlock(randBlocks, blocks);
	return randBlocks;
}

/*
 * k: seed size, n: nmbr of players
 */
struct ExpandedSeed expandSeed(int k, int n, byte* seed){
	ExpandedSeed res;
	res.seed = seed;
	res.F = new byte[k];
	res.G = new byte[n*k];
	res.H = new byte[n*k];

	RandomPoolOld rpo;
	rpo.Put(seed, k);

	rpo.GenerateBlock(res.F, k);
	rpo.GenerateBlock(res.G, n*k);
	rpo.GenerateBlock(res.H, n*k);
	return res;
}

byte* expandSeedF(int k, byte* seed) {
	byte* res = new byte[k];
	RandomPoolOld rpo;
	rpo.Put(seed, k);
	rpo.GenerateBlock(res, k);
	return res;
}

byte* expandSeedG(int k, int n, byte* seed) {
	byte* res = new byte[n*k];
	RandomPoolOld rpo;
	rpo.Put(seed, k);
	rpo.GenerateBlock(res, k);
	rpo.GenerateBlock(res, n*k);
	return res;
}

byte* expandSeedH(int k, int n, byte* seed) {
	byte* res = new byte[n * k];
	RandomPoolOld rpo;
	rpo.Put(seed, k);
	rpo.GenerateBlock(res, k);
	rpo.GenerateBlock(res, n * k);
	rpo.GenerateBlock(res, n * k);
	return res;
}

byte* expandSeed2(int k, int expandSize, byte* seed) {
	RandomPoolOld rpo;
	rpo.Put(seed, k);
	byte* res = new byte[expandSize];
	rpo.GenerateBlock(res, expandSize);
	return res;
}

bool bytewiseComparison(byte* c1, byte* c2, int size) {
	for (int i = 0; i < size; ++i) {
		if (c1[i] != c2[i]) {
			return false;
		}
	}
	return true;
}

void bytewiseXor(byte* in1, byte* in2AndOut, int size) {
	for (int i = 0; i < size; ++i) {
		in2AndOut[i] = in2AndOut[i] ^ in1[i];
	}
}

byte** getSharesID(vector<byte> realValues, int nPlayers) {
	int length = realValues.size();
	byte** res = new byte*[nPlayers];
	byte tmp[length];
	for (int i = 0; i < length; ++i) {
		tmp[i] = 0b0;
	}
	for (int i = 0; i < nPlayers - 1; ++i) {
		res[i] = getRandomBlocks(length);
		for (int j = 0; j < length; ++j) {
			tmp[j] ^= res[i][j];
		}
	}
	res[nPlayers - 1] = new byte[length];
	for (int j = 0; j < length; ++j) {
		res[nPlayers - 1][j] = tmp[j] ^ realValues[j];
	}
	//bool** res = new bool[n-1][eventLength * myInput.size()];
	return res;
}

byte* getSharesID(byte realValue, int nPlayers) {
	byte* shares = getRandomBlocks(nPlayers);
	byte tmp = 0x0;
	for (int i = 0; i < nPlayers - 1; ++i) {
		tmp ^= shares[i];
	}
	shares[nPlayers - 1] = tmp ^ realValue;
	return shares;
}
