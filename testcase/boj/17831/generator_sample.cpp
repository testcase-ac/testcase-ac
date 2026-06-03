#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 14);
    if (mode == 0) {
        n = rnd.next(2, 5);
    }

    vector<int> parent(n + 1, 1);
    if (mode == 0) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = i - 1;
        }
    } else if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = 1;
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = max(1, i / 2);
        }
    } else if (mode == 3) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = rnd.next(1, i - 1);
        }
    } else {
        vector<int> order(n);
        iota(order.begin(), order.end(), 1);
        shuffle(order.begin() + 1, order.end());

        vector<int> position(n + 1);
        for (int i = 0; i < n; ++i) {
            position[order[i]] = i;
        }

        for (int i = 1; i < n; ++i) {
            int child = order[i];
            parent[child] = order[rnd.next(0, i - 1)];
        }
        ensure(position[1] == 0);
    }

    vector<int> skill(n + 1);
    int skillMode = rnd.next(0, 5);
    for (int i = 1; i <= n; ++i) {
        if (skillMode == 0) {
            skill[i] = rnd.next(0, 3);
        } else if (skillMode == 1) {
            skill[i] = rnd.next(97, 100);
        } else if (skillMode == 2) {
            skill[i] = (i % 2 == 0 ? rnd.next(0, 5) : rnd.next(80, 100));
        } else if (skillMode == 3) {
            skill[i] = (i == 1 || rnd.next(0, 3) == 0 ? 0 : rnd.next(1, 100));
        } else {
            skill[i] = rnd.next(0, 100);
        }
    }

    println(n);
    for (int i = 2; i <= n; ++i) {
        if (i > 2) {
            putchar(' ');
        }
        printf("%d", parent[i]);
    }
    putchar('\n');
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            putchar(' ');
        }
        printf("%d", skill[i]);
    }
    putchar('\n');

    return 0;
}
