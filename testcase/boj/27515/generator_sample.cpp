#include "testlib.h"

#include <array>
#include <string>
#include <vector>

using namespace std;

namespace {

constexpr long long kLimit = (1LL << 62);

long long valueFromExponent(int exponent) {
    return 1LL << exponent;
}

string valueText(int exponent) {
    if (exponent == -1) {
        return "0";
    }
    return to_string(valueFromExponent(exponent));
}

int choosePresentExponent(const array<int, 63>& counts, int zeroCount) {
    vector<int> present;
    if (zeroCount > 0) {
        present.push_back(-1);
    }
    for (int i = 0; i <= 62; ++i) {
        if (counts[i] > 0) {
            present.push_back(i);
        }
    }
    return rnd.any(present);
}

int chooseAddExponent(int mode) {
    if (mode == 0) {
        return rnd.next(0, 8);
    }
    if (mode == 1) {
        return rnd.next(0, 4);
    }
    if (mode == 2 && rnd.next(100) < 35) {
        return -1;
    }
    if (mode == 3) {
        return rnd.any(vector<int>{0, 1, 2, 60, 61, 62});
    }
    if (rnd.next(100) < 15) {
        return -1;
    }
    return rnd.next(0, 12);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int q = rnd.next(8, mode == 3 ? 35 : 70);

    vector<pair<char, int>> queries;
    array<int, 63> counts{};
    int zeroCount = 0;
    __int128 total = 0;

    for (int i = 0; i < q; ++i) {
        bool hasPresent = zeroCount > 0;
        for (int c : counts) {
            hasPresent = hasPresent || c > 0;
        }

        bool remove = hasPresent && rnd.next(100) < (mode == 2 ? 45 : 25);
        if (mode == 1 && i > q / 3) {
            remove = hasPresent && rnd.next(100) < 55;
        }

        if (remove) {
            int exponent = choosePresentExponent(counts, zeroCount);
            queries.push_back({'-', exponent});
            if (exponent == -1) {
                --zeroCount;
            } else {
                --counts[exponent];
                total -= valueFromExponent(exponent);
            }
            continue;
        }

        int exponent = chooseAddExponent(mode);
        if (exponent >= 0 && total + valueFromExponent(exponent) > 2 * static_cast<__int128>(kLimit) - 1) {
            exponent = rnd.next(100) < 50 ? -1 : rnd.next(0, 12);
        }
        if (exponent >= 0 && total + valueFromExponent(exponent) > 2 * static_cast<__int128>(kLimit) - 1) {
            exponent = -1;
        }

        queries.push_back({'+', exponent});
        if (exponent == -1) {
            ++zeroCount;
        } else {
            ++counts[exponent];
            total += valueFromExponent(exponent);
        }
    }

    println(static_cast<int>(queries.size()));
    for (auto [op, exponent] : queries) {
        println(string(1, op) + valueText(exponent));
    }

    return 0;
}
