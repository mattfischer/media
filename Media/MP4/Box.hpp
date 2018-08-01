#ifndef MP4_BOX_HPP
#define MP4_BOX_HPP

#include "BoxReference.hpp"

#include <cstdint>
#include <vector>

namespace MP4 {
	class BoxReference;

	namespace Box {
		struct ChunkOffset {
			std::vector<std::uint32_t> chunk_offsets;

			ChunkOffset(const BoxReference &boxReference);
		};

		struct FileType {
			std::string major_brand;
			std::uint32_t minor_version;
			std::vector<std::string> compatible_brands;

			FileType(const BoxReference &boxReference);
		};

		struct SampleSize {
			std::vector<std::uint32_t> entry_sizes;

			SampleSize(const BoxReference &boxReference);
		};

		struct SampleToChunk {
			struct Entry {
				std::uint32_t first_chunk;
				std::uint32_t samples_per_chunk;
				std::uint32_t sample_description_index;
			};

			std::vector<Entry> entries;

			SampleToChunk(const BoxReference &boxReference);
		};
	}
}
#endif