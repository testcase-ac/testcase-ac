#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxSmallN = 14;
    int mode = rnd.next(0, 5);
    int n = (mode == 0 ? 1 : rnd.next(2, maxSmallN));
    int m = rnd.next(n, 2 * n + 8);

    vector<int> parent(n + 1, -1);
    parent[1] = -1;

    if (mode == 1) {
        for (int i = 2; i <= n; ++i) parent[i] = i - 1;
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) parent[i] = 1;
    } else if (mode == 3) {
        for (int i = 2; i <= n; ++i) parent[i] = i / 2;
    } else {
        vector<int> order(n);
        iota(order.begin(), order.end(), 1);
        shuffle(order.begin() + 1, order.end());

        for (int pos = 1; pos < n; ++pos) {
            int child = order[pos];
            int ancestorPos = rnd.next(0, pos - 1);
            parent[child] = order[ancestorPos];
        }
    }

    println(n, m);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) putchar(' ');
        printf("%d", parent[i]);
    }
    putchar('\n');

    for (int command = 0; command < m; ++command) {
        bool forceQuery = (command == m - 1);
        bool useUpdate = !forceQuery && rnd.next(0, 99) < 65;
        int employee = rnd.next(1, n);

        if (useUpdate) {
            int wMode = rnd.next(0, 4);
            int w;
            if (wMode == 0) {
                w = 0;
            } else if (wMode == 1) {
                w = rnd.any(vector<int>{-10000, 10000});
            } else {
                w = rnd.next(-20, 20);
            }
            println(1, employee, w);
        } else {
            println(2, employee);
        }
    }

    return 0;
}
