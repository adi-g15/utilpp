#include <algorithm>
#include <vector>
#include <random>

template<typename T>
std::vector<T>&& get_random_sequence(int length) {
	static_assert(std::is_integral_v<T>,
		"Currently random sequences are only supported for integral types" );

	std::vector<T> v{ length };

	std::generate(v.begin(), v.end(), std::random_device{});

	return std::move(v);
}
