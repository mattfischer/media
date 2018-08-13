#include "EsDescriptor.hpp"

#include "Util/BitReader.hpp"

namespace System {
	std::uint32_t readLength(Util::BitReader &reader)
	{
		std::uint32_t ret = 0;
		std::uint8_t flag;
		do {
			flag = (std::uint8_t)reader.read(1);
			std::uint8_t newBits = (std::uint8_t)reader.read(7);
			ret = (ret << 7) | newBits;

		} while (flag == 1);

		return ret;
	}

	EsDescriptor::EsDescriptor(const std::vector<uint8_t> &buffer)
	{
		Util::BitReader reader(buffer);

		reader.read(8); // type
		readLength(reader); // length

		reader.read(16); // ES_ID
		std::uint8_t streamDependenceFlag = (std::uint8_t)reader.read(1);
		std::uint8_t URL_Flag = (std::uint8_t)reader.read(1);
		std::uint8_t OCRstreamFlag = (std::uint8_t)reader.read(1);
		reader.read(5); // streamPriority
		if (streamDependenceFlag) {
			reader.read(16); // dependsOn_ES_ID
		}

		if (URL_Flag) {
			std::uint8_t URLlength = (std::uint8_t)reader.read(8);
			reader.readBytes(0, URLlength); // URLstring
		}

		if (OCRstreamFlag) {
			reader.read(16); // OCR_ES_Id
		}

		std::uint8_t type = (std::uint8_t)reader.read(8);
		std::uint32_t length = readLength(reader);
		std::uint8_t objectTypeIndication = (std::uint8_t)reader.read(8);
		std::uint8_t streamType = (std::uint8_t)reader.read(6);
		std::uint8_t upStream = (std::uint8_t)reader.read(1);
		reader.read(1);
		std::uint32_t bufferSizeDB = (std::uint32_t)reader.read(24);
		std::uint32_t maxBitrate = (std::uint32_t)reader.read(32);
		std::uint32_t avgBitrate = (std::uint32_t)reader.read(32);

		type = (std::uint8_t)reader.read(8);
		length = readLength(reader);

		mDecoderConfigDescriptor.resize(length);
		reader.readBytes(&mDecoderConfigDescriptor[0], length);
	}

	const std::vector<std::uint8_t> &EsDescriptor::decoderConfigDescriptor() const
	{
		return mDecoderConfigDescriptor;
	}
}