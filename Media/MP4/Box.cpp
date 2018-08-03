#include "Box.hpp"

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

		FileType::FileType(const BoxReference &boxReference)
		{
			char brand[4];
			boxReference.read(brand, 4, 0);
			major_brand = std::string(brand, 4);
			minor_version = boxReference.readUint32(4);
			uint64_t offset = 8;
			for (uint64_t offset = 8; offset < boxReference.dataSize(); offset += 4) {
				boxReference.read(brand, 4, offset);
				compatible_brands.push_back(std::string(brand, 4));
			}
		}

		SampleSize::SampleSize(const BoxReference &boxReference)
		{
			std::uint32_t sample_size = boxReference.readUint32(4);
			std::uint32_t sample_count = boxReference.readUint32(8);

			std::uint64_t offset = 12;
			for (unsigned int i = 0; i < sample_count; i++) {
				std::uint32_t size;
				if (sample_size > 0) {
					size = sample_size;
				} else {
					size = boxReference.readUint32(offset);
					offset += 4;
				}

				entry_sizes.push_back(size);
			}
		}

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