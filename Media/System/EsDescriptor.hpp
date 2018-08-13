#ifndef SYSTEM_ES_DESCRIPTOR_HPP
#define SYSTEM_ES_DESCRIPTOR_HPP

#include <cstdint>
#include <vector>

namespace System {
	class EsDescriptor {
	public:
		EsDescriptor() = default;
		EsDescriptor(const std::vector<std::uint8_t> &buffer);

		const std::vector<uint8_t> &decoderConfigDescriptor() const;

	private:
		std::vector<std::uint8_t> mDecoderConfigDescriptor;
	};
}
#endif