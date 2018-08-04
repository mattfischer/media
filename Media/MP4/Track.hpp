#ifndef MP4_TRACK_HPP
#define MP4_TRACK_HPP

#include "BoxReference.hpp"
#include "Box.hpp"

namespace MP4 {
	class Track {
	public:
		Track(const BoxReference &boxReference);

		const Box::SampleSize &sampleSize() const;
		const Box::ChunkOffset &chunkOffset() const;
		const Box::SampleToChunk &sampleToChunk() const;

		const BoxReference &boxReference() const;

	private:
		BoxReference mBoxReference;
		Box::SampleSize mSampleSize;
		Box::ChunkOffset mChunkOffset;
		Box::SampleToChunk mSampleToChunk;
	};
}
#endif