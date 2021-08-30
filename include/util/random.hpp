#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>
#include <random>
#include <algorithm>
#include <vector>

namespace util{
    class Random{   //gives out non-zero values only
    public:
	static std::vector<uint32_t> random_bytes(size_t length) {
		std::vector<uint32_t> bytes(length);
		std::random_device device;
		for(auto &b: bytes) {
			b = device();
		}

		return bytes;
	}

        template<typename IntegerType = int>
        static std::vector<IntegerType> random_range(size_t length) {
            static_assert(std::is_integral_v<IntegerType>);

            std::vector<IntegerType> arr(length);
            std::generate(arr.begin(), arr.end(), Random::generator);

            return arr;
        }

        template<typename T = uint32_t> // so that, if signed BUT positive integer type is required, it can be given (it required narrowing conversions)
        static T random(){
            static_assert(std::is_integral_v<T>);

            return random<T>(0, std::numeric_limits<uint32_t>::max() );
        }

        template<typename T = uint32_t>
        static T random(uint32_t max){
            static_assert( std::is_integral_v<T> );

            return random<T>(0, max);
        }

        template<typename T = uint32_t>
        static T random(uint32_t min, uint32_t max){ // [`min`, `max`)     ie. max excluded
            static_assert( std::is_integral_v<T> );

            //static std::random_device Random::device;
            //static std::mt19937 Random::generator(Random::device());
            uint32_t num = std::random_device{}();
            // @future - Later use this generator too

            // @fix_me - Fix later-> won't work when (num-min) < 0
            //return static_cast<T>((((num-min)%max) + num ));
            return static_cast<T>((num%(max-min)) + min );
        }

        // static inline std::random_device device;
        // static inline std::mt19937 generator{ device() };
        // static inline std::mt19937 generator;    // these are absolutely fine with C++17, but github action using gcc 7.4 points out as error
        static std::mt19937 generator;
    };
}
