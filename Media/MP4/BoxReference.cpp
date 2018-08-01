#include "BoxReference.hpp"

#include "File.hpp"

#include <cstring>

namespace MP4 {
	BoxReference::BoxReference(const File &file)
		: mFile(file)
	{
		std::memset(mType, 0, 4);
		mSize = mFile.size();
		mDataStart = 0;
	}

	BoxReference::BoxReference(const File &file, std::uint64_t offset)
		: mFile(file)
	{
		mSize = mFile.readUint32(offset);
		mFile.read(mType, 4, offset + 4);
		mDataStart = offset + 8;
		if (mSize == 1) {
			mSize = mFile.readUint64(offset + 8);
			mDataStart += 8;
		}
	}

	std::string BoxReference::type() const
	{
		return std::string((char*)mType, 4);
	}

	std::uint64_t BoxReference::size() const
	{
		return mSize;
	}

	std::vector<BoxReference> BoxReference::children() const
	{
		std::vector<BoxReference> children;

		uint64_t offset = mDataStart;
		while (offset < mDataStart + mSize) {
			BoxReference newBox(mFile, offset);
			children.push_back(newBox);
			offset += newBox.size();
		}

		return children;
	}
}