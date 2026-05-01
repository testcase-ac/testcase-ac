#include "testlib.h"
#include <vector>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Grid dimensions
    int N = rnd.next(2, 12);
    int M = rnd.next(2, 15);
    // Maximum height
    int Hmax = rnd.next(1, 9);
    vector<vector<int>> a(N, vector<int>(M));

    // Initial random fill
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            a[i][j] = rnd.next(0, Hmax);

    // 8 directions
    int dx[8] = {-1,-1,-1,0,0,1,1,1};
    int dy[8] = {-1,0,1,-1,1,-1,0,1};

    // Choose mode: 0 = pure random, 1 = one plateau peak, 2 = multiple plateau peaks
    int mode = rnd.next(0, 2);

    vector<vector<bool>> isPlate(N, vector<bool>(M, false));

    auto clampOthers = [&]() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (!isPlate[i][j] && a[i][j] == Hmax) {
                    a[i][j] = rnd.next(0, Hmax - 1);
                }
            }
        }
    };

    if (mode == 1) {
        // Single plateau
        int target = rnd.next(1, 4);
        vector<pair<int,int>> cells;
        // start cell
        int si = rnd.next(0, N-1), sj = rnd.next(0, M-1);
        cells.emplace_back(si, sj);
        isPlate[si][sj] = true;
        // expand
        for (int k = 1; k < target; k++) {
            int idx = rnd.next(0, (int)cells.size() - 1);
            int x = cells[idx].first, y = cells[idx].second;
            vector<pair<int,int>> cand;
            for (int d = 0; d < 8; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (0 <= nx && nx < N && 0 <= ny && ny < M && !isPlate[nx][ny])
                    cand.emplace_back(nx, ny);
            }
            if (cand.empty()) break;
            auto p = rnd.any(cand);
            isPlate[p.first][p.second] = true;
            cells.push_back(p);
        }
        // set plateau height
        for (auto &p : cells)
            a[p.first][p.second] = Hmax;
        // clamp others
        clampOthers();
    }
    else if (mode == 2) {
        // Multiple plateaus
        int K = rnd.next(2, 4);
        vector<pair<int,int>> allSeeds;
        for (int t = 0; t < K; t++) {
            int sz = rnd.next(1, 3);
            vector<pair<int,int>> cells;
            // find start sufficiently far
            int si, sj;
            for (int it = 0; it < 100; it++) {
                si = rnd.next(0, N-1);
                sj = rnd.next(0, M-1);
                bool ok = true;
                for (auto &q : allSeeds) {
                    if (abs(q.first - si) <= 2 && abs(q.second - sj) <= 2) {
                        ok = false; break;
                    }
                }
                if (ok) break;
            }
            cells.emplace_back(si, sj);
            isPlate[si][sj] = true;
            allSeeds.emplace_back(si, sj);
            // expand
            for (int k = 1; k < sz; k++) {
                int idx = rnd.next(0, (int)cells.size() - 1);
                int x = cells[idx].first, y = cells[idx].second;
                vector<pair<int,int>> cand;
                for (int d = 0; d < 8; d++) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if (0 <= nx && nx < N && 0 <= ny && ny < M && !isPlate[nx][ny])
                        cand.emplace_back(nx, ny);
                }
                if (cand.empty()) break;
                auto p = rnd.any(cand);
                isPlate[p.first][p.second] = true;
                cells.push_back(p);
            }
            for (auto &p : cells)
                a[p.first][p.second] = Hmax;
        }
        clampOthers();
    }
    // mode 0: leave pure random

    // Output
    println(N, M);
    for (int i = 0; i < N; i++)
        println(a[i]);

    return 0;
}
