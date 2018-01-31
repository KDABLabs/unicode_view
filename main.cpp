#include <iostream>
#include <chrono>

#include "unicode_view"
#include "util.h"

using namespace std;

template <typename T>
void printCodePoints(const T *codeUnits)
{
    for (auto codePoint : kdab::make_unicode_view(codeUnits, codeUnits + std::char_traits<T>::length(codeUnits)))
        std::cout << codePoint << " ";
    std::cout << std::endl;
}

enum {
    BENCH_COUNT = 10000000
};

template <typename T>
void benchMark(const T *codeUnits)
{
    const auto length = std::char_traits<T>::length(codeUnits);
    using clock = chrono::steady_clock;
    auto start = clock::now();
    for (int i = 0; i < BENCH_COUNT; ++i) {
        auto view = kdab::make_unicode_view(codeUnits, codeUnits + length);
        for (auto codePoint : view)
          escape(&codePoint);
//        auto sz = view.size();
//        escape(&sz);
    }
    clobber();
    auto stop = clock::now();
    cout << dec << "Benchmarking " << length << " code uints of utf" << 8 * sizeof(T) << " took:" << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << "ms " << endl;
}

int main()
{
    const char     str8[]  = u8"€Hello𐐷7バイト以上の文字は規定されないため、0xFE、0xFF (BOM) に0xFEと0xFFを使用するUTF-16やUTF-32が、UTF-8と混同されることはない。UTF-16 is specified in the latest versions of both the international standard ISO/IEC 10646 and the Unicode Standard.";
    const char16_t str16[] = u"€Hello𐐷7バイト以上の文字は規定されないため、0xFE、0xFF (BOM) に0xFEと0xFFを使用するUTF-16やUTF-32が、UTF-8と混同されることはない。UTF-16 is specified in the latest versions of both the international standard ISO/IEC 10646 and the Unicode Standard.";
    const char32_t str32[] = U"€Hello𐐷7バイト以上の文字は規定されないため、0xFE、0xFF (BOM) に0xFEと0xFFを使用するUTF-16やUTF-32が、UTF-8と混同されることはない。UTF-16 is specified in the latest versions of both the international standard ISO/IEC 10646 and the Unicode Standard.";
    const char     *_str8  = u8"€Hello𐐷";
    const char16_t *_str16 = u"€Hello𐐷";
    const char32_t *_str32 = U"€Hello𐐷";

    cout << "Size in memory " << sizeof str8 << " " <<  sizeof str16 << " " <<  sizeof str32 << endl << hex;
    cout << "Test unicode_view" << endl;
    printCodePoints(str8);
    printCodePoints(str16);
    printCodePoints(str32);
    printCodePoints(_str8);
    printCodePoints(_str16);
    printCodePoints(_str32);

    cout << "benchmarking ..." << endl;
    benchMark(str8);
    benchMark(str16);
    benchMark(str32);

    return 0;
}
