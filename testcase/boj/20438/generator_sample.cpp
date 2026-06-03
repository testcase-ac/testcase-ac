#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 8);
    } else if (mode == 2) {
        n = rnd.next(9, 18);
    } else if (mode == 3) {
        n = rnd.next(20, 35);
    } else {
        n = rnd.next(2, 35);
    }

    vector<int> students;
    for (int x = 3; x <= n + 2; ++x) {
        students.push_back(x);
    }

    vector<int> divisorHeavy;
    for (int x : students) {
        if (x <= 12 || x % 2 == 0 || x % 3 == 0) {
            divisorHeavy.push_back(x);
        }
    }
    shuffle(divisorHeavy.begin(), divisorHeavy.end());
    shuffle(students.begin(), students.end());

    int k = rnd.next(1, n);
    int q = rnd.next(1, n);
    if (mode == 0) {
        k = q = 1;
    } else if (mode == 4) {
        k = rnd.next(max(1, n - 3), n);
        q = rnd.next(max(1, n - 3), n);
    }

    vector<int> sleeping(students.begin(), students.begin() + k);

    vector<int> receiverPool = students;
    if (mode == 2 || mode == 3) {
        receiverPool.clear();
        set<int> used;
        for (int x : divisorHeavy) {
            if (used.insert(x).second) {
                receiverPool.push_back(x);
            }
        }
        for (int x : students) {
            if (used.insert(x).second) {
                receiverPool.push_back(x);
            }
        }
    } else if (mode == 5) {
        receiverPool = sleeping;
        set<int> used(receiverPool.begin(), receiverPool.end());
        for (int x : students) {
            if (used.insert(x).second) {
                receiverPool.push_back(x);
            }
        }
    }

    vector<int> receivers(receiverPool.begin(), receiverPool.begin() + q);

    int m;
    if (mode == 0) {
        m = 1;
    } else {
        m = rnd.next(1, min(20, n * (n + 1) / 2));
    }

    vector<pair<int, int>> intervals;
    intervals.push_back({3, n + 2});
    if (n >= 3) {
        intervals.push_back({3, rnd.next(4, n + 2)});
        intervals.push_back({rnd.next(3, n + 1), n + 2});
    }

    while ((int)intervals.size() < m) {
        int s;
        int e;
        if (mode == 1 && rnd.next(0, 1) == 0) {
            s = rnd.next(3, n + 1);
            e = s + 1;
        } else if (mode == 3 && rnd.next(0, 2) == 0) {
            s = rnd.next(3, max(3, n / 2 + 2));
            e = rnd.next(max(s + 1, n / 2 + 3), n + 2);
        } else {
            s = rnd.next(3, n + 1);
            e = rnd.next(s + 1, n + 2);
        }
        intervals.push_back({s, e});
    }
    shuffle(intervals.begin(), intervals.end());
    intervals.resize(m);

    println(n, k, q, m);
    println(sleeping);
    println(receivers);
    for (auto [s, e] : intervals) {
        println(s, e);
    }

    return 0;
}
