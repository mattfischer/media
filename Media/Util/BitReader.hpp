#ifndef UTIL_BIT_READER_HPP
#define UTIL_BIT_READER_HPP

#include <stdint.h>

namespace Util {
	class BitReader {
	public:
		BitReader(const uint8_t *buffer, size_t size);

		uint64_t read(unsigned int numBits);

	private:
		const uint8_t *mBuffer;
		size_t mSize;
		unsigned int mBitPosition;
	};
}
#endif