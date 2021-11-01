#pragma once

#include <chrono>
#include <iostream>
#include <thread>

namespace util {
struct timer;

void pause(float sec);
} // namespace util

// DEFINTIONS
// Source: https://github.com/Const-me/SimdIntroArticle/blob/master/common.h
// A wrapper around std::chrono::high_resolution_clock which starts measuring
// time once constructed, and reports elapsed time
class Stopwatch {
    using Clock = std::chrono::high_resolution_clock;
    const Clock::time_point start;

    template <class _Period> double elapsed() const {
        const Clock::time_point finish = Clock::now();
        const auto timespan = finish - start;
        return std::chrono::duration_cast<
                   std::chrono::duration<double, _Period>>(timespan)
            .count();
    }

  public:
    Stopwatch() : start(Clock::now()) {}

    // Milliseconds since constructed
    double elapsedMilliseconds() const { return elapsed<std::milli>(); }

    // Microseconds since constructed
    double elapsedMicroseconds() const { return elapsed<std::micro>(); }
};

// A wrapper around std::chrono::high_resolution_clock which prints the time
// passed between constructor and destructor.
class PerfTimer {
    const char *const what;
    const Stopwatch stopwatch;

  public:
    PerfTimer(const char *measure) : what(measure) {}

    ~PerfTimer() {
        const double ms = stopwatch.elapsedMilliseconds();
        printf("%s: %g ms\n", what, ms);
    }
};
#define MEASURE_THIS_FUNCTION()                                                \
    PerfTimer __time { __func__ }

void util::pause(float seconds) {
    std::this_thread::sleep_for(
        std::chrono::milliseconds(static_cast<long>(seconds * 1000)));
}
