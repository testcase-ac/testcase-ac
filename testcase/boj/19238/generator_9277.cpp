#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Passenger {
    int sr, sc;
    int dr, dc;
};

vector<vector<int>> bfsFrom(const vector<vector<int>>& a, int sr, int sc) {
    int N = (int)a.size();
    vector<vector<int>> dist(N, vector<int>(N, -1));
    queue<pair<int,int>> q;
    dist[sr][sc] = 0;
    q.push({sr, sc});
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            if (a[nr][nc] == 1) continue;
            if (dist[nr][nc] != -1) continue;
            dist[nr][nc] = dist[r][c] + 1;
            q.push({nr, nc});
        }
    }
    return dist;
}

long long simulate(const vector<vector<int>>& a,
                   const vector<Passenger>& passengers,
                   int taxiR, int taxiC,
                   long long fuel) {
    int N = (int)a.size();
    int M = (int)passengers.size();
    int curR = taxiR, curC = taxiC;
    vector<int> done(M, 0);

    for (int served = 0; served < M; served++) {
        vector<vector<int>> dist = bfsFrom(a, curR, curC);

        long long bestDist = (long long)1e18;
        int bestIdx = -1;
        int bestR = -1, bestC = -1;

        for (int i = 0; i < M; i++) {
            if (done[i]) continue;
            int sr = passengers[i].sr;
            int sc = passengers[i].sc;
            int d = dist[sr][sc];
            if (d == -1) continue;
            if (bestIdx == -1 || d < bestDist ||
                (d == bestDist && (sr < bestR || (sr == bestR && sc < bestC)))) {
                bestDist = d;
                bestIdx = i;
                bestR = sr;
                bestC = sc;
            }
        }

        if (bestIdx == -1) return -1; // no reachable passenger

        if (fuel < bestDist) return -1;
        fuel -= bestDist;

        curR = passengers[bestIdx].sr;
        curC = passengers[bestIdx].sc;

        vector<vector<int>> dist2 = bfsFrom(a, curR, curC);
        int dr = passengers[bestIdx].dr;
        int dc = passengers[bestIdx].dc;
        int d2 = dist2[dr][dc];
        if (d2 == -1) return -1;
        if (fuel < d2) return -1;
        fuel -= d2;
        fuel += 2LL * d2;
        curR = dr;
        curC = dc;
        done[bestIdx] = 1;
    }

    return fuel;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N
    int sizeType = rnd.next(0, 2);
    int N;
    if (sizeType == 0) N = rnd.next(2, 5);
    else if (sizeType == 1) N = rnd.next(6, 9);
    else N = rnd.next(10, 12);

    vector<vector<int>> a;
    // Generate grid with enough empty cells
    while (true) {
        a.assign(N, vector<int>(N, 0));
        int wallType = rnd.next(0, 3);
        double p;
        if (wallType == 0) p = 0.0;
        else if (wallType == 1) p = 0.15;
        else if (wallType == 2) p = 0.25;
        else p = 0.35;

        int emptiesCnt = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                bool isWall = false;
                if (!(i == 0 && j == 0)) { // no special cell, but avoid all walls
                    int r = rnd.next(0, 99);
                    if (r < int(p * 100.0 + 0.5)) isWall = true;
                }
                a[i][j] = isWall ? 1 : 0;
                if (!isWall) emptiesCnt++;
            }
        }
        if (emptiesCnt >= max(4, N)) break;
    }

    int Nnow = N;
    vector<pair<int,int>> empties;
    vector<vector<int>> idxOf(Nnow, vector<int>(Nnow, -1));
    for (int i = 0; i < Nnow; i++) {
        for (int j = 0; j < Nnow; j++) {
            if (a[i][j] == 0) {
                idxOf[i][j] = (int)empties.size();
                empties.push_back({i, j});
            }
        }
    }
    int E = (int)empties.size();

    // Components of empty cells
    vector<vector<int>> comp(Nnow, vector<int>(Nnow, -1));
    vector<vector<int>> compCells; // indices into 'empties'
    int dr4[4] = {-1, 1, 0, 0};
    int dc4[4] = {0, 0, -1, 1};

    for (int i = 0; i < Nnow; i++) {
        for (int j = 0; j < Nnow; j++) {
            if (a[i][j] == 0 && comp[i][j] == -1) {
                int cid = (int)compCells.size();
                compCells.push_back(vector<int>());
                queue<pair<int,int>> q;
                comp[i][j] = cid;
                q.push({i, j});
                while (!q.empty()) {
                    auto [r, c] = q.front(); q.pop();
                    int idx = idxOf[r][c];
                    if (idx != -1) compCells[cid].push_back(idx);
                    for (int k = 0; k < 4; k++) {
                        int nr = r + dr4[k];
                        int nc = c + dc4[k];
                        if (nr < 0 || nr >= Nnow || nc < 0 || nc >= Nnow) continue;
                        if (a[nr][nc] == 1) continue;
                        if (comp[nr][nc] != -1) continue;
                        comp[nr][nc] = cid;
                        q.push({nr, nc});
                    }
                }
            }
        }
    }

    int M = 0;
    long long fuel = 0;
    vector<Passenger> passengers;
    int taxiR = 0, taxiC = 0;

    auto buildScenario0 = [&]() {
        int Mmax = min(6, E);
        M = rnd.next(1, Mmax);
        passengers.assign(M, Passenger());

        int taxiIndex = rnd.next(0, E - 1);
        taxiR = empties[taxiIndex].first;
        taxiC = empties[taxiIndex].second;

        vector<int> idxs(E);
        iota(idxs.begin(), idxs.end(), 0);
        shuffle(idxs.begin(), idxs.end());

        for (int i = 0; i < M; i++) {
            int sidx = idxs[i];
            passengers[i].sr = empties[sidx].first;
            passengers[i].sc = empties[sidx].second;
        }
        for (int i = 0; i < M; i++) {
            int sidx = idxOf[passengers[i].sr][passengers[i].sc];
            int didx;
            do {
                didx = rnd.next(0, E - 1);
            } while (didx == sidx);
            passengers[i].dr = empties[didx].first;
            passengers[i].dc = empties[didx].second;
        }

        int low = max(10, Nnow * Nnow / 2);
        int high = 200;
        if (low > high) low = high;
        fuel = rnd.next(low, high);
    };

    auto buildScenario1 = [&]() -> bool {
        int Mmax = min(6, E);
        if (Mmax < 1) return false;
        M = rnd.next(1, Mmax);
        passengers.assign(M, Passenger());

        int taxiIndex = rnd.next(0, E - 1);
        taxiR = empties[taxiIndex].first;
        taxiC = empties[taxiIndex].second;

        vector<int> idxs(E);
        iota(idxs.begin(), idxs.end(), 0);
        shuffle(idxs.begin(), idxs.end());
        for (int i = 0; i < M; i++) {
            int sidx = idxs[i];
            passengers[i].sr = empties[sidx].first;
            passengers[i].sc = empties[sidx].second;
        }
        for (int i = 0; i < M; i++) {
            int sidx = idxOf[passengers[i].sr][passengers[i].sc];
            int didx;
            do {
                didx = rnd.next(0, E - 1);
            } while (didx == sidx);
            passengers[i].dr = empties[didx].first;
            passengers[i].dc = empties[didx].second;
        }

        long long hi = 500000;
        if (simulate(a, passengers, taxiR, taxiC, hi) == -1) return false;

        long long lo = 0;
        while (hi - lo > 1) {
            long long mid = (lo + hi) / 2;
            if (simulate(a, passengers, taxiR, taxiC, mid) == -1)
                lo = mid;
            else
                hi = mid;
        }
        long long Fmin = hi;
        long long L = (Fmin >= 3 ? Fmin - 2 : 1);
        long long R = min(500000LL, Fmin + 2);
        if (L > R) L = R;
        fuel = rnd.next((int)L, (int)R);
        if (fuel < 1) fuel = 1;
        return true;
    };

    auto buildScenario2 = [&]() -> bool {
        int C = (int)compCells.size();
        if (C < 2) return false;

        vector<int> compsNonEmpty;
        for (int c = 0; c < C; c++) {
            if (!compCells[c].empty()) compsNonEmpty.push_back(c);
        }
        if ((int)compsNonEmpty.size() < 2) return false;

        int compA = rnd.any(compsNonEmpty);
        vector<int> others;
        for (int c : compsNonEmpty) if (c != compA) others.push_back(c);
        if (others.empty()) return false;
        int compB = rnd.any(others);

        int taxiIndex = rnd.any(compCells[compA]);
        taxiR = empties[taxiIndex].first;
        taxiC = empties[taxiIndex].second;

        int Mmax = min(6, E);
        if (Mmax < 1) return false;
        M = rnd.next(1, Mmax);
        passengers.assign(M, Passenger());

        int startIndex = rnd.any(compCells[compA]);
        int destIndex = rnd.any(compCells[compB]);

        passengers[0].sr = empties[startIndex].first;
        passengers[0].sc = empties[startIndex].second;
        passengers[0].dr = empties[destIndex].first;
        passengers[0].dc = empties[destIndex].second;

        vector<int> avail;
        for (int i = 0; i < E; i++) {
            if (i != startIndex) avail.push_back(i);
        }
        shuffle(avail.begin(), avail.end());
        for (int i = 1; i < M; i++) {
            int idx = avail[i - 1];
            passengers[i].sr = empties[idx].first;
            passengers[i].sc = empties[idx].second;
        }
        for (int i = 1; i < M; i++) {
            int sidx = idxOf[passengers[i].sr][passengers[i].sc];
            int didx;
            do {
                didx = rnd.next(0, E - 1);
            } while (didx == sidx);
            passengers[i].dr = empties[didx].first;
            passengers[i].dc = empties[didx].second;
        }

        int low = max(20, Nnow * Nnow);
        int high = 200;
        if (low > high) low = high;
        fuel = rnd.next(low, high);
        return true;
    };

    auto buildScenario3 = [&]() -> bool {
        int C = (int)compCells.size();
        if (C < 2) return false;

        int taxiComp = rnd.next(0, C - 1);
        if (compCells[taxiComp].empty()) return false;

        int taxiIndex = rnd.any(compCells[taxiComp]);
        taxiR = empties[taxiIndex].first;
        taxiC = empties[taxiIndex].second;

        vector<int> otherComps;
        for (int c = 0; c < C; c++) {
            if (c == taxiComp) continue;
            if (!compCells[c].empty()) otherComps.push_back(c);
        }
        if (otherComps.empty()) return false;
        int badComp = rnd.any(otherComps);
        int unreachableStartIndex = rnd.any(compCells[badComp]);

        int Mmax = min(6, E);
        if (Mmax < 1) return false;
        int lower = (Mmax >= 2 ? 2 : 1);
        M = rnd.next(lower, Mmax);
        passengers.assign(M, Passenger());

        passengers[0].sr = empties[unreachableStartIndex].first;
        passengers[0].sc = empties[unreachableStartIndex].second;

        vector<int> avail;
        for (int i = 0; i < E; i++) {
            if (i != unreachableStartIndex) avail.push_back(i);
        }
        shuffle(avail.begin(), avail.end());
        for (int i = 1; i < M; i++) {
            int idx = avail[i - 1];
            passengers[i].sr = empties[idx].first;
            passengers[i].sc = empties[idx].second;
        }

        for (int i = 0; i < M; i++) {
            int sidx = idxOf[passengers[i].sr][passengers[i].sc];
            int didx;
            do {
                didx = rnd.next(0, E - 1);
            } while (didx == sidx);
            passengers[i].dr = empties[didx].first;
            passengers[i].dc = empties[didx].second;
        }

        int low = max(15, Nnow * Nnow / 2);
        int high = 200;
        if (low > high) low = high;
        fuel = rnd.next(low, high);
        return true;
    };

    auto buildScenario4 = [&]() -> bool {
        if (E < 2) return false;

        int taxiIndex = rnd.next(0, E - 1);
        taxiR = empties[taxiIndex].first;
        taxiC = empties[taxiIndex].second;

        vector<vector<int>> dist = bfsFrom(a, taxiR, taxiC);

        int maxDist = 0;
        for (int idx = 0; idx < E; idx++) {
            int r = empties[idx].first;
            int c = empties[idx].second;
            int d = dist[r][c];
            if (d > maxDist) maxDist = d;
        }
        if (maxDist == 0) return false;

        vector<vector<int>> nodesAtDist(maxDist + 1);
        for (int idx = 0; idx < E; idx++) {
            int r = empties[idx].first;
            int c = empties[idx].second;
            int d = dist[r][c];
            if (d >= 0) nodesAtDist[d].push_back(idx);
        }

        vector<int> candidateDs;
        for (int d = 1; d <= maxDist; d++) {
            if ((int)nodesAtDist[d].size() >= 2) candidateDs.push_back(d);
        }
        if (candidateDs.empty()) return false;

        int d = rnd.any(candidateDs);
        vector<int> vec = nodesAtDist[d];
        if ((int)vec.size() < 2) return false;
        shuffle(vec.begin(), vec.end());
        int idx1 = vec[0];
        int idx2 = vec[1];

        int Mmax = min(6, E);
        if (Mmax < 2) return false;
        M = rnd.next(2, Mmax);
        passengers.assign(M, Passenger());

        passengers[0].sr = empties[idx1].first;
        passengers[0].sc = empties[idx1].second;
        passengers[1].sr = empties[idx2].first;
        passengers[1].sc = empties[idx2].second;

        vector<int> avail;
        for (int i = 0; i < E; i++) {
            if (i != idx1 && i != idx2) avail.push_back(i);
        }
        shuffle(avail.begin(), avail.end());
        for (int i = 2; i < M; i++) {
            int idx = avail[i - 2];
            passengers[i].sr = empties[idx].first;
            passengers[i].sc = empties[idx].second;
        }

        for (int i = 0; i < M; i++) {
            int sidx = idxOf[passengers[i].sr][passengers[i].sc];
            int didx;
            do {
                didx = rnd.next(0, E - 1);
            } while (didx == sidx);
            passengers[i].dr = empties[didx].first;
            passengers[i].dc = empties[didx].second;
        }

        int low = max(10, Nnow * Nnow / 2);
        int high = 150;
        if (low > high) low = high;
        fuel = rnd.next(low, high);
        return true;
    };

    auto buildScenario5 = [&]() {
        int Mmax = min(6, E);
        M = rnd.next(1, Mmax);
        passengers.assign(M, Passenger());

        int taxiIndex = rnd.next(0, E - 1);
        taxiR = empties[taxiIndex].first;
        taxiC = empties[taxiIndex].second;

        passengers[0].sr = taxiR;
        passengers[0].sc = taxiC;

        vector<int> avail;
        for (int i = 0; i < E; i++) {
            if (i != taxiIndex) avail.push_back(i);
        }
        shuffle(avail.begin(), avail.end());
        for (int i = 1; i < M; i++) {
            int idx = avail[i - 1];
            passengers[i].sr = empties[idx].first;
            passengers[i].sc = empties[idx].second;
        }

        for (int i = 0; i < M; i++) {
            int sidx = idxOf[passengers[i].sr][passengers[i].sc];
            int didx;
            do {
                didx = rnd.next(0, E - 1);
            } while (didx == sidx);
            passengers[i].dr = empties[didx].first;
            passengers[i].dc = empties[didx].second;
        }

        int low = max(5, Nnow * Nnow / 3);
        int high = 100;
        if (low > high) low = high;
        fuel = rnd.next(low, high);
    };

    int scenario = rnd.next(0, 5); // 0..5
    bool built = false;

    if (scenario == 0) {
        buildScenario0();
        built = true;
    } else if (scenario == 1) {
        if (buildScenario1()) built = true;
    } else if (scenario == 2) {
        if (buildScenario2()) built = true;
    } else if (scenario == 3) {
        if (buildScenario3()) built = true;
    } else if (scenario == 4) {
        if (buildScenario4()) built = true;
    } else if (scenario == 5) {
        buildScenario5();
        built = true;
    }

    if (!built) {
        buildScenario0();
    }

    // Ensure fuel is within limits
    if (fuel < 1) fuel = 1;
    if (fuel > 500000) fuel = 500000;

    println(Nnow, M, fuel);
    for (int i = 0; i < Nnow; i++) {
        println(a[i]);
    }
    println(taxiR + 1, taxiC + 1);
    for (int i = 0; i < M; i++) {
        println(passengers[i].sr + 1, passengers[i].sc + 1,
                passengers[i].dr + 1, passengers[i].dc + 1);
    }

    return 0;
}
