#pragma once
#include <cstdint>
#include <vector>

namespace GB {
	struct float32 {
		int32_t fraction : 23;
		int32_t exponent : 8;
		int32_t sign : 1;
	};

	union fp32 {
		float32 bitfield;
		float value;
	};

	const uint32_t FRACTION_BITS{ 23 };

	class FloatULP
	{
	public:
		FloatULP();
		float float_from_bitfield(const fp32 &a);
	private:
		fp32 number_{};
		std::vector<uint32_t> fraction_denom_;
		std::vector<uint32_t> fraction_numer_;
	};
}

