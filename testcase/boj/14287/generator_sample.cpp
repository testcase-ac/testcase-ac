#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(2, 15);
    int m = rnd.next(2, 35);

    vector<int> parent(n + 1, -1);
    parent[1] = -1;

    if (mode == 0) {
        for (int i = 2; i <= n; ++i) parent[i] = i - 1;
    } else if (mode == 1) {
        for (int i = 2; i <= n; ++i) parent[i] = 1;
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) parent[i] = i / 2;
    } else {
        int bias = rnd.next(-2, 3);
        for (int i = 2; i <= n; ++i) parent[i] = rnd.wnext(i - 1, bias) + 1;
    }

    vector<int> childCount(n + 1, 0);
    for (int i = 2; i <= n; ++i) ++childCount[parent[i]];

    vector<int> nonLeaves;
    for (int i = 1; i <= n; ++i) {
        if (childCount[i] > 0) nonLeaves.push_back(i);
    }

    println(n, m);
    printf("-1");
    for (int i = 2; i <= n; ++i) printf(" %d", parent[i]);
    printf("\n");

    int updateWeightMax = rnd.next(1, 1000);
    for (int q = 0; q < m; ++q) {
        bool makeUpdate = rnd.next(0, 99) < 60;
        if (makeUpdate) {
            int employee = rnd.any(nonLeaves);
            int weight = rnd.next(1, updateWeightMax);
            println(1, employee, weight);
        } else {
            int employee = rnd.next(1, n);
            println(2, employee);
        }
    }

    return 0;
}
