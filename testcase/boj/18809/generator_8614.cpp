#include "testlib.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // 1. Choose N, M (small/medium for readability)
    int N, M;
    if (rnd.next(0, 99) < 40) {
        N = rnd.next(2, 6);
        M = rnd.next(2, 6);
    } else {
        N = rnd.next(5, 15);
        M = rnd.next(5, 15);
    }

    vector<vector<int>> grid;
    int landCnt = 0;

    // 2. Generate base grid of 0 (lake) and 1 (land) with enough land
    int attempts = 0;
    while (true) {
        attempts++;
        grid.assign(N, vector<int>(M, 1));

        int baseType = rnd.next(0, 3); // 0..3
        if (baseType == 0) {
            // Mostly land, few lakes
            double p0 = (rnd.next(0, 1) == 0 ? 0.15 : 0.25);
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < M; ++j)
                    if (rnd.next() < p0)
                        grid[i][j] = 0;
        } else if (baseType == 1) {
            // Roughly half lakes
            double p0 = 0.5;
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < M; ++j)
                    grid[i][j] = (rnd.next() < p0 ? 0 : 1);
        } else if (baseType == 2) {
            // Horizontal stripes
            for (int i = 0; i < N; ++i) {
                bool lakeRow = (rnd.next(0, 1) == 0);
                double p0 = lakeRow ? 0.7 : 0.1;
                for (int j = 0; j < M; ++j)
                    grid[i][j] = (rnd.next() < p0 ? 0 : 1);
            }
        } else {
            // Vertical stripes
            for (int j = 0; j < M; ++j) {
                bool lakeCol = (rnd.next(0, 1) == 0);
                double p0 = lakeCol ? 0.7 : 0.1;
                for (int i = 0; i < N; ++i)
                    grid[i][j] = (rnd.next() < p0 ? 0 : 1);
            }
        }

        landCnt = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (grid[i][j] != 0)
                    landCnt++;

        if (landCnt >= 2)
            break;

        // Fallback: ensure progress
        if (attempts > 50) {
            grid.assign(N, vector<int>(M, 1));
            landCnt = N * M;
            break;
        }
    }

    // 3. Collect land cells where we may place value 2
    vector<pair<int,int>> land;
    land.reserve(landCnt);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (grid[i][j] != 0)
                land.push_back({i, j});

    landCnt = (int)land.size();
    int maxK = min(10, landCnt);
    int K2 = (maxK == 2 ? 2 : rnd.next(2, maxK)); // # of '2' cells

    // 4. Decide pattern for placing '2' cells
    vector<pair<int,int>> twos;
    twos.reserve(K2);
    vector<vector<int>> used(N, vector<int>(M, 0));
    int placeType = rnd.next(0, 3); // 0..3

    if (placeType == 0) {
        // Completely random among land cells
        shuffle(land.begin(), land.end());
        for (int i = 0; i < K2; ++i) {
            twos.push_back(land[i]);
        }
    } else if (placeType == 1) {
        // One cluster via BFS from random land start
        vector<vector<int>> vis(N, vector<int>(M, 0));
        vector<pair<int,int>> cluster;
        cluster.reserve(landCnt);
        pair<int,int> start = rnd.any(land);
        queue<pair<int,int>> q;
        q.push(start);
        vis[start.first][start.second] = 1;
        const int dx[4] = {-1,1,0,0};
        const int dy[4] = {0,0,-1,1};
        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            cluster.push_back(cur);
            int x = cur.first, y = cur.second;
            for (int d = 0; d < 4; ++d) {
                int nx = x + dx[d], ny = y + dy[d];
                if (0 <= nx && nx < N && 0 <= ny && ny < M) {
                    if (!vis[nx][ny] && grid[nx][ny] != 0) {
                        vis[nx][ny] = 1;
                        q.push({nx, ny});
                    }
                }
            }
        }
        // Take as many as possible from the cluster
        int take = min(K2, (int)cluster.size());
        for (int i = 0; i < take; ++i) {
            twos.push_back(cluster[i]);
            used[cluster[i].first][cluster[i].second] = 1;
        }
        // Fill remaining randomly from other land cells
        if ((int)twos.size() < K2) {
            vector<pair<int,int>> rem;
            for (auto &p : land)
                if (!used[p.first][p.second])
                    rem.push_back(p);
            shuffle(rem.begin(), rem.end());
            int need = K2 - (int)twos.size();
            for (int i = 0; i < need && i < (int)rem.size(); ++i) {
                twos.push_back(rem[i]);
                used[rem[i].first][rem[i].second] = 1;
            }
        }
    } else if (placeType == 2) {
        // Try to spread them far apart (large Manhattan distances)
        shuffle(land.begin(), land.end());
        int distMin = (rnd.next(0, 1) == 0 ? 2 : 3);
        for (auto &cell : land) {
            if ((int)twos.size() >= K2) break;
            bool ok = true;
            for (auto &p : twos) {
                int d = abs(p.first - cell.first) + abs(p.second - cell.second);
                if (d < distMin) { ok = false; break; }
            }
            if (ok) {
                twos.push_back(cell);
                used[cell.first][cell.second] = 1;
            }
        }
        // If not enough, fill randomly from remaining land
        if ((int)twos.size() < K2) {
            vector<pair<int,int>> rem;
            for (auto &p : land)
                if (!used[p.first][p.second])
                    rem.push_back(p);
            shuffle(rem.begin(), rem.end());
            int need = K2 - (int)twos.size();
            for (int i = 0; i < need && i < (int)rem.size(); ++i) {
                twos.push_back(rem[i]);
                used[rem[i].first][rem[i].second] = 1;
            }
        }
    } else {
        // Prefer border cells
        vector<pair<int,int>> border;
        for (auto &p : land) {
            int i = p.first, j = p.second;
            if (i == 0 || i == N - 1 || j == 0 || j == M - 1)
                border.push_back(p);
        }
        shuffle(border.begin(), border.end());
        if ((int)border.size() >= K2) {
            for (int i = 0; i < K2; ++i) {
                twos.push_back(border[i]);
            }
        } else {
            for (auto &p : border) {
                twos.push_back(p);
                used[p.first][p.second] = 1;
            }
            int need = K2 - (int)twos.size();
            vector<pair<int,int>> rem;
            for (auto &p : land)
                if (!used[p.first][p.second])
                    rem.push_back(p);
            shuffle(rem.begin(), rem.end());
            for (int i = 0; i < need && i < (int)rem.size(); ++i) {
                twos.push_back(rem[i]);
                used[rem[i].first][rem[i].second] = 1;
            }
        }
    }

    // Ensure we have exactly K2 distinct '2' cells
    sort(twos.begin(), twos.end());
    twos.erase(unique(twos.begin(), twos.end()), twos.end());
    if ((int)twos.size() > K2) {
        twos.resize(K2);
    }

    // Apply '2' cells to grid
    for (auto &p : twos) {
        grid[p.first][p.second] = 2;
    }

    int actualK = (int)twos.size(); // number of cells with value 2

    // 5. Choose G and R such that 1 <= G,R <= 5 and G+R <= actualK
    vector<pair<int,int>> cand;
    for (int g = 1; g <= 5; ++g) {
        for (int r = 1; r <= 5; ++r) {
            if (g + r <= actualK)
                cand.emplace_back(g, r);
        }
    }

    // Prefer sometimes G+R == actualK
    bool preferFull = rnd.next(0, 99) < 50;
    vector<pair<int,int>> eq;
    if (preferFull) {
        for (auto &p : cand)
            if (p.first + p.second == actualK)
                eq.push_back(p);
    }

    pair<int,int> chosen;
    if (!eq.empty()) {
        chosen = rnd.any(eq);
    } else {
        chosen = rnd.any(cand);
    }
    int G = chosen.first;
    int R = chosen.second;

    // 6. Output
    println(N, M, G, R);
    for (int i = 0; i < N; ++i)
        println(grid[i]);

    return 0;
}
