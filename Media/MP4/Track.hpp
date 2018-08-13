#ifndef MP4_TRACK_HPP
#define MP4_TRACK_HPP

#include "BoxReference.hpp"
#include "Box.hpp"

#include "System/EsDescriptor.hpp"

namespace MP4 {
	class Track {
	public:
		enum class Type {
			None,
			Sound,
			Video,
			Hint
		};

		Track(const BoxReference &boxReference);

		Type type() const;

		const Box::SampleSize &sampleSize() const;
		const Box::ChunkOffset &chunkOffset() const;
		const Box::SampleToChunk &sampleToChunk() const;

		const BoxReference &boxReference() const;

		const System::EsDescriptor &esDescriptor() const;

	private:
		Type mType;
		BoxReference mBoxReference;
		Box::SampleSize mSampleSize;
		Box::ChunkOffset mChunkOffset;
		Box::SampleToChunk mSampleToChunk;
		System::EsDescriptor mEsDescriptor;
	};
}
#endif