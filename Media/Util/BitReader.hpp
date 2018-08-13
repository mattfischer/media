#ifndef UTIL_BIT_READER_HPP
#define UTIL_BIT_READER_HPP

#include <stdint.h>
#include <vector>

namespace Util {
	class BitReader {
	public:
		BitReader(const uint8_t *buffer, size_t size);
		BitReader(const std::vector<uint8_t> &buffer);

		uint64_t read(unsigned int numBits);
		void readBytes(uint8_t *buffer, size_t size);

		void align();

	private:
		const uint8_t *mBuffer;
		size_t mSize;
		unsigned int mBitPosition;
	};
}
#endif