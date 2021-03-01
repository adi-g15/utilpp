#pragma once
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>


namespace util
{
    std::string exec(const char* cmd);
}

// https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
inline std::string util::exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(
#ifdef _WIN32
        _popen(cmd, "r"),
        _pclose
#else
        popen(cmd, "r"),
        pclose
#endif
    );
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

// https://stackoverflow.com/questions/52164723/how-to-execute-a-command-and-get-return-code-stdout-and-stderr-of-command-in-c
std::pair<std::string, int> exec_ret_code(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    int return_code = -1;
    auto pclose_wrapper = [&return_code](FILE* cmd){
#ifdef _WIN32
        return_code = _pclose(cmd);
#else
        return_code = pclose(cmd);
#endif
    };
    { // scope is important, have to make sure the ptr goes out of scope first
    const std::unique_ptr<FILE, decltype(pclose_wrapper)> pipe(
#ifdef _WIN32
        _popen(cmd, "r"),
#else
        popen(cmd, "r"),
#endif
        pclose_wrapper
    );
    if (pipe) {
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
    }
    }
    return std::make_pair(result, return_code);
}
