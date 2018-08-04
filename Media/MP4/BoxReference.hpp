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

		const File &file() const;
		std::uint64_t offset() const;

		std::string type() const;
		std::uint64_t size() const;
		std::uint64_t dataSize() const;
		std::uint64_t dataStart() const;

		std::vector<BoxReference> children() const;

		BoxReference findChild(const std::string &type, bool &found) const;

		void read(void *data, std::uint64_t size, std::uint64_t position) const;
		std::uint16_t readUint16(std::uint64_t position) const;
		std::uint32_t readUint32(std::uint64_t position) const;
		std::uint64_t readUint64(std::uint64_t position) const;

	private:
		const File &mFile;
		std::uint64_t mOffset;
		std::uint64_t mDataStart;
		std::uint8_t mType[4];
		std::uint64_t mSize;
	};
}
#endif