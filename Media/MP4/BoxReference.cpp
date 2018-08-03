#include "BoxReference.hpp"

#include "File.hpp"

#include <cstring>

namespace MP4 {
	BoxReference::BoxReference(const File &file)
		: mFile(file)
	{
		std::memset(mType, 0, 4);
		mSize = mFile.size();
		mOffset = 0;
		mDataStart = 0;
	}

	BoxReference::BoxReference(const File &file, std::uint64_t offset)
		: mFile(file)
	{
		mOffset = offset;
		mSize = mFile.readUint32(offset);
		mFile.read(mType, 4, offset + 4);
		mDataStart = 8;
		if (mSize == 1) {
			mSize = mFile.readUint64(offset + 8);
			mDataStart += 8;
		}
	}

	const File &BoxReference::file() const
	{
		return mFile;
	}

	std::string BoxReference::type() const
	{
		return std::string((char*)mType, 4);
	}

	std::uint64_t BoxReference::size() const
	{
		return mSize;
	}

	std::uint64_t BoxReference::dataSize() const
	{
		return mSize - mDataStart;
	}

	std::vector<BoxReference> BoxReference::children() const
	{
		std::vector<BoxReference> children;

		uint64_t offset = mDataStart;
		while (offset < mSize) {
			BoxReference newBox(mFile, mOffset + offset);
			children.push_back(newBox);
			offset += newBox.size();
		}

		return children;
	}

	BoxReference BoxReference::findChild(const std::string &type, bool &found) const
	{
		uint64_t offset = mDataStart;
		while (offset < mSize) {
			BoxReference newBox(mFile, mOffset + offset);
			if (newBox.type() == type) {
				found = true;
				return newBox;
			}
			offset += newBox.size();
		}

		found = false;
		return *this;
	}

	void BoxReference::read(void *data, std::uint64_t size, std::uint64_t position) const
	{
		mFile.read(data, size, mOffset + mDataStart + position);
	}

	std::uint32_t BoxReference::readUint32(std::uint64_t position) const
	{
		return mFile.readUint32(mOffset + mDataStart + position);
	}

	std::uint64_t BoxReference::readUint64(std::uint64_t position) const
	{
		return mFile.readUint64(mOffset + mDataStart + position);
	}
}