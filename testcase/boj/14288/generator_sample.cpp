#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(2, 18);
    int m = rnd.next(n, 40);

    vector<int> parent(n + 1);
    parent[1] = -1;
    for (int i = 2; i <= n; ++i) {
        if (mode == 0) {
            parent[i] = i - 1;
        } else if (mode == 1) {
            parent[i] = 1;
        } else if (mode == 2) {
            parent[i] = max(1, i - rnd.next(1, min(i - 1, 3)));
        } else {
            parent[i] = rnd.next(1, i - 1);
        }
    }

    println(n, m);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) printf(" ");
        printf("%d", parent[i]);
    }
    printf("\n");

    bool hasQuery = false;
    for (int q = 1; q <= m; ++q) {
        int type;
        if (q == m && !hasQuery) {
            type = 2;
        } else if (q % 7 == 0) {
            type = 3;
        } else {
            type = rnd.next(1, 100) <= 62 ? 1 : 2;
        }

        if (type == 1) {
            int employee = rnd.next(1, n);
            int weight = rnd.next(1, 1000);
            println(1, employee, weight);
        } else if (type == 2) {
            int employee = rnd.next(1, n);
            println(2, employee);
            hasQuery = true;
        } else {
            println(3);
        }
    }

    return 0;
}
