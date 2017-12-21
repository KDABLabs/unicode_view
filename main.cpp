#include <iostream>
#include <chrono>

#include "unicode_view"

using namespace std;

template <typename T>
void printCodePoints(const T *codeUints)
{
    for (auto codePoint : to_unicode_view(codeUints))
        cout << codePoint << " ";
    cout << endl;
}

template <typename T, size_t N>
void printCodePoints(const T (&codeUints)[N])
{
    for (auto codePoint : to_unicode_view(codeUints, N - 1))
        cout << codePoint << " ";
    cout << endl;
}

enum {
    BENCH_COUNT = 10000000
};

template <typename T, size_t N>
void benchMark(const T (&codeUints)[N])
{
    using clock = chrono::high_resolution_clock;
    auto start = clock::now();
    uint64_t sum = 0;
    for (int i = 0; i < BENCH_COUNT; ++i) {
        auto view = to_unicode_view(codeUints, N - 1);
        for (auto codePoint : view)
            sum += codePoint;
        sum += view.size();
    }
    auto stop = clock::now();
    cout << dec << "Benchmarking " << N - 1 << " code uints of utf" << 8 * sizeof(T) << " took:" << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << "ms" << endl;
}

int main()
{
    char     str8[]  =  "€Hello𐐷7バイト以上の文字は規定されないため、0xFE、0xFF (BOM) に0xFEと0xFFを使用するUTF-16やUTF-32が、UTF-8と混同されることはない。UTF-16 is specified in the latest versions of both the international standard ISO/IEC 10646 and the Unicode Standard.";
    char16_t str16[] = u"€Hello𐐷7バイト以上の文字は規定されないため、0xFE、0xFF (BOM) に0xFEと0xFFを使用するUTF-16やUTF-32が、UTF-8と混同されることはない。UTF-16 is specified in the latest versions of both the international standard ISO/IEC 10646 and the Unicode Standard.";
    char32_t str32[] = U"€Hello𐐷7バイト以上の文字は規定されないため、0xFE、0xFF (BOM) に0xFEと0xFFを使用するUTF-16やUTF-32が、UTF-8と混同されることはない。UTF-16 is specified in the latest versions of both the international standard ISO/IEC 10646 and the Unicode Standard.";
    const char     *_str8  =  "€Hello𐐷";
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
