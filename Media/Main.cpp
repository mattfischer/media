#include "MP4/Container.hpp"
#include "MP4/TrackReader.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cerr << "Error: Filename required" << std::endl;
		return 1;
	}

	std::string filename = argv[1];

	MP4::Container container(filename);

	if (!container.valid()) {
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return 1;
	}

	char buffer[1024];
	MP4::TrackReader reader(*container.tracks()[0]);
	while (true) {
		unsigned int read = reader.readNextSample(buffer, sizeof(buffer));
		if (read == 0) {
			break;
		}
		std::cout << "Sample size: " << read << std::endl;
	}
	return 0;
}