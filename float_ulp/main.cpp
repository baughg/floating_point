#include <iostream>
#include "FloatULP.h"

using namespace GB;

int main() {
	fp32 a{ };
	a.value = 1.54321f;

	FloatULP f{};
	float b{ f.float_from_bitfield(a) };
	return 0;
}