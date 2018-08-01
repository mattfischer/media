#ifndef MP4_BOX_FILE_TYPE_HPP
#define MP4_BOX_FILE_TYPE_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace MP4 {
	class BoxReference;

	namespace Box {
		struct FileType {
			std::string major_brand;
			std::uint32_t minor_version;
			std::vector<std::string> compatible_brands;

			FileType(const BoxReference &boxReference);
		};
	}
}
#endif