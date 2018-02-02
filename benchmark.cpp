#include "unicode_view"
#include "benchmark_util.h"

#include <chrono>
#include <iostream>
#include <string>

enum {
    BENCH_COUNT = 10000000
};

template <typename String>
void benchMarkSafe(const String &string, int maxCount = BENCH_COUNT)
{
    using clock = std::chrono::steady_clock;
    auto view = kdab::make_safe_unicode_view(string.begin(), string.end());

    auto start = clock::now();
    for (int i = 0; i < maxCount; ++i) {
        for (auto codePoint : view)
          escape(&codePoint);
    }
    clobber();
    auto stop = clock::now();
    std::cout << "Benchmarking (safe) " << string.size() << " code units of utf" << 8 * sizeof(typename String::value_type) << " took: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms " << std::endl;
}

template <typename String>
void benchMarkTrusted(const String &string, int maxCount = BENCH_COUNT)
{
    using clock = std::chrono::steady_clock;
    auto view = kdab::make_trusted_unicode_view(string.begin(), string.end());

    auto start = clock::now();
    for (int i = 0; i < maxCount; ++i) {
        for (auto codePoint : view)
          escape(&codePoint);
    }
    clobber();
    auto stop = clock::now();
    std::cout << "Benchmarking (safe) " << string.size() << " code units of utf" << 8 * sizeof(typename String::value_type) << " took: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms " << std::endl;
}

enum {
    BULK_DATA_COPIES = 100000,
    BULK_DATA_TEST_COUNT = 100
};

template <typename String>
String prepareBulkData(const String &input)
{
    String result;
    result.reserve(input.size() * BULK_DATA_COPIES);
    for (int i = 0; i < BULK_DATA_COPIES; ++i)
        std::copy(input.begin(), input.end(), std::back_inserter(result));

    return result;
}

template <typename String>
void benchmarkSafeBulkData(const String &string)
{
    String data = prepareBulkData(string);
    benchMarkSafe(data, BULK_DATA_TEST_COUNT);
}

template <typename String>
void benchmarkTrustedBulkData(const String &string)
{
    String data = prepareBulkData(string);
    benchMarkTrusted(data, BULK_DATA_TEST_COUNT);
}

int main()
{
    std::string str8  = u8"€Hello𐐷7バイト以上の文字は規定されないため、0xFE、0xFF (BOM) に0xFEと0xFFを使用するUTF-16やUTF-32が、UTF-8と混同されることはない。UTF-16 is specified in the latest versions of both the international standard ISO/IEC 10646 and the Unicode Standard.";
    std::u16string str16 = u"€Hello𐐷7バイト以上の文字は規定されないため、0xFE、0xFF (BOM) に0xFEと0xFFを使用するUTF-16やUTF-32が、UTF-8と混同されることはない。UTF-16 is specified in the latest versions of both the international standard ISO/IEC 10646 and the Unicode Standard.";
    std::u32string str32 = U"€Hello𐐷7バイト以上の文字は規定されないため、0xFE、0xFF (BOM) に0xFEと0xFFを使用するUTF-16やUTF-32が、UTF-8と混同されることはない。UTF-16 is specified in the latest versions of both the international standard ISO/IEC 10646 and the Unicode Standard.";

    std::cout << "benchmarking short strings, safe iterator" << std::endl;
    benchMarkSafe(str8);
    benchMarkSafe(str16);
    benchMarkSafe(str32);

    std::cout << "benchmarking short strings, trusted iterator" << std::endl;
    benchMarkTrusted(str8);
    benchMarkTrusted(str16);
    benchMarkTrusted(str32);

    std::cout << "benchmarking long strings, safe iterator" << std::endl;
    benchmarkSafeBulkData(str8);
    benchmarkSafeBulkData(str16);
    benchmarkSafeBulkData(str32);

    std::cout << "benchmarking long strings, trusted iterator" << std::endl;
    benchmarkTrustedBulkData(str8);
    benchmarkTrustedBulkData(str16);
    benchmarkTrustedBulkData(str32);
}
