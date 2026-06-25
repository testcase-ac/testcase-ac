#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Bale = pair<long long, long long>;

const long long kMaxValue = 1000000000LL;

void addBale(vector<Bale>& bales, set<long long>& usedPositions, long long size,
             long long position, long long bessie) {
    if (position < 1 || position > kMaxValue || position == bessie) return;
    if (!usedPositions.insert(position).second) return;
    bales.emplace_back(size, position);
}

long long randomSize(long long distanceHint, int mode) {
    if (mode == 0) return rnd.next(1LL, 12LL);
    if (mode == 1) return rnd.next(1LL, max(1LL, distanceHint));
    if (mode == 2) return rnd.next(distanceHint + 1, min(kMaxValue, distanceHint + 20));
    return rnd.any(vector<long long>{1LL, 2LL, 3LL, 10LL, 100LL, kMaxValue});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<Bale> bales;
    set<long long> usedPositions;
    long long bessie;

    if (mode == 0) {
        bessie = rnd.next(8LL, 60LL);
        int leftCount = rnd.next(1, 5);
        int rightCount = rnd.next(1, 5);
        long long pos = bessie;
        for (int i = 0; i < leftCount; ++i) {
            pos -= rnd.next(1LL, 8LL);
            addBale(bales, usedPositions, randomSize(bessie - pos, rnd.next(0, 3)), pos, bessie);
        }
        pos = bessie;
        for (int i = 0; i < rightCount; ++i) {
            pos += rnd.next(1LL, 8LL);
            addBale(bales, usedPositions, randomSize(pos - bessie, rnd.next(0, 3)), pos, bessie);
        }
    } else if (mode == 1) {
        bessie = rnd.next(10LL, 80LL);
        int count = rnd.next(1, 8);
        long long pos = bessie + rnd.next(1LL, 5LL);
        for (int i = 0; i < count; ++i) {
            addBale(bales, usedPositions, randomSize(pos - bessie, rnd.next(0, 3)), pos, bessie);
            pos += rnd.next(1LL, 10LL);
        }
    } else if (mode == 2) {
        bessie = rnd.next(2LL, 20LL);
        addBale(bales, usedPositions, rnd.next(1LL, 5LL), 1LL, bessie);
        int count = rnd.next(2, 8);
        for (int i = 0; i < count; ++i) {
            long long position = bessie + rnd.next(1LL, 35LL);
            addBale(bales, usedPositions, randomSize(position - bessie, rnd.next(0, 3)), position,
                    bessie);
        }
        addBale(bales, usedPositions, rnd.next(1LL, kMaxValue), kMaxValue, bessie);
    } else {
        bessie = rnd.next(100000000LL, 900000000LL);
        int count = rnd.next(2, 10);
        for (int i = 0; i < count; ++i) {
            long long delta = rnd.next(1LL, 1000000LL);
            long long position = (i % 2 == 0 ? bessie - delta : bessie + delta);
            addBale(bales, usedPositions, randomSize(delta, rnd.next(0, 3)), position, bessie);
        }
    }

    if (bales.empty()) {
        bessie = 2;
        addBale(bales, usedPositions, 1, 1, bessie);
    }

    shuffle(bales.begin(), bales.end());
    println(static_cast<int>(bales.size()), bessie);
    for (const auto& bale : bales) {
        println(bale.first, bale.second);
    }

    return 0;
}
