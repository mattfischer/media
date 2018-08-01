#ifndef MP4_BOX_SAMPLE_SIZE_HPP
#define MP4_BOX_SAMPLE_SIZE_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace MP4 {
	class BoxReference;

	namespace Box {
		struct SampleSize {
			std::vector<std::uint32_t> entry_sizes;

			SampleSize(const BoxReference &boxReference);
		};
	}
}
#endif