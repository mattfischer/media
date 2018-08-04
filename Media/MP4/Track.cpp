#include "Track.hpp"
#include "Box.hpp"

namespace MP4 {
	Track::Track(const BoxReference &boxReference)
		: mBoxReference(boxReference)
	{
		bool found;
		BoxReference mdia = boxReference.findChild("mdia", found);
		if (!found) {
			return;
		}

		BoxReference minf = mdia.findChild("minf", found);
		if (!found) {
			return;
		}

		BoxReference stbl = minf.findChild("stbl", found);
		if (!found) {
			return;
		}

		BoxReference stsz = stbl.findChild("stsz", found);
		if (!found) {
			return;
		}
		mSampleSize = Box::SampleSize(stsz);

		BoxReference stsc = stbl.findChild("stsc", found);
		if (!found) {
			return;
		}
		mSampleToChunk = Box::SampleToChunk(stsc);

		BoxReference stco = stbl.findChild("stco", found);
		if (!found) {
			return;
		}
		mChunkOffset = Box::ChunkOffset(stco);

		BoxReference hdlr = mdia.findChild("hdlr", found);
		if (!found) {
			return;
		}
		mHandler = Box::Handler(hdlr);

		BoxReference stsd = stbl.findChild("stsd", found);
		if (!found) {
			return;
		}
		Box::SampleDescription sampleDescription(stsd);
	}

	const Box::SampleSize &Track::sampleSize() const
	{
		return mSampleSize;
	}

	const Box::ChunkOffset &Track::chunkOffset() const
	{
		return mChunkOffset;
	}

	const Box::SampleToChunk &Track::sampleToChunk() const
	{
		return mSampleToChunk;
	}

	const BoxReference &Track::boxReference() const
	{
		return mBoxReference;
	}
}