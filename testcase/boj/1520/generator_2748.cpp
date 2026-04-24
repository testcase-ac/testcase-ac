#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Dimensions
    int M = rnd.next(2, 10);
    int N = rnd.next(2, 10);

    // Decide whether to guarantee at least one strictly downhill path
    bool guarantee = rnd.next(0, 1) == 1;
    int pathLen = M + N - 1;

    // Height upper bound
    int hi = rnd.next(1, 100);
    if (guarantee && hi < pathLen) {
        hi = pathLen;
    }

    // Grid initialization
    vector<vector<int>> a(M, vector<int>(N, 0));

    // If guaranteeing a path, build one by random R/D moves
    if (guarantee) {
        vector<pair<int,int>> path;
        int x = 0, y = 0;
        path.emplace_back(x, y);
        while (x != M-1 || y != N-1) {
            if (x == M-1) {
                y++;
            } else if (y == N-1) {
                x++;
            } else if (rnd.next(0,1)) {
                x++;
            } else {
                y++;
            }
            path.emplace_back(x, y);
        }
        // Compute a step so heights stay >=1
        int stepMax = (hi - 1) / (pathLen - 1);
        if (stepMax < 1) stepMax = 1;
        int step = rnd.next(1, stepMax);
        for (int i = 0; i < (int)path.size(); i++) {
            auto p = path[i];
            a[p.first][p.second] = hi - i * step;
        }
    }

    // Fill other cells with random heights in [1, hi]
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (!guarantee || a[i][j] == 0) {
                a[i][j] = rnd.next(1, hi);
            }
        }
    }

    // Output
    println(M, N);
    for (int i = 0; i < M; i++) {
        println(a[i]);
    }
    return 0;
}
