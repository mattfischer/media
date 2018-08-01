#include "File.hpp"

namespace MP4 {
	File::File(const std::string &filename)
		: mFile(filename.c_str(), std::ios_base::in | std::ios_base::binary)
	{
	}

	bool File::valid()
	{
		return mFile.good();
	}
}