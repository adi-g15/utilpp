#include <vector>
#include <array>
#include <queue>
#include <cassert>

namespace util {
    using Array = std::vector<int>;
    // template<typename Array>    // support both std::array, std::vector
    void radix_sort(Array& arr);

    void radix_sort_bucket(std::vector<int>& arr);

    void counting_sort(Array& arr);

    namespace _impl {
        template<typename IntegerType>
        inline int num_digits(IntegerType num) {    // should be pass by value
            static_assert(std::is_integral_v<IntegerType>);

            int count = 0;
            while (num > 0)
            {
                ++count;
                num /= 10;
            }
            return count;
        }
    }
}

using Array = std::vector<int>;
// template<typename Array>    // support both std::array, std::vector
inline void util::radix_sort(Array& arr) {
    // using counting sort, (not buckets)
    std::array<int, 10> counts; // 0-9
    Array output_array(arr.size());

    int div = 10;

    do {
        std::fill(counts.begin(), counts.end(), 0);
        for (auto &&i : arr)
        {
            ++counts[(i%div)/(div/10)];
        }

        // take the prefix sum
        for (auto i = 1; i < counts.size(); i++)
        {
            counts[i] += counts[i-1];
        }

        for(auto iter = arr.rbegin(); iter != arr.rend(); ++iter) {
            auto& num = *iter;

            output_array[--counts[(num%div)/(div/10)]] = num;
        }
        std::swap(arr, output_array);

        div *= 10;
    } while ( counts[0] == arr.size() );
}

inline void util::radix_sort_bucket(std::vector<int>& arr) {
    // uses buckets to sort it
    std::array<
        std::queue<int>,
        10  // 0-9 digit
    > buckets;

    int div = 10;   // divisor, to get the relevant digit

    do {
        for (auto &&i : arr)
        {
            buckets[(i%div)/(div/10)].push(i);
        }

        div *= 10;

        size_t index = 0;
        for (auto &&bucket : buckets)
        {
            while (!bucket.empty())
            {
                arr[index++] = bucket.front();
                bucket.pop();
            }
        }
        assert(index == arr.size());    // the number of contents in all buckets MUST BE the same as number of elements in the array, logically it will be true here
    }while (buckets[0].size() != arr.size());    // when div has more digits than the max number, then all numbers will end up in the 0th index bucket

}

void counting_sort(Array& arr, const bool FORCE_RUN = false) {
    int counter_length = *std::max_element(arr.begin(), arr.end());

    if(!FORCE_RUN && counter_length > 1000) {
        assert(false);
        return;
    }

    std::vector<uint32_t> count(counter_length); // all elements 0 for non-class type
    for (auto &&i : arr)
    {
        count[i]++;
    }

    size_t index = 0;
    for (auto i = 0; i < count.size(); i++)
    {
        while (count[i]-- != 0) // invariant- count[i] >= 0
        {
            arr[index++] = i;
        }
    }
}
