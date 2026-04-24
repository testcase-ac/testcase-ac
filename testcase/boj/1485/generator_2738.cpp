#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;
using ll = long long;

bool isSquare(const vector<pair<int,int>>& pts) {
    vector<ll> dists;
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            ll dx = pts[i].first - pts[j].first;
            ll dy = pts[i].second - pts[j].second;
            dists.push_back(dx*dx + dy*dy);
        }
    }
    sort(dists.begin(), dists.end());
    // 4 equal sides (smallest), 2 equal diagonals (largest), non-zero sides
    if (dists[0] == 0) return false;
    return dists[0] == dists[1] && dists[1] == dists[2] && dists[2] == dists[3]
        && dists[4] == dists[5] && dists[4] == 2 * dists[0];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int maxCoord = rnd.next(5, 10);
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        bool wantSquare = rnd.next() < 0.5;
        vector<pair<int,int>> pts;
        if (wantSquare) {
            bool rotated = rnd.next(0, 1);
            if (!rotated) {
                // axis-aligned square
                int bias = rnd.next(-1, 1);
                int rawL = rnd.wnext(maxCoord, bias) + 1; // 1..maxCoord
                int L = rawL;
                int x0 = rnd.next(-maxCoord, maxCoord - L);
                int y0 = rnd.next(-maxCoord, maxCoord - L);
                pts = {{x0, y0}, {x0+L, y0}, {x0, y0+L}, {x0+L, y0+L}};
            } else {
                // 45-degree rotated square
                int bias = rnd.next(-1, 1);
                int k = rnd.wnext(maxCoord, bias) + 1;
                int cx = rnd.next(-maxCoord+k, maxCoord-k);
                int cy = rnd.next(-maxCoord+k, maxCoord-k);
                pts = {{cx, cy+k}, {cx+k, cy}, {cx, cy-k}, {cx-k, cy}};
            }
            shuffle(pts.begin(), pts.end());
        } else {
            // random non-square
            do {
                pts.clear();
                while ((int)pts.size() < 4) {
                    int x = rnd.next(-maxCoord, maxCoord);
                    int y = rnd.next(-maxCoord, maxCoord);
                    pair<int,int> p = {x, y};
                    bool dup = false;
                    for (auto& q : pts) if (q == p) { dup = true; break; }
                    if (!dup) pts.push_back(p);
                }
            } while (isSquare(pts));
        }
        for (auto& p : pts)
            println(p.first, p.second);
    }
    return 0;
}
