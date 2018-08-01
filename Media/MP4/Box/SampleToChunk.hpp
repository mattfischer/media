#ifndef MP4_BOX_SAMPLE_TO_CHUNK_HPP
#define MP4_BOX_SAMPLE_TO_CHUNK_HPP

#include <cstdint>
#include <vector>

namespace MP4 {
	class BoxReference;

	namespace Box {
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