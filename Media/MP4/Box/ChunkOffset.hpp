#ifndef MP4_BOX_CHUNK_OFFSET_HPP
#define MP4_BOX_CHUNK_OFFSET_HPP

#include <cstdint>
#include <vector>

namespace MP4 {
	class BoxReference;

	namespace Box {
		struct ChunkOffset {
			std::vector<std::uint32_t> chunk_offsets;

			ChunkOffset(const BoxReference &boxReference);
		};
	}
}
#endif