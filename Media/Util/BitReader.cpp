#include "BitReader.hpp"

#include <algorithm>

namespace Util {
	BitReader::BitReader(const uint8_t *buffer, size_t size) :
		mBuffer(buffer), mSize(size), mBitPosition(0)
	{
	}

	uint64_t BitReader::read(unsigned int numBits)
	{
		uint64_t ret = 0;
		while (numBits > 0) {
			unsigned int byte = mBitPosition / 8;
			unsigned int bitsLeftInByte = 8 - (mBitPosition % 8);
			unsigned int bitsToRead = std::min(numBits, bitsLeftInByte);
			unsigned int shift = (bitsLeftInByte - bitsToRead);
			unsigned int mask = (1 << bitsToRead) - 1;

			uint8_t newBits = (mBuffer[byte] >> shift) & mask;
			ret = (ret << bitsToRead) | newBits;

			mBitPosition += bitsToRead;
			numBits -= bitsToRead;
		}

		return ret;
	}
}