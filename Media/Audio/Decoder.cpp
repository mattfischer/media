#include "Decoder.hpp"

#include "Util/BitReader.hpp"

namespace Audio {
	std::uint32_t getAudioObjectType(Util::BitReader &reader)
	{
		std::uint16_t audioObjectType = (std::uint16_t)reader.read(5);
		if (audioObjectType == 31) {
			audioObjectType = 32 + (std::uint16_t)reader.read(6);
		}
		return audioObjectType;
	}

	Decoder::Decoder(const System::EsDescriptor &esDescriptor)
	{
		Util::BitReader reader(esDescriptor.decoderConfigDescriptor());

		std::uint16_t audioObjectType = getAudioObjectType(reader);
		std::uint8_t samplingFrequencyIndex = (std::uint8_t)reader.read(4);
		if (samplingFrequencyIndex == 0xf) {
			reader.read(24); // samplingFrequency
		}
		std::uint8_t channelConfiguration = (std::uint8_t)reader.read(4);

		if (audioObjectType == 5 || audioObjectType == 29) {
			std::uint8_t extensionSamplingFrequencyIndex = (std::uint8_t)reader.read(4);
			if (extensionSamplingFrequencyIndex == 0xf) {
				reader.read(24); // extensionSamplingFrequency
			}
			audioObjectType = getAudioObjectType(reader);
			if (audioObjectType == 22) {
				reader.read(4); // extensionChannelConfiguration
			}
		}

		if (audioObjectType >= 1 && audioObjectType <= 23) {
			// GASpecificConfig

			reader.read(1); // frameLengthFlag
			std::uint8_t dependsOnCoreCoder = (std::uint8_t)reader.read(1);
			if (dependsOnCoreCoder) {
				reader.read(14); // coreCoderDelay
			}
			std::uint8_t extensionFlag = (std::uint8_t)reader.read(1);

			if (channelConfiguration == 0) {
				// program_config_element

				reader.read(4); // element_instance_tag
				reader.read(2); // object_type
				reader.read(4); // sampling_frequency_index
				std::uint8_t num_front_channel_elements = reader.read(4);
				std::uint8_t num_side_channel_elements = reader.read(4);
				std::uint8_t num_back_channel_elements = reader.read(4);
				std::uint8_t num_lfe_channel_elements = reader.read(2);
				std::uint8_t num_assoc_data_elements = reader.read(3);
				std::uint8_t num_valid_cc_elements = reader.read(4);

				std::uint8_t mono_mixdown_present = (std::uint8_t)reader.read(1);
				if (mono_mixdown_present == 1) {
					reader.read(4); // mono_mixdown_element_number
				}

				std::uint8_t stereo_mixdown_present = (std::uint8_t)reader.read(1);
				if (stereo_mixdown_present == 1) {
					reader.read(4); // stereo_mixdown_element_number
				}

				std::uint8_t matrix_mixdown_idx_present = (std::uint8_t)reader.read(1);
				if (matrix_mixdown_idx_present == 1) {
					reader.read(2); // matrix_mixdown_idx
					reader.read(1); // pseudo_surround_enable
				}

				for (unsigned int i = 0; i < num_front_channel_elements; i++) {
					reader.read(1); // front_element_is_cpe[i]
					reader.read(4); // front_element_tag_select[i]
				}

				for (unsigned int i = 0; i < num_side_channel_elements; i++) {
					reader.read(1); // side_element_is_cpe[i]
					reader.read(4); // side_element_tag_select[i]
				}

				for (unsigned int i = 0; i < num_back_channel_elements; i++) {
					reader.read(1); // back_element_is_cpe[i]
					reader.read(4); // back_element_tag_select[i]
				}

				for (unsigned int i = 0; i < num_lfe_channel_elements; i++) {
					reader.read(4); // lfe_element_tag_select[i]
				}

				for (unsigned int i = 0; i < num_assoc_data_elements; i++) {
					reader.read(4); // assoc_data_element_tag_select[i]
				}

				for (unsigned int i = 0; i < num_valid_cc_elements; i++) {
					reader.read(1); // cc_element_is_ind_sw[i]
					reader.read(4); // valid_cc_element_tag_select[i]
				}

				reader.align();

				std::uint8_t comment_field_bytes = (std::uint8_t)reader.read(8);
				reader.readBytes(0, comment_field_bytes); // comment_field_data
			}

			if (audioObjectType == 6 || audioObjectType == 20) {
				reader.read(3); // layerNr
			}

			if (extensionFlag) {
				if (audioObjectType == 22) {
					reader.read(5); // numOfSubFrame
					reader.read(11); // layer_length
				}

				if (audioObjectType == 17 || audioObjectType == 19 || audioObjectType == 20 || audioObjectType == 23) {
					reader.read(1); // aacSectionDataResilienceFlag
					reader.read(1); // aacScalefactorDataResilienceFlag
					reader.read(1); // aacSpectralDataResilienceFlag
				}

				reader.read(1); // extensionFlag3
			}
		}
	}
}