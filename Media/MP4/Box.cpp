#include "Box.hpp"

namespace MP4 {
	namespace Box {
		ChunkOffset::ChunkOffset(const BoxReference &boxReference)
		{
			std::uint32_t entry_count = boxReference.readUint32(4);

			std::uint64_t offset = 8;
			for (unsigned int i = 0; i < entry_count; i++) {
				chunk_offsets.push_back(boxReference.readUint32(offset));
				offset += 4;
			}
		}

		FileType::FileType(const BoxReference &boxReference)
		{
			char brand[4];
			boxReference.read(brand, 4, 0);
			major_brand = std::string(brand, 4);
			minor_version = boxReference.readUint32(4);
			uint64_t offset = 8;
			for (uint64_t offset = 8; offset < boxReference.dataSize(); offset += 4) {
				boxReference.read(brand, 4, offset);
				compatible_brands.push_back(std::string(brand, 4));
			}
		}

		SampleSize::SampleSize(const BoxReference &boxReference)
		{
			std::uint32_t sample_size = boxReference.readUint32(4);
			std::uint32_t sample_count = boxReference.readUint32(8);

			std::uint64_t offset = 12;
			for (unsigned int i = 0; i < sample_count; i++) {
				std::uint32_t size;
				if (sample_size > 0) {
					size = sample_size;
				} else {
					size = boxReference.readUint32(offset);
					offset += 4;
				}

				entry_sizes.push_back(size);
			}
		}

		SampleToChunk::SampleToChunk(const BoxReference &boxReference)
		{
			std::uint32_t entry_count = boxReference.readUint32(4);
			std::uint64_t offset = 8;
			for (unsigned int i = 0; i < entry_count; i++) {
				Entry entry;
				entry.first_chunk = boxReference.readUint32(offset);
				entry.samples_per_chunk = boxReference.readUint32(offset + 4);
				entry.sample_description_index = boxReference.readUint32(offset + 8);
				entries.push_back(entry);
				offset += 12;
			}
		}

		Handler::Handler(const BoxReference &boxReference)
		{
			char type_chars[4];
			boxReference.read(type_chars, 4, 8);
			type = std::string(type_chars, 4);
			char *name_chars = new char[(unsigned int)boxReference.dataSize() - 12];
			boxReference.read(name_chars, boxReference.dataSize() - 12, 12);
			name = std::string(name_chars);
			delete[] name_chars;
		}

		SampleDescription::SampleDescription(const BoxReference &boxReference)
		{
			std::uint32_t entry_count = boxReference.readUint32(4);
			std::uint64_t offset = 8;
			for (unsigned int i = 0; i < entry_count; i++) {
				BoxReference newBoxReference(boxReference.file(), boxReference.offset() + boxReference.dataStart() + offset);
				entries.push_back(newBoxReference);
				offset += newBoxReference.size();
			}
		}

		AudioSampleEntry::AudioSampleEntry(const BoxReference &boxReference)
		{
			data_reference_index = boxReference.readUint16(6);
			channelcount = boxReference.readUint16(16);
			samplesize = boxReference.readUint16(18);
			pre_defined = boxReference.readUint16(20);
			samplerate = boxReference.readUint32(24);
		}

		ESDBox::ESDBox(const BoxReference &boxReference) {
			ES.resize((unsigned int)boxReference.dataSize() - 4);
			boxReference.read(&ES[0], boxReference.dataSize() - 4, 4);
		}

		MP4AudioSampleEntry::MP4AudioSampleEntry(const BoxReference &boxReference)
		{
			audioSampleEntry = AudioSampleEntry(boxReference);
			BoxReference esds(boxReference.file(), boxReference.offset() + boxReference.dataStart() + 28);
			esdBox = ESDBox(esds);
		}
	}
}