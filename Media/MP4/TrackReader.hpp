#ifndef MP4_TRACK_READER_HPP
#define MP4_TRACK_READER_HPP

#include "Track.hpp"

namespace MP4 {
	class TrackReader {
	public:
		TrackReader(const Track &track);

		unsigned int readNextSample(void *buffer, unsigned int bufferSize);

	private:
		const Track &mTrack;
		unsigned int mSampleIndex;
		unsigned int mSampleToChunkIndex;
		unsigned int mChunkIndex;
		unsigned int mFirstSampleInChunk;
		unsigned int mOffsetWithinChunk;
	};
}
#endif