#include "FloatULP.h"

using namespace GB;

FloatULP::FloatULP()
	:fraction_denom_(FRACTION_BITS),
	fraction_numer_(FRACTION_BITS)
{

}


float FloatULP::float_from_bitfield(const fp32 &a) {
	int32_t exp{ 1 << (a.bitfield.exponent - 127) };
	const int32_t sign{ a.bitfield.sign ? -1 : 1 };

	uint32_t fraction{ static_cast<uint32_t>(a.bitfield.fraction) };
	uint32_t max_frac{};
	uint32_t max_shift{};
	const uint32_t last_bit{ FRACTION_BITS - 1 };

	for (uint32_t b{}; b < FRACTION_BITS; ++b) {

		const uint32_t bit_sel{ last_bit - b };
		uint32_t bit{ ((1 << bit_sel) & fraction) >> bit_sel };
		fraction_numer_[b] = bit;
		fraction_denom_[b] = bit * (b + 1);

		if (fraction_denom_[b] > max_frac) {
			max_shift = fraction_denom_[b];
		}
	}

	uint32_t num{};

	for (uint32_t b{}; b < FRACTION_BITS; ++b) {
		fraction_numer_[b] <<= (max_shift - fraction_denom_[b]);
		num += fraction_numer_[b];
	}

	exp *= sign;

	int32_t numerator{ static_cast<int32_t>(num) * exp };
	double frac{ static_cast<double>(numerator) / static_cast<double>(1 << max_shift) };
	frac += static_cast<double>(exp);
	return static_cast<float>(frac);
}
