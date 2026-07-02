#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> chooseDenominations(int D, int V, int mode) {
    vector<int> values;

    if (mode == 0) {
        for (int x = 1; x <= V; ++x) {
            values.push_back(x);
        }
        shuffle(values.begin(), values.end());
        values.resize(D);
    } else if (mode == 1) {
        values.push_back(1);
        for (int x = 2; x <= V && static_cast<int>(values.size()) < D; ++x) {
            values.push_back(x);
        }
        while (static_cast<int>(values.size()) < D) {
            int x = rnd.next(1, V);
            if (find(values.begin(), values.end(), x) == values.end()) {
                values.push_back(x);
            }
        }
    } else if (mode == 2) {
        values.push_back(V);
        while (static_cast<int>(values.size()) < D) {
            int x = rnd.next(max(1, V / 2), V);
            if (find(values.begin(), values.end(), x) == values.end()) {
                values.push_back(x);
            }
        }
    } else {
        int step = max(1, rnd.next(1, 6));
        int cur = rnd.next(1, min(V, step + 1));
        while (cur <= V && static_cast<int>(values.size()) < D) {
            values.push_back(cur);
            cur += rnd.next(1, step);
        }
        while (static_cast<int>(values.size()) < D) {
            int x = rnd.next(1, V);
            if (find(values.begin(), values.end(), x) == values.end()) {
                values.push_back(x);
            }
        }
    }

    sort(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(6, 20);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 3);
        int V;
        if (tc == 0) {
            V = 1;
        } else if (tc == 1) {
            V = 30;
        } else if (mode == 2) {
            V = rnd.next(10, 30);
        } else {
            V = rnd.next(2, 30);
        }

        int D = rnd.next(1, min(5, V));
        vector<int> denominations = chooseDenominations(D, V, mode);

        println(1, D, V);
        println(denominations);
    }

    return 0;
}
