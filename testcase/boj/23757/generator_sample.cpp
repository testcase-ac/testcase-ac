#include "testlib.h"

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 15);
    int m = rnd.next(1, n);
    vector<int> boxes(n);
    vector<int> wants;

    if (mode == 0) {
        int hi = rnd.next(3, 40);
        for (int& x : boxes) x = rnd.next(1, hi);
        for (int i = 0; i < m; ++i) wants.push_back(rnd.next(1, hi + 5));
    } else if (mode == 1) {
        int hi = rnd.next(5, 80);
        priority_queue<int> pq;
        for (int& x : boxes) {
            x = rnd.next(1, hi);
            pq.push(x);
        }
        for (int i = 0; i < m; ++i) {
            int top = pq.top();
            pq.pop();
            int want = rnd.next(1, top);
            wants.push_back(want);
            pq.push(top - want);
        }
    } else if (mode == 2) {
        int hi = rnd.next(5, 60);
        priority_queue<int> pq;
        for (int& x : boxes) {
            x = rnd.next(1, hi);
            pq.push(x);
        }
        int failAt = rnd.next(0, m - 1);
        for (int i = 0; i < m; ++i) {
            int top = pq.top();
            pq.pop();
            if (i == failAt) {
                wants.push_back(top + rnd.next(1, hi));
                pq.push(top);
            } else {
                int want = rnd.next(1, top);
                wants.push_back(want);
                pq.push(top - want);
            }
        }
    } else if (mode == 3) {
        n = rnd.next(1, 8);
        m = rnd.next(1, n);
        boxes.assign(n, rnd.next(1, 6));
        boxes[0] = rnd.next(20, 70);
        int remaining = boxes[0];
        for (int i = 0; i < m; ++i) {
            int want = rnd.next(1, max(1, remaining / (m - i)));
            if (i == m - 1 && rnd.next(0, 1)) want = min(100000, remaining + rnd.next(1, 5));
            wants.push_back(want);
            remaining = max(0, remaining - want);
        }
    } else {
        n = rnd.next(1, 12);
        m = rnd.next(1, n);
        boxes.resize(n);
        int base = rnd.next(99960, 100000);
        for (int& x : boxes) x = rnd.next(max(1, base - 30), base);
        for (int i = 0; i < m; ++i) wants.push_back(rnd.next(max(1, base - 50), 100000));
    }

    shuffle(boxes.begin(), boxes.end());

    println(n, m);
    println(boxes);
    println(wants);

    return 0;
}
