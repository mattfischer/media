#include "SampleSize.hpp"

#include "MP4/BoxReference.hpp"

namespace MP4 {
	namespace Box {
		SampleSize::SampleSize(const BoxReference &boxReference)
		{
			std::uint32_t sample_size = boxReference.readUint32(0);
			std::uint32_t sample_count = boxReference.readUint32(0);

			for (std::uint64_t offset = 0; offset < boxReference.dataSize(); offset += 4) {
				entry_sizes.push_back(boxReference.readUint32(offset));
			}
		}
	}
}