#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose size
    int N = rnd.next(1, 10);
    int a = rnd.next(1, N);
    int b = rnd.next(1, N);

    // Value-distribution mode: 0=small, 1=large, 2=mixed
    int mode = rnd.next(0, 2);
    const int smallMax = 20;
    const int largeMax = 50000;
    int maxval = (mode == 0 ? smallMax : largeMax);

    // Decide if we force an "ANGRY" case (only if there is at least one other visible)
    bool isAngry = false;
    if (N > 1) {
        isAngry = (rnd.next(0, 1) == 1);
    }

    // Prepare matrix X (1-based indexing)
    vector<vector<int>> X(N+1, vector<int>(N+1, 0));

    // Compute X[a][b]
    int Xab;
    if (isAngry) {
        // ensure Xab < maxval so we can place someone larger
        Xab = rnd.next(1, maxval - 1);
    } else {
        Xab = rnd.next(1, maxval);
    }
    X[a][b] = Xab;

    // List of visible seats (same row or same column, except itself)
    vector<pair<int,int>> vis;
    for (int j = 1; j <= N; j++) {
        if (j == b) continue;
        vis.emplace_back(a, j);
    }
    for (int i = 1; i <= N; i++) {
        if (i == a) continue;
        vis.emplace_back(i, b);
    }

    // If angry, pick one visible to be strictly greater
    pair<int,int> forced = {-1, -1};
    if (isAngry && !vis.empty()) {
        forced = rnd.any(vis);
        X[forced.first][forced.second] = rnd.next(Xab + 1, maxval);
    }

    // Fill the rest
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i == a && j == b) continue;
            if (isAngry && make_pair(i,j) == forced) continue;
            // If not angry, ensure no one in row/col exceeds Xab
            if (!isAngry && (i == a || j == b)) {
                X[i][j] = rnd.next(1, Xab);
            }
            else {
                // Regular fill: obey mode
                if (mode == 2) {
                    // mixed small/large
                    if (rnd.next() < 0.5) {
                        X[i][j] = rnd.next(1, smallMax);
                    } else {
                        X[i][j] = rnd.next(1, largeMax);
                    }
                } else {
                    // uniform in [1, maxval]
                    X[i][j] = rnd.next(1, maxval);
                }
            }
        }
    }

    // Output
    println(N, a, b);
    for (int i = 1; i <= N; i++) {
        vector<int> row;
        for (int j = 1; j <= N; j++) {
            row.push_back(X[i][j]);
        }
        println(row);
    }

    return 0;
}
