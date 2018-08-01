#ifndef MP4_BOX_REFERENCE_HPP
#define MP4_BOX_REFERENCE_HPP

#include <fstream>
#include <cstdint>
#include <vector>

namespace MP4 {
	class File;

	class BoxReference {
	public:
		BoxReference(const File &file);
		BoxReference(const File &file, std::uint64_t start);

		std::string type() const;
		std::uint64_t size() const;

		std::vector<BoxReference> children() const;

	private:
		const File &mFile;
		std::uint64_t mDataStart;
		std::uint8_t mType[4];
		std::uint64_t mSize;
	};
}
#endif