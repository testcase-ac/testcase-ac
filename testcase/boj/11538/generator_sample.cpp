#include "testlib.h"
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

namespace {
constexpr int kMaxLuminosity = 250000;
constexpr int kTubeCount = 18;

void addIfValid(set<int>& values, int value) {
    if (1 <= value && value <= kMaxLuminosity) {
        values.insert(value);
    }
}

void addNeighbors(set<int>& values, int base, int maxFlips) {
    addIfValid(values, base);

    for (int first = 0; first < kTubeCount; ++first) {
        addIfValid(values, base ^ (1 << first));
    }

    if (maxFlips >= 2) {
        for (int first = 0; first < kTubeCount; ++first) {
            for (int second = first + 1; second < kTubeCount; ++second) {
                addIfValid(values, base ^ (1 << first) ^ (1 << second));
            }
        }
    }
}
} // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    set<int> values;
    int mode = rnd.next(0, 4);
    int targetSize = rnd.next(6, 45);

    if (mode == 0) {
        int base = rnd.next(1, kMaxLuminosity);
        addNeighbors(values, base, 2);
    } else if (mode == 1) {
        int limit = rnd.next(12, 90);
        for (int value = 1; value <= limit; ++value) {
            if (rnd.next(0, 99) < 65) {
                values.insert(value);
            }
        }
    } else if (mode == 2) {
        int base = rnd.next(1, kMaxLuminosity);
        int window = rnd.next(20, 1200);
        for (int i = 0; i < targetSize * 4; ++i) {
            addIfValid(values, base + rnd.next(-window, window));
        }
    } else if (mode == 3) {
        for (int i = 0; i < targetSize; ++i) {
            addIfValid(values, kMaxLuminosity - rnd.next(0, 5000));
        }
        addIfValid(values, kMaxLuminosity - 1);
        addIfValid(values, kMaxLuminosity);
    } else {
        int clusters = rnd.next(2, 5);
        for (int cluster = 0; cluster < clusters; ++cluster) {
            int base = rnd.next(1, kMaxLuminosity);
            addNeighbors(values, base, rnd.next(1, 2));
        }
    }

    while (values.size() > static_cast<size_t>(targetSize)) {
        auto it = values.begin();
        advance(it, rnd.next(static_cast<int>(values.size())));
        values.erase(it);
    }

    while (values.empty()) {
        values.insert(rnd.next(1, kMaxLuminosity));
    }

    for (int value : values) {
        println(value);
    }
    println(-1);

    return 0;
}
