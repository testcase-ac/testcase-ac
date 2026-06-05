#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxV = 1000000000;

    vector<int> minNodes = {1, 2};
    while (true) {
        long long next = 1LL + minNodes[minNodes.size() - 1] + minNodes[minNodes.size() - 2];
        if (next > maxV) break;
        minNodes.push_back((int)next);
    }

    int mode = rnd.next(0, 4);
    int t = rnd.next(12, 60);
    vector<int> values;
    values.reserve(t);

    auto addThresholdValue = [&]() {
        int idx = rnd.next(0, (int)minNodes.size() - 1);
        int delta = rnd.next(-2, 2);
        int value = minNodes[idx] + delta;
        value = max(1, min(maxV, value));
        values.push_back(value);
    };

    while ((int)values.size() < t) {
        if (mode == 0) {
            values.push_back(rnd.next(1, 30));
        } else if (mode == 1) {
            addThresholdValue();
        } else if (mode == 2) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) values.push_back(rnd.next(1, 1000));
            if (bucket == 1) values.push_back(rnd.next(1000, 1000000));
            if (bucket == 2) values.push_back(rnd.next(1000000, maxV));
            if (bucket == 3) addThresholdValue();
        } else if (mode == 3) {
            values.push_back(maxV - rnd.next(0, 1000));
        } else {
            int idx = rnd.next(0, (int)minNodes.size() - 1);
            int lo = minNodes[idx];
            int hi = idx + 1 < (int)minNodes.size() ? minNodes[idx + 1] - 1 : maxV;
            values.push_back(rnd.next(lo, hi));
        }
    }

    println(t);
    for (int value : values) println(value);

    return 0;
}
