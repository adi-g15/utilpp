#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace util {
    using path_type = std::string; // plan to support UTF32 for file names

    std::string read_file(std::ifstream &fin) {
        std::string content;
        std::string tmp;

        if (fin) {
            while (std::getline(fin, tmp) && !fin.eof()) {
                content.append(tmp);
                content.push_back('\n');
            }
        }

        return content;
    }

    std::string read_file(const path_type &path) {
        std::ifstream fin(path);
        return read_file(fin);
    }

    /*
    * @brief Reads n bytes from given offset (default 0)
    * @note the file reference will be modified
    * */
    std::vector<char> get_n_bytes_from_file(std::ifstream &file, uint64_t num_bytes,
                                            uint64_t offset) {
        std::vector<char> buffer(num_bytes);

        // auto old_offset = file.tellg();

        file.seekg(offset);
        file.read(buffer.data(), num_bytes);

        // file.seekg( old_offset );	// restore original offset

        return buffer;
    }
} // namespace util
