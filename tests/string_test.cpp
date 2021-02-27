#include <catch2/catch.hpp>

#include "util/string.hpp"

TEST_CASE("starts_with test", "[string]") {
    REQUIRE( util::starts_with("aditya", "adi") == true );
    REQUIRE( util::starts_with(" hi", " ") == true );
    REQUIRE( util::starts_with("checking it", "check") == true );
    REQUIRE( util::starts_with("false", "true") == false );
    REQUIRE( util::starts_with("fa", "false") == false );
    REQUIRE( util::starts_with("trial string", "str") == false );
}
