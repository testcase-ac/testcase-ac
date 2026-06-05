#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

vector<int> makeRow(const vector<int>& base, int targetDiff) {
    vector<int> row = base;
    vector<int> order(base.size());
    for (int i = 0; i < int(order.size()); ++i) order[i] = i;
    shuffle(order.begin(), order.end());

    for (int idx : order) {
        if (targetDiff == 0) break;
        int delta = min(targetDiff, 4000);
        int sign = rnd.next(0, 1) == 0 ? -1 : 1;
        row[idx] = base[idx] + sign * delta;
        targetDiff -= delta;
    }

    return row;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 9);
    int m = rnd.next(1, 8);
    if (mode == 6) {
        n = rnd.next(10, 30);
        m = rnd.any(vector<int>{1, 20, 100});
    }

    vector<int> lalpa(m);
    for (int j = 0; j < m; ++j) lalpa[j] = rnd.next(4500, 5500);

    int others = n - 1;
    int hostileCount;
    if (mode == 0) {
        hostileCount = 0;
    } else if (mode == 1) {
        hostileCount = others;
    } else if (mode == 2) {
        hostileCount = max(0, n / 2 - 1);
    } else if (mode == 3) {
        hostileCount = min(others, n / 2);
    } else {
        hostileCount = rnd.next(0, others);
    }

    vector<int> diffs;
    for (int i = 0; i < others; ++i) {
        if (i < hostileCount) {
            diffs.push_back(rnd.any(vector<int>{2001, 2002, rnd.next(2500, min(4000 * m, 12000))}));
        } else {
            diffs.push_back(rnd.any(vector<int>{0, rnd.next(1, 1999), 2000}));
        }
    }
    shuffle(diffs.begin(), diffs.end());

    println(n, m);
    println(lalpa);
    for (int diff : diffs) println(makeRow(lalpa, diff));

    return 0;
}
