#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int l;
    int t;
    int n;

    if (mode == 0) {
        l = rnd.next(2, 12);
        t = rnd.next(1, 3 * l);
        n = rnd.next(1, l - 1);
    } else if (mode == 1) {
        l = rnd.next(3, 30);
        t = rnd.any(vector<int>{1, l - 1, l, l + 1, 2 * l - 1, 2 * l, 2 * l + 1});
        n = rnd.next(1, min(l - 1, 12));
    } else if (mode == 2) {
        l = rnd.next(8, 40);
        t = rnd.next(1, 1000000);
        n = rnd.next(max(1, l - 8), l - 1);
    } else if (mode == 3) {
        l = rnd.next(20, 80);
        t = rnd.next(1, 4 * l);
        n = rnd.next(2, min(l - 1, 18));
    } else if (mode == 4) {
        l = rnd.next(2, 200000);
        t = rnd.next(max(1, 1000000 - 10 * max(1, l)), 1000000);
        n = rnd.next(1, min(l - 1, 20));
    } else {
        l = rnd.next(4, 60);
        t = rnd.next(1, 6 * l);
        n = rnd.next(1, min(l - 1, 25));
    }

    vector<int> positions;
    if (mode == 2) {
        for (int x = 1; x < l; ++x) positions.push_back(x);
        shuffle(positions.begin(), positions.end());
        positions.resize(n);
    } else if (mode == 3) {
        positions.push_back(1);
        if (n > 1) positions.push_back(l - 1);
        while ((int)positions.size() < n) {
            int candidate = rnd.next(1, l - 1);
            if (find(positions.begin(), positions.end(), candidate) == positions.end()) {
                positions.push_back(candidate);
            }
        }
    } else {
        while ((int)positions.size() < n) {
            int candidate = rnd.next(1, l - 1);
            if (find(positions.begin(), positions.end(), candidate) == positions.end()) {
                positions.push_back(candidate);
            }
        }
    }
    sort(positions.begin(), positions.end());

    println(l, t);
    println(n);
    for (int i = 0; i < n; ++i) {
        string direction;
        if (mode == 1) {
            direction = (positions[i] * 2 <= l ? "D" : "L");
        } else if (mode == 3) {
            direction = (i % 2 == 0 ? "L" : "D");
        } else if (mode == 5) {
            direction = (i % 3 == 0 ? "D" : rnd.any(vector<string>{"L", "D"}));
        } else {
            direction = rnd.any(vector<string>{"L", "D"});
        }
        println(positions[i], direction);
    }

    return 0;
}
