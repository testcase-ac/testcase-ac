#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

static void addSelfNoise(vector<pair<int, int>>& pairs, int n, int count) {
    for (int i = 0; i < count; ++i) {
        int x = rnd.next(1, n);
        pairs.push_back({x, x});
    }
}

static void addDuplicateNoise(vector<pair<int, int>>& pairs, int count) {
    if (pairs.empty()) return;
    for (int i = 0; i < count; ++i) {
        pairs.push_back(rnd.any(pairs));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<pair<int, int>> pairs;

    if (mode == 0) {
        n = rnd.next(1, 8);
        addSelfNoise(pairs, n, rnd.next(1, 12));
        addDuplicateNoise(pairs, rnd.next(0, 10));
    } else if (mode == 1) {
        n = rnd.next(2, 16);
        int start = rnd.next(1, n);
        for (int i = 1; i < n; ++i) {
            int x = ((start + i - 2) % n) + 1;
            int y = ((start + i - 1) % n) + 1;
            pairs.push_back({x, y});
            if (rnd.next(0, 2) == 0) pairs.push_back({y, x});
        }
        addSelfNoise(pairs, n, rnd.next(0, 5));
        addDuplicateNoise(pairs, rnd.next(0, 8));
    } else if (mode == 2) {
        n = rnd.next(4, 18);
        int center = rnd.next(1, n);
        for (int x = 1; x <= n; ++x) {
            if (x == center) continue;
            if (rnd.next(0, 1) == 0) pairs.push_back({center, x});
            else pairs.push_back({x, center});
        }
        addDuplicateNoise(pairs, rnd.next(2, 12));
    } else if (mode == 3) {
        n = rnd.next(6, 20);
        vector<int> vertices(n);
        for (int i = 0; i < n; ++i) vertices[i] = i + 1;
        shuffle(vertices.begin(), vertices.end());

        int pos = 0;
        while (pos < n) {
            int remaining = n - pos;
            int blockSize = min(remaining, rnd.next(2, 5));
            for (int i = pos; i < pos + blockSize; ++i) {
                for (int j = i; j < pos + blockSize; ++j) {
                    if (rnd.next(0, 2) != 0) pairs.push_back({vertices[i], vertices[j]});
                }
            }
            pos += blockSize;
        }
        addDuplicateNoise(pairs, rnd.next(0, 10));
    } else if (mode == 4) {
        n = rnd.next(2, 25);
        int m = rnd.next(1, 60);
        for (int i = 0; i < m; ++i) {
            int x = rnd.next(1, n);
            int y = rnd.next(1, n);
            pairs.push_back({x, y});
        }
    } else {
        n = rnd.next(4900, 5000);
        int base = rnd.next(n - 30, n);
        int m = rnd.next(8, 40);
        for (int i = 0; i < m; ++i) {
            int x = rnd.next(base, n);
            int y = rnd.next(base, n);
            pairs.push_back({x, y});
        }
    }

    if (pairs.empty()) pairs.push_back({1, 1});
    shuffle(pairs.begin(), pairs.end());

    println(n, (int)pairs.size());
    for (auto [x, y] : pairs) println(x, y);

    return 0;
}
