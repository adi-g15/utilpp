#pragma once

#include <fstream>
#include <string>

namespace util{
    using path_type = std::string;  // plan to support UTF32 for file names

    std::string read_file(std::ifstream& fin) {
        std::string content;
        std::string tmp;

        if(fin) {
            while (std::getline(fin, tmp) && !fin.eof())
            {
                content.append(tmp);
                content.push_back('\n');
            }
        }

        return content;
    }

    std::string read_file(const path_type& path) {
        std::ifstream fin(path);
        return read_file(fin);
    }
}