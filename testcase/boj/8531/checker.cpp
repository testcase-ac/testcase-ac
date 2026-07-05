#include "testlib.h"

#include <algorithm>
#include <climits>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

using ull = unsigned long long;

ull n;
ull a;

struct Fraction {
    ull numerator;
    ull denominator;

    bool operator<(const Fraction& other) const {
        return numerator == other.numerator ? denominator < other.denominator : numerator < other.numerator;
    }

    bool operator==(const Fraction& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }
};

bool inInterval(Fraction fraction) {
    __uint128_t scaledNumerator = static_cast<__uint128_t>(fraction.numerator) * n * n;
    __uint128_t lower = static_cast<__uint128_t>(a) * fraction.denominator;
    __uint128_t upper = static_cast<__uint128_t>(a + 1) * fraction.denominator;
    return lower <= scaledNumerator && scaledNumerator <= upper;
}

vector<Fraction> readAnswer(InStream& stream, ull expectedCount, bool compareCount) {
    ull count = stream.readUnsignedLong(0, ULLONG_MAX, "fraction count");
    stream.readEoln();

    if (compareCount && count != expectedCount) {
        stream.quitf(_wa,
                     "reported %llu fraction(s), but jury reported %llu",
                     count,
                     expectedCount);
    }

    set<Fraction> seen;
    vector<Fraction> fractions;
    fractions.reserve(static_cast<size_t>(min<ull>(count, 1000000ULL)));

    for (ull i = 0; i < count; ++i) {
        ull numerator = stream.readUnsignedLong(1, ULLONG_MAX, format("fraction[%llu].numerator", i + 1).c_str());
        stream.readSpace();
        ull denominator = stream.readUnsignedLong(1, n, format("fraction[%llu].denominator", i + 1).c_str());
        stream.readEoln();

        Fraction fraction{numerator, denominator};
        if (gcd(numerator, denominator) != 1) {
            stream.quitf(_wa,
                         "fraction %llu/%llu is not simplified",
                         numerator,
                         denominator);
        }
        if (!inInterval(fraction)) {
            stream.quitf(_wa,
                         "fraction %llu/%llu is outside the required interval",
                         numerator,
                         denominator);
        }
        if (!seen.insert(fraction).second) {
            stream.quitf(_wa,
                         "fraction %llu/%llu is repeated",
                         numerator,
                         denominator);
        }
        fractions.push_back(fraction);
    }

    stream.readEof();
    sort(fractions.begin(), fractions.end());
    return fractions;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readUnsignedLong(1, 4294967295ULL, "n");
    a = inf.readUnsignedLong(1, 18446744073709551614ULL, "a");

    vector<Fraction> jury = readAnswer(ans, 0, false);
    vector<Fraction> participant = readAnswer(ouf, jury.size(), true);

    if (participant != jury) {
        quitf(_wa, "participant fractions differ from jury fractions");
    }

    quitf(_ok, "%d fraction(s)", (int)jury.size());
}
