#include "FileType.hpp"

#include "MP4/BoxReference.hpp"

namespace MP4 {
	namespace Box {
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
	}
}