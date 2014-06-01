/*
 * sample.h
 *
 *  Created on: Jun 30, 2009
 *      Author: bhess
 */

#include <cryptopp/md5.h>
#include <cryptopp/hex.h>
#include "../protocol/message.h"
#include <cryptopp/osrng.h>

#include <vector>

using namespace std;
//#include <cryptopp/ida.h>
//#include <cryptopp/randpool.h>

using namespace CryptoPP;

/*
	void doe() {
		CryptoPP::MD5 hash;
		byte digest[ CryptoPP::MD5::DIGESTSIZE ];
		std::string message = "abcdefghijklmnopqrstuvwxyz";

		hash.CalculateDigest(digest, (byte const*)message.c_str(), message.length());
		//hash.CalculateDigest( digest, message.c, message.length() );

		CryptoPP::HexEncoder encoder;
		std::string output;
		encoder.Attach( new CryptoPP::StringSink(output) );
		encoder.Put( digest, sizeof(digest) );
		encoder.MessageEnd();

		//std::cout << output << std::endl;
	}
*/
	byte* getRandomBlocks(int blocks);

	static AutoSeededRandomPool asrng;
	struct ExpandedSeed expandSeed(int k, int n, byte* seed);
	byte* expandSeedF(int k, byte* seed);
	byte* expandSeedG(int k, int n, byte* seed);
	byte* expandSeedH(int k, int n, byte* seed);


	bool bytewiseComparison(byte* c1, byte* c2, int size);
	void bytewiseXor(byte* in1, byte* in2AndOut, int size);

	byte** getSharesID(vector<byte> realValues, int nPlayers);
	byte* getSharesID(byte realValue, int nPlayers);
