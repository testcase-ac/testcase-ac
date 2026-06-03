#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0) ? 1 : rnd.next(2, 14);

    vector<int> x(n), range(max(0, n - 1));
    x[0] = 0;

    if (mode == 0) {
        println(n);
        println(x);
        return 0;
    }

    if (mode == 1) {
        int current = 0;
        for (int i = 1; i < n; ++i) {
            current += rnd.next(0, 4);
            x[i] = current;
        }
        int reach = 0;
        for (int i = 0; i < n - 1; ++i) {
            int need = max(0, x[i + 1] - x[i]);
            range[i] = rnd.next(need, need + 5);
            reach = max(reach, x[i] + range[i]);
            if (i + 1 < n - 1 && reach < x[i + 1]) {
                range[i] += x[i + 1] - reach;
                reach = x[i] + range[i];
            }
        }
    } else if (mode == 2) {
        int current = 0;
        for (int i = 1; i < n; ++i) {
            current += rnd.next(1, 6);
            x[i] = current;
        }
        int breakAt = rnd.next(0, n - 2);
        for (int i = 0; i < n - 1; ++i) {
            int need = x[i + 1] - x[i];
            if (i == breakAt) {
                range[i] = rnd.next(0, max(0, need - 1));
            } else {
                range[i] = rnd.next(need, need + 4);
            }
        }
    } else if (mode == 3) {
        int clusterSize = rnd.next(2, min(n, 5));
        for (int i = 1; i < clusterSize; ++i) {
            x[i] = 0;
        }
        int current = 0;
        for (int i = clusterSize; i < n; ++i) {
            current += rnd.next(1, 5);
            x[i] = current;
        }
        for (int i = 0; i < n - 1; ++i) {
            int nextGap = x[i + 1] - x[i];
            range[i] = rnd.next(0, nextGap + 5);
        }
    } else if (mode == 4) {
        int current = 0;
        for (int i = 1; i < n; ++i) {
            current += rnd.next(0, 8);
            x[i] = current;
        }
        for (int i = 0; i < n - 1; ++i) {
            int target = rnd.next(i + 1, n - 1);
            range[i] = max(0, x[target] - x[i] + rnd.next(-1, 2));
        }
    } else {
        int current = 0;
        for (int i = 1; i < n; ++i) {
            current += rnd.wnext(10, -2);
            x[i] = current;
        }
        for (int i = 0; i < n - 1; ++i) {
            range[i] = rnd.wnext(18, -1);
        }
    }

    for (int& value : range) {
        value = min(value, 1000000);
    }

    println(n);
    println(x);
    println(range);

    return 0;
}
