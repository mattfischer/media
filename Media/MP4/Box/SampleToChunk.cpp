#include "SampleToChunk.hpp"

#include "MP4/BoxReference.hpp"

namespace MP4 {
	namespace Box {
		SampleToChunk::SampleToChunk(const BoxReference &boxReference)
		{
			std::uint32_t entry_count = boxReference.readUint32(4);
			std::uint64_t offset = 8;
			for (unsigned int i = 0; i < entry_count; i++) {
				Entry entry;
				entry.first_chunk = boxReference.readUint32(offset);
				entry.samples_per_chunk = boxReference.readUint32(offset + 4);
				entry.sample_description_index = boxReference.readUint32(offset + 8);
				entries.push_back(entry);
				offset += 12;
			}
		}
	}
}