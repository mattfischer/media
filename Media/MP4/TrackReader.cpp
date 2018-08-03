#include "TrackReader.hpp"
#include "File.hpp"

#include <algorithm>

namespace MP4 {
	TrackReader::TrackReader(const Track &track)
		: mTrack(track)
	{
		mSampleIndex = 0;
		mSampleToChunkIndex = 0;
		mChunkIndex = mTrack.sampleToChunk().entries[mSampleToChunkIndex].first_chunk;
		mFirstSampleInChunk = 0;
		mOffsetWithinChunk = 0;
	}

	unsigned int TrackReader::readNextSample(void *buffer, unsigned int bufferSize)
	{
		if (mSampleIndex >= mTrack.sampleSize().entry_sizes.size()) {
			return 0;
		}

		uint32_t offset = mTrack.chunkOffset().chunk_offsets[mChunkIndex - 1];
		uint32_t size = mTrack.sampleSize().entry_sizes[mSampleIndex];
		mTrack.boxReference().file().read(buffer, std::min(size, bufferSize), offset + mOffsetWithinChunk);
		mOffsetWithinChunk += mTrack.sampleSize().entry_sizes[mSampleIndex];
		mSampleIndex++;
		
		if (mSampleIndex - mFirstSampleInChunk >= mTrack.sampleToChunk().entries[mSampleToChunkIndex].samples_per_chunk) {
			mChunkIndex++;
			mFirstSampleInChunk = mSampleIndex;
			mOffsetWithinChunk = 0;
		}
		while (mSampleToChunkIndex < mTrack.sampleToChunk().entries.size() - 1 && mChunkIndex >= mTrack.sampleToChunk().entries[mSampleToChunkIndex + 1].first_chunk) {
			mSampleToChunkIndex++;
		}

		return size;
	}
}