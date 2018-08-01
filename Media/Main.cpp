#include "MP4/File.hpp"
#include "MP4/BoxReference.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cerr << "Error: Filename required" << std::endl;
		return 1;
	}

	std::string filename = argv[1];
	MP4::File file(filename);

	if (!file.valid()) {
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return 1;
	}

	std::vector<MP4::BoxReference> boxes = file.root().children();
	std::cout << "Root boxes:" << std::endl;
	for (const MP4::BoxReference &box : boxes) {
		std::cout << "  " << box.type() << std::endl;
	}

	return 0;
}