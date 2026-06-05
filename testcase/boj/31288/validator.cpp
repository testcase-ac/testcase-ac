#include "testlib.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <array>
#include <cstdint>
#include <string>

using boost::multiprecision::cpp_int;
using namespace std;

cpp_int parseDecimal(const string& value) {
    cpp_int result = 0;
    for (char ch : value) {
        result = result * 10 + (ch - '0');
    }
    return result;
}

cpp_int powMod(cpp_int base, cpp_int exponent, const cpp_int& mod) {
    cpp_int result = 1;
    base %= mod;
    while (exponent != 0) {
        if ((exponent & 1) != 0) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exponent >>= 1;
    }
    return result;
}

bool isPrime(const cpp_int& value) {
    if (value < 2) {
        return false;
    }

    static constexpr array<uint32_t, 32> bases = {
        2, 3, 5, 7, 11, 13, 17, 19,
        23, 29, 31, 37, 41, 43, 47, 53,
        59, 61, 67, 71, 73, 79, 83, 89,
        97, 101, 103, 107, 109, 113, 127, 131,
    };

    for (uint32_t prime : bases) {
        if (value == prime) {
            return true;
        }
        if (value % prime == 0) {
            return false;
        }
    }

    cpp_int oddPart = value - 1;
    int powersOfTwo = 0;
    while ((oddPart & 1) == 0) {
        oddPart >>= 1;
        ++powersOfTwo;
    }

    for (uint32_t base : bases) {
        if (cpp_int(base) >= value) {
            continue;
        }

        cpp_int witness = powMod(base, oddPart, value);
        if (witness == 1 || witness == value - 1) {
            continue;
        }

        bool passed = false;
        for (int i = 1; i < powersOfTwo; ++i) {
            witness = (witness * witness) % value;
            if (witness == value - 1) {
                passed = true;
                break;
            }
        }
        if (!passed) {
            return false;
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 3545, "T");
    inf.readEoln();

    int sumN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100, "N");
        inf.readSpace();
        string pToken = inf.readToken("[1-9][0-9]{0,99}", "P");
        inf.readEoln();

        sumN += n;
        ensuref(sumN <= 3545, "sum of N exceeds 3545 after case %d", tc);
        ensuref(static_cast<int>(pToken.size()) == n,
                "P must have exactly N digits in case %d: N=%d, len(P)=%d",
                tc, n, static_cast<int>(pToken.size()));

        cpp_int p = parseDecimal(pToken);
        ensuref(isPrime(p), "P must be prime in case %d", tc);
    }

    inf.readEof();
}
