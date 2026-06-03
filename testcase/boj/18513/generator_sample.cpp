#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int MIN_X = -100000000;
const int MAX_X = 100000000;

void addUnique(set<int>& used, vector<int>& positions, int x) {
    if (x < MIN_X || x > MAX_X || used.count(x)) {
        return;
    }
    used.insert(x);
    positions.push_back(x);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 0;
    int k = 0;
    vector<int> positions;
    set<int> used;

    if (mode == 0) {
        n = 1;
        k = rnd.next(1, 30);
        int x = rnd.next(-20, 20);
        addUnique(used, positions, x);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        k = rnd.next(1, 40);
        int start = rnd.next(-30, 30);
        int gap = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            addUnique(used, positions, start + i * gap);
        }
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        k = rnd.next(10, 80);
        int left = rnd.next(-100, -20);
        int right = rnd.next(20, 100);
        for (int i = 0; i < n; ++i) {
            int base = (i % 2 == 0 ? left : right);
            addUnique(used, positions, base + rnd.next(-3, 3) + i / 2);
        }
        for (int x = left; (int)positions.size() < n; ++x) {
            addUnique(used, positions, x);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 6);
        k = rnd.next(1, 50);
        addUnique(used, positions, MIN_X);
        addUnique(used, positions, MAX_X);
        while ((int)positions.size() < n) {
            int side = rnd.next(0, 1);
            int offset = rnd.next(1, 100);
            addUnique(used, positions, side == 0 ? MIN_X + offset : MAX_X - offset);
        }
    } else if (mode == 4) {
        n = rnd.next(3, 15);
        k = rnd.next(1, 120);
        int center = rnd.next(-50, 50);
        while ((int)positions.size() < n) {
            addUnique(used, positions, center + rnd.next(-12, 12));
        }
    } else {
        n = rnd.next(5, 25);
        k = rnd.next(20, 200);
        while ((int)positions.size() < n) {
            addUnique(used, positions, rnd.next(-1000, 1000));
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(positions.begin(), positions.end());
    } else {
        sort(positions.begin(), positions.end());
    }

    println((int)positions.size(), k);
    println(positions);

    return 0;
}
