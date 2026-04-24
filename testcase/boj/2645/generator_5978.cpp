#include "testlib.h"
#include <vector>
#include <utility>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size
    int n = rnd.next(3, 12);
    // Start and target
    int sr = rnd.next(1, n), sc = rnd.next(1, n);
    int tr, tc;
    do {
        tr = rnd.next(1, n);
        tc = rnd.next(1, n);
    } while (tr == sr && tc == sc);
    // Cost on occupied
    int k = rnd.next(2, 60);
    // Max number of circuits to place
    int m_target = min(7, (n*n)/4);
    int m = rnd.next(1, max(1, m_target));

    vector<vector<bool>> occ(n+1, vector<bool>(n+1, false));
    int occCount = 0;
    vector<vector<pair<int,int>>> circuits;

    // Utility to count free cells
    auto freeCells = [&]() { return n*n - occCount; };

    for (int ci = 0; ci < m; ci++) {
        bool placed = false;
        // Try multiple times for this circuit
        for (int it = 0; it < 500 && !placed; it++) {
            int maxlen = min(15, freeCells());
            if (maxlen < 2) break;
            int len = rnd.next(2, maxlen);
            double straight_prob = rnd.next();
            vector<pair<int,int>> path;

            if (rnd.next() < straight_prob) {
                // Straight horizontal or vertical
                bool horiz = rnd.next(0,1) == 1;
                int dr = horiz ? 0 : 1;
                int dc = horiz ? 1 : 0;
                // Direction +/-1
                int dir = rnd.next(0,1) ? 1 : -1;
                int r0, c0;
                if (horiz) {
                    r0 = rnd.next(1, n);
                    if (dir == 1) {
                        if (n - len + 1 < 1) continue;
                        c0 = rnd.next(1, n - len + 1);
                    } else {
                        if (len > n) continue;
                        c0 = rnd.next(len, n);
                    }
                } else {
                    c0 = rnd.next(1, n);
                    if (dir == 1) {
                        if (n - len + 1 < 1) continue;
                        r0 = rnd.next(1, n - len + 1);
                    } else {
                        if (len > n) continue;
                        r0 = rnd.next(len, n);
                    }
                }
                bool ok = true;
                for (int t = 0; t < len; t++) {
                    int rr = r0 + dr * dir * t;
                    int cc = c0 + dc * dir * t;
                    if (rr < 1 || rr > n || cc < 1 || cc > n || occ[rr][cc]) {
                        ok = false; break;
                    }
                    path.emplace_back(rr, cc);
                }
                if (!ok) continue;
            } else {
                // Random walk
                // Gather free cells
                vector<pair<int,int>> frees;
                frees.reserve(freeCells());
                for (int i = 1; i <= n; i++)
                    for (int j = 1; j <= n; j++)
                        if (!occ[i][j])
                            frees.emplace_back(i, j);
                if ((int)frees.size() < len) continue;
                auto start = rnd.any(frees);
                path.push_back(start);
                // Walk
                while ((int)path.size() < len) {
                    auto [r, c] = path.back();
                    vector<pair<int,int>> nbr;
                    const int drs[4] = {1, -1, 0, 0};
                    const int dcs[4] = {0, 0, 1, -1};
                    for (int d = 0; d < 4; d++) {
                        int rr = r + drs[d], cc = c + dcs[d];
                        if (rr < 1 || rr > n || cc < 1 || cc > n) continue;
                        if (occ[rr][cc]) continue;
                        bool seen = false;
                        for (auto &pp : path)
                            if (pp.first == rr && pp.second == cc) { seen = true; break; }
                        if (!seen) nbr.emplace_back(rr, cc);
                    }
                    if (nbr.empty()) break;
                    auto nxt = rnd.any(nbr);
                    path.push_back(nxt);
                }
                if ((int)path.size() < len) continue;
            }

            // Place it
            for (auto &p : path) {
                if (!occ[p.first][p.second]) {
                    occ[p.first][p.second] = true;
                    occCount++;
                }
            }
            circuits.push_back(path);
            placed = true;
        }
        if (!placed) break;
    }

    // Output
    println(n);
    println(sr, sc, tr, tc);
    println(k);
    println((int)circuits.size());
    for (auto &P : circuits) {
        printf("%d", (int)P.size());
        for (auto &p : P) {
            printf(" %d %d", p.first, p.second);
        }
        printf("\n");
    }

    return 0;
}
