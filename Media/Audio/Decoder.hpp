#ifndef AUDIO_DECODER_HPP
#define AUDIO_DECODER_HPP

#include "System/EsDescriptor.hpp"

namespace Audio {
	class Decoder {
	public:
		Decoder(const System::EsDescriptor &esDescriptor);
	};
}
#endif