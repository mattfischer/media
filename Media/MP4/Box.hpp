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

			ChunkOffset() = default;
			ChunkOffset(const BoxReference &boxReference);
		};

		struct FileType {
			std::string major_brand;
			std::uint32_t minor_version;
			std::vector<std::string> compatible_brands;

			FileType() = default;
			FileType(const BoxReference &boxReference);
		};

		struct SampleSize {
			std::vector<std::uint32_t> entry_sizes;

			SampleSize() = default;
			SampleSize(const BoxReference &boxReference);
		};

		struct SampleToChunk {
			struct Entry {
				std::uint32_t first_chunk;
				std::uint32_t samples_per_chunk;
				std::uint32_t sample_description_index;
			};

			std::vector<Entry> entries;

			SampleToChunk() = default;
			SampleToChunk(const BoxReference &boxReference);
		};

		struct Handler {
			std::string type;
			std::string name;

			Handler() = default;
			Handler(const BoxReference &boxReference);
		};

		struct SampleDescription {
			std::vector<BoxReference> entries;

			SampleDescription() = default;
			SampleDescription(const BoxReference &boxReference);
		};
	}
}
#endif