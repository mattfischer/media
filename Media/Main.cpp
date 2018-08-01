#include "MP4/File.hpp"
#include "MP4/BoxReference.hpp"
#include "MP4/Box/FileType.hpp"
#include "MP4/Box/SampleSize.hpp"

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

	bool found;
	MP4::BoxReference moov = file.root().findChild("moov", found);
	MP4::BoxReference trak = moov.findChild("trak", found);
	MP4::BoxReference mdia = trak.findChild("mdia", found);
	MP4::BoxReference minf = mdia.findChild("minf", found);
	MP4::BoxReference stbl = minf.findChild("stbl", found);
	MP4::BoxReference stsz = stbl.findChild("stsz", found);

	MP4::Box::SampleSize sampleSize(stsz);
	std::cout << "Sample sizes:" << std::endl;
	for (std::uint32_t size : sampleSize.entry_sizes) {
		std::cout << "  " << size << std::endl;
	}
	return 0;
}