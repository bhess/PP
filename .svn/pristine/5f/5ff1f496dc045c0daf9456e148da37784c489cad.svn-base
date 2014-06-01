// randpool.cpp - written and placed in the public domain by Wei Dai
// The algorithm in this module comes from PGP's randpool.c

#include <cryptopp/pch.h>

#ifndef CRYPTOPP_IMPORTS

#include "randpoolold.h"
#include <cryptopp/mdc.h>
#include <cryptopp/sha.h>
#include <cryptopp/modes.h>

NAMESPACE_BEGIN(CryptoPP)

typedef MDC<SHA> RandomPoolOldCipher;

RandomPoolOld::RandomPoolOld(unsigned int poolSize)
	: pool(poolSize), key(RandomPoolOldCipher::DEFAULT_KEYLENGTH)
{
	assert(poolSize > key.size());

	addPos=0;
	getPos=poolSize;
	memset(pool, 0, poolSize);
	memset(key, 0, key.size());
}

void RandomPoolOld::Stir()
{
	CFB_Mode<RandomPoolOldCipher>::Encryption cipher;

	for (int i=0; i<2; i++)
	{
		cipher.SetKeyWithIV(key, key.size(), pool.end()-cipher.IVSize());
		cipher.ProcessString(pool, pool.size());
		memcpy(key, pool, key.size());
	}

	addPos = 0;
	getPos = key.size();
}

size_t RandomPoolOld::Put2(const byte *inString, size_t length, int messageEnd, bool blocking)
{
	size_t t;

	while (length > (t = pool.size() - addPos))
	{
		xorbuf(pool+addPos, inString, t);
		inString += t;
		length -= t;
		Stir();
	}

	if (length)
	{
		xorbuf(pool+addPos, inString, length);
		addPos += length;
		getPos = pool.size(); // Force stir on get
	}

	return 0;
}

size_t RandomPoolOld::TransferTo2(BufferedTransformation &target, lword &transferBytes, const std::string &channel, bool blocking)
{
	if (!blocking)
		throw NotImplemented("RandomPoolOld: nonblocking transfer is not implemented by this object");

	lword size = transferBytes;

	while (size > 0)
	{
		if (getPos == pool.size())
			Stir();
		size_t t = UnsignedMin(pool.size() - getPos, size);
		target.ChannelPut(channel, pool+getPos, t);
		size -= t;
		getPos += t;
	}

	return 0;
}

byte RandomPoolOld::GenerateByte()
{
	if (getPos == pool.size())
		Stir();

	return pool[getPos++];
}

void RandomPoolOld::GenerateBlock(byte *outString, size_t size)
{
	ArraySink sink(outString, size);
	TransferTo(sink, size);
}

NAMESPACE_END

#endif
