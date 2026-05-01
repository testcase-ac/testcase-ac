#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseType = rnd.next(0, 2);
    int N;
    vector<int> a;
    vector<pair<int,int>> edges;

    if (caseType == 0) {
        // Case 0: random tree
        N = rnd.next(3, 12);
        a.resize(N+1);
        for (int i = 1; i <= N; i++) {
            a[i] = rnd.next(-5, 5);
        }
        for (int v = 2; v <= N; v++) {
            int p = rnd.next(1, v-1);
            edges.emplace_back(p, v);
        }
    }
    else if (caseType == 1) {
        // Case 1: symmetric star at root
        int m = rnd.next(1, 5);
        bool middle = false;
        if (2*m+1 <= 11) middle = rnd.next(0,1);
        int children = 2*m + (middle ? 1 : 0);
        N = 1 + children;
        a.assign(N+1, 0);
        a[1] = rnd.next(-5,5);
        int id = 2;
        // m pairs
        for (int i = 0; i < m; i++) {
            int v = rnd.next(-5,5);
            a[id] = v;
            edges.emplace_back(1, id++);
            a[id] = v;
            edges.emplace_back(1, id++);
        }
        if (middle) {
            a[id] = rnd.next(-5,5);
            edges.emplace_back(1, id++);
        }
    }
    else {
        // Case 2: full symmetric binary tree of height 2
        N = 7;
        a.resize(N+1);
        a[1] = rnd.next(-5,5);
        int v1 = rnd.next(-5,5);
        int v2 = rnd.next(-5,5);
        a[2] = v1; a[3] = v1;
        a[4] = v2; a[5] = v2;
        a[6] = v2; a[7] = v2;
        edges = {
            {1,2},{1,3},
            {2,4},{2,5},
            {3,6},{3,7}
        };
    }

    // Output
    println(N);
    for (int i = 1; i <= N; i++) {
        if (i > 1) printf(" ");
        printf("%d", a[i]);
    }
    printf("\n");
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
