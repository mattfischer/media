#include "MP4/File.hpp"
#include "MP4/BoxReference.hpp"
#include "MP4/Box/FileType.hpp"
#include "MP4/Box/SampleSize.hpp"
#include "MP4/Box/SampleToChunk.hpp"
#include "MP4/Box/ChunkOffset.hpp"

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

	MP4::BoxReference stsc = stbl.findChild("stsc", found);
	MP4::Box::SampleToChunk sampleToChunk(stsc);

	MP4::BoxReference stco = stbl.findChild("stco", found);
	MP4::Box::ChunkOffset chunkOffset(stco);

	return 0;
}