#include "testlib.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <algorithm>
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

cpp_int absDiff(const cpp_int& a, const cpp_int& b) {
    return a > b ? a - b : b - a;
}

cpp_int gcd(cpp_int a, cpp_int b) {
    while (b != 0) {
        cpp_int r = a % b;
        a = b;
        b = r;
    }
    return a;
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

bool isProbablePrime(const cpp_int& value) {
    if (value < 2) {
        return false;
    }

    static constexpr array<uint32_t, 32> smallBases = {
        2, 3, 5, 7, 11, 13, 17, 19,
        23, 29, 31, 37, 41, 43, 47, 53,
        59, 61, 67, 71, 73, 79, 83, 89,
        97, 101, 103, 107, 109, 113, 127, 131,
    };

    for (uint32_t prime : smallBases) {
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

    for (uint32_t baseValue : smallBases) {
        if (cpp_int(baseValue) >= value) {
            continue;
        }

        cpp_int witness = powMod(baseValue, oddPart, value);
        if (witness == 1 || witness == value - 1) {
            continue;
        }

        bool maybePrime = false;
        for (int i = 1; i < powersOfTwo; ++i) {
            witness = (witness * witness) % value;
            if (witness == value - 1) {
                maybePrime = true;
                break;
            }
        }
        if (!maybePrime) {
            return false;
        }
    }

    return true;
}

cpp_int rhoStep(const cpp_int& x, const cpp_int& c, const cpp_int& mod) {
    return (x * x + c) % mod;
}

cpp_int pollardRho(const cpp_int& value) {
    if (value % 2 == 0) {
        return 2;
    }

    static constexpr array<uint32_t, 12> seeds = {
        1, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
    };

    for (uint32_t seed : seeds) {
        cpp_int c = seed;
        cpp_int x = 2 + seed;
        cpp_int y = x;
        cpp_int factor = 1;

        while (factor == 1) {
            x = rhoStep(x, c, value);
            y = rhoStep(rhoStep(y, c, value), c, value);
            factor = gcd(absDiff(x, y), value);
        }

        if (factor != value) {
            return factor;
        }
    }

    ensuref(false, "could not factor P quickly enough to validate semiprimality");
    return 1;
}

int primeFactorCount(cpp_int value, int limit) {
    if (value == 1) {
        return 0;
    }
    if (limit < 0) {
        return limit;
    }
    if (isProbablePrime(value)) {
        return 1;
    }

    cpp_int factor = pollardRho(value);
    int left = primeFactorCount(factor, limit);
    int right = primeFactorCount(value / factor, limit - left);
    return left + right;
}

bool isSemiprime(cpp_int value) {
    return primeFactorCount(value, 2) == 2;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string pToken = inf.readToken("[1-9][0-9]{0,99}", "P");
    cpp_int p = parseDecimal(pToken);
    ensuref(p >= 4, "P must be at least 4");

    inf.readSpace();
    inf.readInt(2, 1000000, "K");
    inf.readEoln();
    inf.readEof();

    ensuref(isSemiprime(p), "P must be the product of two primes");
}
