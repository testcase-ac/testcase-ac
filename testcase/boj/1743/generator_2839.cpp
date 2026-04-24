#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for small but diverse grids
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);
    int K = rnd.next(1, N * M);

    // Prepare a grid to mark taken cells
    vector<vector<bool>> used(N + 1, vector<bool>(M + 1, false));

    // Decide a cluster size to ensure at least one connected component
    int clusterGoal = rnd.next(1, min(K, 5));
    vector<pair<int,int>> clusterCells;
    // Pick a random center for the cluster
    int r0 = rnd.next(1, N);
    int c0 = rnd.next(1, M);
    clusterCells.emplace_back(r0, c0);
    used[r0][c0] = true;

    // Grow the cluster by adding neighboring cells
    for (int i = 1; i < clusterGoal; i++) {
        vector<pair<int,int>> nbrs;
        for (auto &pr : clusterCells) {
            int r = pr.first, c = pr.second;
            const int dr[4] = {1,-1,0,0};
            const int dc[4] = {0,0,1,-1};
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr >= 1 && nr <= N && nc >= 1 && nc <= M && !used[nr][nc]) {
                    nbrs.emplace_back(nr, nc);
                }
            }
        }
        if (nbrs.empty()) break;
        shuffle(nbrs.begin(), nbrs.end());
        auto pick = nbrs[0];
        used[pick.first][pick.second] = true;
        clusterCells.push_back(pick);
    }

    // Prepare the rest of the positions
    int need = K - (int)clusterCells.size();
    vector<pair<int,int>> rest;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (!used[i][j]) rest.emplace_back(i, j);
        }
    }
    shuffle(rest.begin(), rest.end());
    rest.resize(need);

    // Combine and shuffle final list
    vector<pair<int,int>> allCells = clusterCells;
    allCells.insert(allCells.end(), rest.begin(), rest.end());
    shuffle(allCells.begin(), allCells.end());

    // Output
    println(N, M, K);
    for (auto &pr : allCells) {
        println(pr.first, pr.second);
    }

    return 0;
}
