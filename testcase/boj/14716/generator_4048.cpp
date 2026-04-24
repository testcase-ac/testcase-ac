#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small grid size for hand-checkable
    int M = rnd.next(1, 8);
    int N = rnd.next(1, 8);
    vector<vector<int>> grid(M, vector<int>(N, 0));
    int mode = rnd.next(0, 2);

    if (mode == 0) {
        // Uniform random density, biased by wnext
        int wad = rnd.next(-1, 1);
        int dens_i = rnd.wnext(101, wad);  // 0..100
        double density = dens_i / 100.0;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                grid[i][j] = (rnd.next() < density) ? 1 : 0;
    }
    else if (mode == 1) {
        // A few isolated single-cell islands
        int maxk = min(M * N, 5);
        int k = rnd.next(0, maxk);
        vector<int> cells(M * N);
        iota(cells.begin(), cells.end(), 0);
        shuffle(cells.begin(), cells.end());
        for (int t = 0; t < k; t++) {
            int id = cells[t];
            grid[id / N][id % N] = 1;
        }
    }
    else {
        // A few blobs grown by random walks
        int maxb = min(M * N, 3);
        int b = rnd.next(1, maxb);
        vector<vector<bool>> used(M, vector<bool>(N, false));
        vector<pair<int,int>> dirs = {
            {-1,-1},{-1,0},{-1,1},
            {0,-1},       {0,1},
            {1,-1}, {1,0}, {1,1}
        };
        for (int bi = 0; bi < b; bi++) {
            // pick a free start
            vector<int> freec;
            for (int i = 0; i < M; i++)
                for (int j = 0; j < N; j++)
                    if (!used[i][j])
                        freec.push_back(i * N + j);
            if (freec.empty()) break;
            int idx = rnd.next(0, (int)freec.size() - 1);
            int si = freec[idx] / N, sj = freec[idx] % N;
            used[si][sj] = true;
            vector<pair<int,int>> blob = {{si, sj}};
            int s = rnd.next(1, 5);
            for (int t = 0; t < s; t++) {
                auto p = blob[rnd.next(0, (int)blob.size() - 1)];
                auto d = rnd.any(dirs);
                int ni = p.first + d.first, nj = p.second + d.second;
                if (ni < 0 || ni >= M || nj < 0 || nj >= N) continue;
                if (used[ni][nj]) continue;
                used[ni][nj] = true;
                blob.emplace_back(ni, nj);
            }
            for (auto &p : blob)
                grid[p.first][p.second] = 1;
        }
    }

    // Output
    println(M, N);
    for (int i = 0; i < M; i++)
        println(grid[i]);

    return 0;
}
