#include "testlib.h"
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size hyper-parameters
    int N = rnd.next(5, 10);
    int M = rnd.next(5, 10);

    // Cheese density percent (10%–90%), skewed towards lower densities
    int density = rnd.wnext(81, -1) + 10;

    // Initialize grid with no cheese on the border
    vector<vector<int>> g(N, vector<int>(M, 0));
    int totalCheese = 0;
    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < M - 1; j++) {
            if (rnd.next(100) < density) {
                g[i][j] = 1;
                totalCheese++;
            }
        }
    }
    // Ensure at least one cheese cell
    if (totalCheese == 0) {
        int i = rnd.next(1, N - 2);
        int j = rnd.next(1, M - 2);
        g[i][j] = 1;
    }

    // Occasionally carve out an internal hole
    if (rnd.next() < 0.5) {
        vector<pair<int,int>> ones;
        for (int i = 1; i < N - 1; i++)
            for (int j = 1; j < M - 1; j++)
                if (g[i][j] == 1)
                    ones.emplace_back(i, j);
        if (ones.size() > 4) {
            auto center = rnd.any(ones);
            int maxr = (int)ones.size() / 4;
            int hr = rnd.next(1, maxr);
            int wr = rnd.next(1, maxr);
            int i0 = max(1, center.first - hr);
            int i1 = min(N - 2, center.first + hr);
            int j0 = max(1, center.second - wr);
            int j1 = min(M - 2, center.second + wr);
            for (int i = i0; i <= i1; i++)
                for (int j = j0; j <= j1; j++)
                    g[i][j] = 0;
        }
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d", g[i][j]);
            if (j + 1 < M) printf(" ");
        }
        printf("\n");
    }
    return 0;
}
