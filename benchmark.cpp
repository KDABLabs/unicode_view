#include "unicode_view"
#include "benchmark_util.h"

#include <chrono>
#include <iostream>

enum {
    BENCH_COUNT = 10000000
};

template <typename T>
void benchMarkSafe(const T *codeUnits)
{
    const auto length = std::char_traits<T>::length(codeUnits);
    using clock = std::chrono::steady_clock;
    auto view = kdab::make_safe_unicode_view(codeUnits, codeUnits + length);

    auto start = clock::now();
    for (int i = 0; i < BENCH_COUNT; ++i) {
        for (auto codePoint : view)
          escape(&codePoint);
    }
    clobber();
    auto stop = clock::now();
    std::cout << "Benchmarking (safe) " << length << " code units of utf" << 8 * sizeof(T) << " took: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms " << std::endl;
}

template <typename T>
void benchMarkTrusted(const T *codeUnits)
{
    const auto length = std::char_traits<T>::length(codeUnits);
    using clock = std::chrono::steady_clock;
    auto view = kdab::make_trusted_unicode_view(codeUnits, codeUnits + length);

    auto start = clock::now();
    for (int i = 0; i < BENCH_COUNT; ++i) {
        for (auto codePoint : view)
          escape(&codePoint);
    }
    clobber();
    auto stop = clock::now();
    std::cout << "Benchmarking (trusted) " << length << " code units of utf" << 8 * sizeof(T) << " took: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms " << std::endl;
}

int main()
{
    const char     str8[]  = u8"€Hello𐐷7バイト以上の文字は規定されないため、0xFE、0xFF (BOM) に0xFEと0xFFを使用するUTF-16やUTF-32が、UTF-8と混同されることはない。UTF-16 is specified in the latest versions of both the international standard ISO/IEC 10646 and the Unicode Standard.";
    const char16_t str16[] = u"€Hello𐐷7バイト以上の文字は規定されないため、0xFE、0xFF (BOM) に0xFEと0xFFを使用するUTF-16やUTF-32が、UTF-8と混同されることはない。UTF-16 is specified in the latest versions of both the international standard ISO/IEC 10646 and the Unicode Standard.";
    const char32_t str32[] = U"€Hello𐐷7バイト以上の文字は規定されないため、0xFE、0xFF (BOM) に0xFEと0xFFを使用するUTF-16やUTF-32が、UTF-8と混同されることはない。UTF-16 is specified in the latest versions of both the international standard ISO/IEC 10646 and the Unicode Standard.";

    std::cout << "benchmarking short strings, safe iterator" << std::endl;
    benchMarkSafe(str8);
    benchMarkSafe(str16);
    benchMarkSafe(str32);

    std::cout << "benchmarking short strings, trusted iterator" << std::endl;
    benchMarkTrusted(str8);
    benchMarkTrusted(str16);
    benchMarkTrusted(str32);
}
