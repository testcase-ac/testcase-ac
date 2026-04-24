#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N and M: bias small or large
    int tN = rnd.next(-1, 1);
    int N = rnd.wnext(9, tN) + 2; // N in [2..10]
    int tM = rnd.next(-1, 1);
    int M = rnd.wnext(9, tM) + 2; // M in [2..10]
    int K = rnd.next(1, N);

    // Hyper-parameter for overall density: sparse or dense
    double p;
    if (rnd.next(0, 1) == 0) {
        // sparse regime
        p = rnd.next() * 0.3;
    } else {
        // dense regime
        p = 0.3 + rnd.next() * 0.7;
    }

    // Build availability matrix
    vector<vector<bool>> ok(N, vector<bool>(M, false));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (rnd.next() < p) {
                ok[i][j] = true;
            }
        }
        // Ensure each employee can do at least one job
        bool any = false;
        for (int j = 0; j < M; j++) if (ok[i][j]) { any = true; break; }
        if (!any) {
            int j = rnd.next(0, M-1);
            ok[i][j] = true;
        }
    }
    // Ensure at least one total edge
    bool anyEdge = false;
    for (int i = 0; i < N && !anyEdge; i++)
        for (int j = 0; j < M; j++)
            if (ok[i][j]) { anyEdge = true; break; }
    if (!anyEdge) {
        int i = rnd.next(0, N-1), j = rnd.next(0, M-1);
        ok[i][j] = true;
    }

    // Output
    println(N, M, K);
    for (int i = 0; i < N; i++) {
        vector<int> js;
        for (int j = 0; j < M; j++) if (ok[i][j]) js.push_back(j+1);
        shuffle(js.begin(), js.end());
        // print count and list
        printf("%d", (int)js.size());
        for (int x : js) printf(" %d", x);
        printf("\n");
    }

    return 0;
}
