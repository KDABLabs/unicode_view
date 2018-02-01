#include <iostream>

#include "unicode_view"
#include "benchmark_util.h"

template <typename T>
void printCodePoints(const T *codeUnits)
{
    for (auto codePoint : kdab::make_safe_unicode_view(codeUnits, codeUnits + std::char_traits<T>::length(codeUnits)))
        std::cout << codePoint << " ";
    std::cout << std::endl;

    for (auto codePoint : kdab::make_trusted_unicode_view(codeUnits, codeUnits + std::char_traits<T>::length(codeUnits)))
        std::cout << codePoint << " ";
    std::cout << std::endl;
}

int main()
{
    const char     str8[]  = u8"€Hello𐐷7バイト以上の文字は規定されないため、0xFE、0xFF (BOM) に0xFEと0xFFを使用するUTF-16やUTF-32が、UTF-8と混同されることはない。UTF-16 is specified in the latest versions of both the international standard ISO/IEC 10646 and the Unicode Standard.";
    const char16_t str16[] = u"€Hello𐐷7バイト以上の文字は規定されないため、0xFE、0xFF (BOM) に0xFEと0xFFを使用するUTF-16やUTF-32が、UTF-8と混同されることはない。UTF-16 is specified in the latest versions of both the international standard ISO/IEC 10646 and the Unicode Standard.";
    const char32_t str32[] = U"€Hello𐐷7バイト以上の文字は規定されないため、0xFE、0xFF (BOM) に0xFEと0xFFを使用するUTF-16やUTF-32が、UTF-8と混同されることはない。UTF-16 is specified in the latest versions of both the international standard ISO/IEC 10646 and the Unicode Standard.";
    const char     *_str8  = u8"€Hello𐐷";
    const char16_t *_str16 = u"€Hello𐐷";
    const char32_t *_str32 = U"€Hello𐐷";

    std::cout << "Size in memory " << sizeof str8 << " " <<  sizeof str16 << " " <<  sizeof str32 << std::endl;
    std::cout << "Test unicode_view" << std::endl;
    std::cout << std::hex;
    printCodePoints(str8);
    printCodePoints(str16);
    printCodePoints(str32);
    printCodePoints(_str8);
    printCodePoints(_str16);
    printCodePoints(_str32);
}
