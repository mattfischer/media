#include "MP4/File.hpp"
#include "MP4/BoxReference.hpp"
#include "MP4/Box/FileType.hpp"

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
	std::cout << std::endl;

	bool found;
	MP4::BoxReference box = file.root().findChild("ftyp", found);
	if (found) {
		MP4::Box::FileType fileType(box);

		std::cout << "File type: " << fileType.major_brand << " " << fileType.minor_version << std::endl;
		std::cout << "Compatible brands:" << std::endl;
		for (const std::string &brand : fileType.compatible_brands) {
			std::cout << "  " << brand << std::endl;
		}
		std::cout << std::endl;
	}

	MP4::BoxReference moov = file.root().findChild("moov", found);
	if (found) {
		std::cout << "moov box children:" << std::endl;
		for (const MP4::BoxReference &box : moov.children()) {
			std::cout << "  " << box.type() << std::endl;
		}
	}

	return 0;
}