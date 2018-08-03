#include "Container.hpp"
#include "BoxReference.hpp"
#include "Box.hpp"

namespace MP4 {
	Container::Container(const std::string &filename)
		: mFile(filename)
	{
		if (!mFile.valid()) {
			return;
		}

		bool found;
		BoxReference moov = mFile.root().findChild("moov", found);
		if (!found) {
			return;
		}

		for (const BoxReference &child : moov.children()) {
			if (child.type() == "trak") {
				std::unique_ptr<Track> track = std::make_unique<Track>(child);
				mTracks.push_back(std::move(track));
			}
		}
	}

	bool Container::valid() const
	{
		return mFile.valid();
	}

	const std::vector<std::unique_ptr<Track>> &Container::tracks() const
	{
		return mTracks;
	}
}