#ifndef MP4_FILE_HPP
#define MP4_FILE_HPP

#include <string>
#include <fstream>

namespace MP4 {
	class File {
	public:
		File(const std::string &filename);

		bool valid();

	private:
		std::ifstream mFile;
	};
}
#endif