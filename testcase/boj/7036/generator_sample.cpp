#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int MIN_POS = 1;
const int MAX_POS = 1000000;

void addUnique(set<int>& used, vector<int>& positions, int value) {
    value = max(MIN_POS, min(MAX_POS, value));
    if (used.insert(value).second) positions.push_back(value);
}

void fillRandom(set<int>& used, vector<int>& positions, int n) {
    while ((int)positions.size() < n) {
        addUnique(used, positions, rnd.next(MIN_POS, MAX_POS));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 12);
    int l = rnd.next(MIN_POS, MAX_POS);
    vector<int> positions;
    set<int> used;

    if (mode == 0) {
        n = 1;
        l = rnd.any(vector<int>{MIN_POS, MAX_POS, rnd.next(MIN_POS, MAX_POS)});
        addUnique(used, positions, l);
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        l = rnd.next(5, 80);
        for (int i = 0; i < n; ++i) {
            addUnique(used, positions, l + rnd.next(0, 80));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        l = rnd.next(MAX_POS - 80, MAX_POS - 4);
        for (int i = 0; i < n; ++i) {
            addUnique(used, positions, l - rnd.next(0, 80));
        }
    } else if (mode == 3) {
        n = rnd.next(3, 14);
        l = rnd.next(30, MAX_POS - 30);
        int radius = rnd.next(1, 25);
        for (int d = -radius; d <= radius && (int)positions.size() < n; ++d) {
            if (rnd.next(0, 2) != 0) addUnique(used, positions, l + d);
        }
    } else if (mode == 4) {
        n = rnd.next(4, 12);
        l = rnd.next(200000, 800000);
        addUnique(used, positions, MIN_POS);
        addUnique(used, positions, MAX_POS);
        addUnique(used, positions, l);
        while ((int)positions.size() < n) {
            int side = rnd.next(0, 1);
            int gap = rnd.next(1, 200000);
            addUnique(used, positions, l + (side ? gap : -gap));
        }
    } else if (mode == 5) {
        n = rnd.next(8, 20);
        l = rnd.next(1000, MAX_POS - 1000);
        int start = rnd.next(max(MIN_POS, l - 400), l);
        int step = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            addUnique(used, positions, start + i * step);
        }
    } else {
        n = rnd.next(10, 30);
        l = rnd.next(MIN_POS, MAX_POS);
    }

    fillRandom(used, positions, n);

    int orderMode = rnd.next(0, 3);
    if (orderMode == 0) {
        sort(positions.begin(), positions.end());
    } else if (orderMode == 1) {
        sort(positions.rbegin(), positions.rend());
    } else {
        shuffle(positions.begin(), positions.end());
    }

    println(n, l);
    for (int p : positions) {
        println(p);
    }

    return 0;
}
