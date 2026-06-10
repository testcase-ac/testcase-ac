#include "testlib.h"

#include <array>
#include <string>

using namespace std;

namespace {

constexpr long long kMaxValue = (1LL << 62);
constexpr __int128 kAnswerLimit = static_cast<__int128>(1LL << 62);

long long parseCanonicalNonnegative(const string& s, int queryIndex) {
    ensuref(!s.empty(), "missing x at query %d", queryIndex);
    ensuref(s == "0" || s[0] != '0', "x has leading zero at query %d: %s", queryIndex, s.c_str());

    __int128 value = 0;
    for (char c : s) {
        ensuref('0' <= c && c <= '9', "x contains non-digit at query %d: %s", queryIndex, s.c_str());
        value = value * 10 + (c - '0');
        ensuref(value <= kMaxValue, "x exceeds 2^62 at query %d: %s", queryIndex, s.c_str());
    }

    return static_cast<long long>(value);
}

int valueExponent(long long x, int queryIndex) {
    if (x == 0) {
        return -1;
    }

    ensuref((x & (x - 1)) == 0, "x is not zero or a power of two at query %d: %lld", queryIndex, x);
    return __builtin_ctzll(static_cast<unsigned long long>(x));
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 1000000, "Q");
    inf.readEoln();

    array<int, 63> counts{};
    int zeroCount = 0;
    __int128 total = 0;

    for (int i = 1; i <= q; ++i) {
        string token = inf.readToken("[+-][0-9]{1,19}", "query");
        inf.readEoln();

        char op = token[0];
        long long x = parseCanonicalNonnegative(token.substr(1), i);
        int exponent = valueExponent(x, i);

        if (op == '+') {
            if (exponent == -1) {
                ++zeroCount;
            } else {
                ++counts[exponent];
                total += x;
            }
        } else {
            if (exponent == -1) {
                ensuref(zeroCount > 0, "removing absent zero at query %d", i);
                --zeroCount;
            } else {
                ensuref(counts[exponent] > 0, "removing absent value at query %d: %lld", i, x);
                --counts[exponent];
                total -= x;
            }
        }

        ensuref(total <= 2 * kAnswerLimit - 1,
                "answer exceeds 2^62 after query %d", i);
    }

    inf.readEof();
}
