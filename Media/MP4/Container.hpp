#ifndef MP4_CONTAINER_HPP
#define MP4_CONTAINER_HPP

#include "File.hpp"
#include "Track.hpp"

#include <vector>
#include <memory>

namespace MP4 {
	class Container {
	public:
		Container(const std::string &filename);

		bool valid() const;
		const std::vector<std::unique_ptr<Track>> &tracks() const;

	private:
		File mFile;
		std::vector<std::unique_ptr<Track>> mTracks;
	};
}
#endif