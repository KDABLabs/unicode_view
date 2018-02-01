#include "unicode_view"

#include <algorithm>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE("unicode_view")
{
    SECTION("simple comparison with a reference string") {
        const char     str8[]  = u8"€Hello𐐷7バイト以上の文字は規定されないため、0xFE、0xFF (BOM) に0xFEと0xFFを使用するUTF-16やUTF-32が、UTF-8と混同されることはない。UTF-16 is specified in the latest versions of both the international standard ISO/IEC 10646 and the Unicode Standard.";
        const char16_t str16[] = u"€Hello𐐷7バイト以上の文字は規定されないため、0xFE、0xFF (BOM) に0xFEと0xFFを使用するUTF-16やUTF-32が、UTF-8と混同されることはない。UTF-16 is specified in the latest versions of both the international standard ISO/IEC 10646 and the Unicode Standard.";
        const char32_t str32[] = U"€Hello𐐷7バイト以上の文字は規定されないため、0xFE、0xFF (BOM) に0xFEと0xFFを使用するUTF-16やUTF-32が、UTF-8と混同されることはない。UTF-16 is specified in the latest versions of both the international standard ISO/IEC 10646 and the Unicode Standard.";

        const auto safe_view8 = kdab::make_safe_unicode_view(std::begin(str8), std::end(str8));
        const auto safe_view16 = kdab::make_safe_unicode_view(std::begin(str16), std::end(str16));
        const auto safe_view32 = kdab::make_safe_unicode_view(std::begin(str32), std::end(str32));

        REQUIRE( std::equal(std::begin(safe_view8),  std::end(safe_view8),  std::begin(str32), std::end(str32)) );
        REQUIRE( std::equal(std::begin(safe_view16), std::end(safe_view16), std::begin(str32), std::end(str32)) );
        REQUIRE( std::equal(std::begin(safe_view32), std::end(safe_view32), std::begin(str32), std::end(str32)) );

        const auto trusted_view8 = kdab::make_trusted_unicode_view(std::begin(str8), std::end(str8));
        const auto trusted_view16 = kdab::make_trusted_unicode_view(std::begin(str16), std::end(str16));
        const auto trusted_view32 = kdab::make_trusted_unicode_view(std::begin(str32), std::end(str32));

        REQUIRE( std::equal(std::begin(trusted_view8),  std::end(trusted_view8),  std::begin(str32), std::end(str32)) );
        REQUIRE( std::equal(std::begin(trusted_view16), std::end(trusted_view16), std::begin(str32), std::end(str32)) );
        REQUIRE( std::equal(std::begin(trusted_view32), std::end(trusted_view32), std::begin(str32), std::end(str32)) );
    }

    SECTION("UTF-8 decoding") {
        SECTION("Valid UTF-8") {

        }

        SECTION("Illegal code units") {

        }

        SECTION("Overlong sequence") {

        }

        SECTION("Illegal code points") {

        }
    }

    SECTION("UTF-16 decoding") {
        SECTION("Valid UTF-16") {

        }

        SECTION("Illegal code units") {

        }

        SECTION("Illegal code points") {

        }
    }
}
