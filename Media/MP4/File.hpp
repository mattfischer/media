#ifndef MP4_FILE_HPP
#define MP4_FILE_HPP

#include <string>
#include <fstream>
#include <cstdint>

namespace MP4 {
	class BoxReference;

	class File {
	public:
		File(const std::string &filename);

		bool valid() const;
		std::uint64_t size() const;

		BoxReference root() const;

		void read(void *data, std::uint64_t size, std::uint64_t position) const;
		std::uint16_t readUint16(std::uint64_t position) const;
		std::uint32_t readUint32(std::uint64_t position) const;
		std::uint64_t readUint64(std::uint64_t position) const;

	private:
		mutable std::ifstream mFile;
	};
}
#endif