#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 3);
    for (int tc = 0; tc < T; ++tc) {
        // Maze dimensions
        int M = rnd.next(2, 10);
        int N = rnd.next(2, 10);
        println(M, N);

        // Initial door directions
        string dirs = "NESW";
        for (int i = 0; i < M; ++i) {
            string row;
            for (int j = 0; j < N; ++j) {
                row += rnd.any(dirs);
            }
            println(row);
        }

        // Treasure boxes
        int maxK = min(8, M * N - 2);
        int K = rnd.next(1, maxK);
        println(K);

        // All possible cells except start and end
        vector<pair<int,int>> cells;
        for (int i = 1; i <= M; ++i) {
            for (int j = 1; j <= N; ++j) {
                if ((i == 1 && j == 1) || (i == M && j == N)) continue;
                cells.emplace_back(i, j);
            }
        }
        shuffle(cells.begin(), cells.end());

        // Pick K distinct treasure positions
        for (int i = 0; i < K; ++i) {
            println(cells[i].first, cells[i].second);
        }
    }

    // End of input
    println(0, 0);
    return 0;
}
