#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Stick = pair<int, int>;

int boundedValue(int x) {
    return max(1, min(10000, x));
}

int pick(int low, int high) {
    return low == high ? low : rnd.next(low, high);
}

void emitCase(const vector<Stick>& sticks) {
    println((int)sticks.size());
    for (int i = 0; i < (int)sticks.size(); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << sticks[i].first << ' ' << sticks[i].second;
    }
    cout << '\n';
}

vector<Stick> increasingChain(int n) {
    vector<Stick> sticks;
    int length = pick(1, 30);
    int weight = pick(1, 30);
    for (int i = 0; i < n; ++i) {
        length += pick(0, 6);
        weight += pick(0, 6);
        sticks.push_back({boundedValue(length), boundedValue(weight)});
    }
    return sticks;
}

vector<Stick> decreasingWeights(int n) {
    vector<Stick> sticks;
    int length = pick(1, 20);
    int weight = pick(8000, 10000);
    for (int i = 0; i < n; ++i) {
        length += pick(0, 5);
        weight -= pick(0, 5);
        sticks.push_back({boundedValue(length), boundedValue(weight)});
    }
    return sticks;
}

vector<Stick> duplicateHeavy(int n) {
    vector<Stick> base;
    int kinds = pick(1, min(n, 8));
    for (int i = 0; i < kinds; ++i) {
        base.push_back({pick(1, 10000), pick(1, 10000)});
    }

    vector<Stick> sticks;
    while ((int)sticks.size() < n) {
        sticks.push_back(rnd.any(base));
    }
    return sticks;
}

vector<Stick> clustered(int n) {
    vector<Stick> sticks;
    int lengthBase = pick(1, 9900);
    int weightBase = pick(1, 9900);
    int spread = pick(1, 80);
    for (int i = 0; i < n; ++i) {
        sticks.push_back({
            boundedValue(lengthBase + pick(0, spread)),
            boundedValue(weightBase + pick(0, spread)),
        });
    }
    return sticks;
}

vector<Stick> layered(int n) {
    vector<Stick> sticks;
    int layers = n == 1 ? 1 : pick(2, min(n, 10));
    for (int i = 0; i < n; ++i) {
        int layer = i % layers;
        int length = 1 + layer * pick(4, 12) + pick(0, 3);
        int weight = 1 + (layers - 1 - layer) * pick(4, 12) + pick(0, 3);
        sticks.push_back({boundedValue(length), boundedValue(weight)});
    }
    return sticks;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tests = pick(4, 10);
    println(tests);

    for (int tc = 0; tc < tests; ++tc) {
        int n = pick(1, 24);
        if (tc == tests - 1 && rnd.next(3) == 0) {
            n = pick(40, 120);
        }

        int mode = rnd.next(5);
        vector<Stick> sticks;
        if (mode == 0) {
            sticks = increasingChain(n);
        } else if (mode == 1) {
            sticks = decreasingWeights(n);
        } else if (mode == 2) {
            sticks = duplicateHeavy(n);
        } else if (mode == 3) {
            sticks = clustered(n);
        } else {
            sticks = layered(n);
        }

        if (rnd.next(4) != 0) {
            shuffle(sticks.begin(), sticks.end());
        }
        emitCase(sticks);
    }

    return 0;
}
