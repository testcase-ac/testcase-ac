#include "testlib.h"

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int finishTime(const vector<int>& d, int k) {
    priority_queue<int, vector<int>, greater<int>> stage;
    for (int i = 0; i < k; ++i) stage.push(d[i]);

    for (int i = k; i < int(d.size()); ++i) {
        int t = stage.top();
        stage.pop();
        stage.push(t + d[i]);
    }

    int answer = 0;
    while (!stage.empty()) {
        answer = max(answer, stage.top());
        stage.pop();
    }
    return answer;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 24);
    vector<int> d(n);

    if (mode == 0) {
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, min(100000, lo + rnd.next(0, 80)));
        for (int& x : d) x = rnd.next(lo, hi);
    } else if (mode == 1) {
        int value = rnd.next(1, 100000);
        for (int& x : d) x = value;
    } else if (mode == 2) {
        int cur = rnd.next(1, 15);
        for (int& x : d) {
            cur += rnd.next(0, 20);
            x = min(cur, 100000);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                d[i] = rnd.next(50000, 100000);
            } else {
                d[i] = rnd.next(1, 30);
            }
        }
    } else if (mode == 4) {
        int heavy = rnd.next(1000, 100000);
        for (int i = 0; i < n; ++i) {
            d[i] = (i % 2 == 0 ? heavy : rnd.next(1, min(heavy, 100)));
        }
    } else {
        n = rnd.next(1, 10);
        d.assign(n, rnd.next(90000, 100000));
        for (int& x : d) x = rnd.next(max(1, d[0] - 1000), 100000);
    }

    int targetK = rnd.next(1, n);
    int tMax = finishTime(d, targetK);

    if (targetK > 1 && rnd.next(0, 2) == 0) {
        int previous = finishTime(d, targetK - 1);
        if (previous > tMax) tMax = rnd.next(tMax, previous - 1);
    }

    println(n, tMax);
    for (int x : d) println(x);

    return 0;
}
