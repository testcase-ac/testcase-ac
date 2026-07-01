#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 5);
    } else if (mode == 1) {
        n = rnd.next(5, 12);
    } else if (mode == 2) {
        n = rnd.next(2, 9);
    } else if (mode == 3) {
        n = rnd.next(6, 14);
    } else {
        n = rnd.next(1, 12);
    }

    vector<int> assigned;
    if (mode == 2) {
        int base = rnd.next(980, 1000 - n + 1);
        for (int i = 0; i < n; ++i) {
            assigned.push_back(base + i);
        }
    } else if (mode == 3) {
        int base = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            assigned.push_back(base + i);
        }
    } else {
        set<int> used;
        while ((int)assigned.size() < n) {
            int value = (mode == 1) ? rnd.next(1, 30) : rnd.next(1, 1000);
            if (used.insert(value).second) {
                assigned.push_back(value);
            }
        }
        sort(assigned.begin(), assigned.end());
    }

    vector<vector<int>> available(n);
    for (int i = 0; i < n; ++i) {
        set<int> times;
        times.insert(assigned[i]);

        int targetSize;
        if (mode == 0) {
            targetSize = rnd.next(1, 4);
        } else if (mode == 1) {
            targetSize = rnd.next(8, 18);
        } else if (mode == 2) {
            targetSize = rnd.next(1, 5);
        } else if (mode == 3) {
            targetSize = rnd.next(2, 9);
        } else {
            targetSize = rnd.next(1, 30);
        }

        while ((int)times.size() < targetSize) {
            int value;
            if (mode == 1) {
                value = rnd.next(1, 35);
            } else if (mode == 2) {
                value = rnd.next(max(1, assigned[i] - 10), 1000);
            } else if (mode == 3) {
                value = rnd.next(1, min(60, assigned.back() + 10));
            } else if (mode == 4 && rnd.next(0, 1) == 0) {
                value = rnd.next(1, min(1000, assigned[i] + 20));
            } else {
                value = rnd.next(1, 1000);
            }
            times.insert(value);
        }

        available[i].assign(times.begin(), times.end());
    }

    shuffle(available.begin(), available.end());

    println(n);
    for (const vector<int>& times : available) {
        printf("%d", (int)times.size());
        for (int time : times) {
            printf(" %d", time);
        }
        printf("\n");
    }

    return 0;
}
