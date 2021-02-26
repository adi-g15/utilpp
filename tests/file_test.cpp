#include <catch2/catch.hpp>

#include "util/file.hpp"

#include <filesystem>
#include <fstream>
#include <string>

TEST_CASE("Files utilities", "[read]") {
    std::string random_content = "Namaste Tests\n"
                                    "This is the content\n"
                                    "\n"
                                    "After empty line\n"
                                    "Test this\n"
                                    "";

    constexpr auto TEST_FILE = "tests_file.txt";
    std::ofstream fout(TEST_FILE);
    SECTION("Writing random content to a file") {
        fout << random_content;
        fout.close();
    }

    auto file_contents = util::read_file(TEST_FILE);
    std::filesystem::remove(TEST_FILE);

    REQUIRE(file_contents == random_content);
}
