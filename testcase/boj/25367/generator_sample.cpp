#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using int64 = long long;

const int64 LIM = 1000000000000000000LL;

int64 randomMask(int maxBit, int wantBits) {
    vector<int> bits;
    for (int bit = 0; bit <= maxBit; ++bit) bits.push_back(bit);
    shuffle(bits.begin(), bits.end());

    int64 value = 0;
    wantBits = min(wantBits, (int)bits.size());
    for (int i = 0; i < wantBits; ++i) value |= 1LL << bits[i];
    return value;
}

pair<int64, int64> solvableQuery() {
    int maxBit = rnd.next(0, 58);
    int yBits = rnd.next(0, min(12, maxBit + 1));
    int64 y = randomMask(maxBit, yBits);

    vector<int> freeBits;
    for (int bit = 0; bit <= maxBit; ++bit)
        if (((y >> bit) & 1LL) == 0) freeBits.push_back(bit);
    shuffle(freeBits.begin(), freeBits.end());

    int64 carry = 0;
    int take = freeBits.empty() ? 0 : rnd.next(0, min(10, (int)freeBits.size()));
    for (int i = 0; i < take; ++i) carry |= 1LL << freeBits[i];

    int64 x = y + 2 * carry;
    if (x > LIM) return {0, 0};
    return {x, y};
}

pair<int64, int64> impossibleQuery() {
    int type = rnd.next(0, 2);
    if (type == 0) {
        int64 y = rnd.next(1LL, LIM);
        int64 x = rnd.next(0LL, y - 1);
        return {x, y};
    }
    if (type == 1) {
        int64 y = rnd.next(0LL, LIM - 1);
        int64 x = y + 1;
        return {x, y};
    }

    int bit = rnd.next(0, 58);
    int64 y = 1LL << bit;
    int64 carry = y;
    int64 x = y + 2 * carry;
    return {x, y};
}

pair<int64, int64> randomQuery() {
    int type = rnd.next(0, 3);
    if (type == 0) return {rnd.next(0LL, 1000LL), rnd.next(0LL, 1000LL)};
    if (type == 1) return {rnd.next(LIM - 1000000LL, LIM), rnd.next(0LL, 1000000LL)};
    if (type == 2) return {rnd.next(0LL, 1000000LL), rnd.next(LIM - 1000000LL, LIM)};
    return {rnd.next(0LL, LIM), rnd.next(0LL, LIM)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int64, int64>> queries = {
        {0, 0},
        {1, 0},
        {1, 1},
        {LIM, LIM},
        {LIM, 0},
        {0, LIM},
    };

    int q = rnd.next(12, 30);
    while ((int)queries.size() < q) {
        int mode = rnd.next(0, 2);
        if (mode == 0) queries.push_back(solvableQuery());
        else if (mode == 1) queries.push_back(impossibleQuery());
        else queries.push_back(randomQuery());
    }
    shuffle(queries.begin(), queries.end());

    println((int)queries.size());
    for (auto [x, y] : queries) println(x, y);

    return 0;
}
