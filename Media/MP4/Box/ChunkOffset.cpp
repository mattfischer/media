#include "ChunkOffset.hpp"

#include "MP4/BoxReference.hpp"

namespace MP4 {
	namespace Box {
		ChunkOffset::ChunkOffset(const BoxReference &boxReference)
		{
			std::uint32_t entry_count = boxReference.readUint32(4);

			std::uint64_t offset = 8;
			for (unsigned int i = 0; i < entry_count; i++) {
				chunk_offsets.push_back(boxReference.readUint32(offset));
				offset += 4;
			}
		}
	}
}