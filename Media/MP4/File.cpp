#include "File.hpp"
#include "BoxReference.hpp"

namespace MP4 {
	File::File(const std::string &filename)
		: mFile(filename.c_str(), std::ios_base::in | std::ios_base::binary)
	{
	}

	bool File::valid() const
	{
		return mFile.good();
	}

	std::uint64_t File::size() const
	{
		mFile.seekg(0, std::ios_base::end);
		return mFile.tellg();
	}

	BoxReference File::root() const
	{
		return BoxReference(*this);
	}

	void File::read(void *data, std::uint64_t size, std::uint64_t position) const
	{
		mFile.seekg(position);
		mFile.read((char*)data, size);
	}

	std::uint16_t File::readUint16(std::uint64_t position) const
	{
		std::uint8_t data[2];
		read(data, 2, position);

		return ((uint32_t)data[1]) |
			((uint32_t)data[0] << 8);
	}

	std::uint32_t File::readUint32(std::uint64_t position) const
	{
		std::uint8_t data[4];
		read(data, 4, position);

		return ((uint32_t)data[3]) |
			   ((uint32_t)data[2] << 8) |
			   ((uint32_t)data[1] << 16) |
			   ((uint32_t)data[0] << 24);
	}

	std::uint64_t File::readUint64(std::uint64_t position) const
	{
		std::uint8_t data[8];
		read(data, 8, position);

		return ((uint64_t)data[7]) |
			   ((uint64_t)data[6] << 8) |
			   ((uint64_t)data[5] << 16) |
			   ((uint64_t)data[4] << 24) |
			   ((uint64_t)data[3] << 32) |
			   ((uint64_t)data[2] << 40) |
			   ((uint64_t)data[1] << 48) |
			   ((uint64_t)data[0] << 56);
	}
}