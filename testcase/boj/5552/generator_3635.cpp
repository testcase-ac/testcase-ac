#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size
    int W = rnd.next(1, 20);
    int H = rnd.next(1, 20);
    // Number of houses
    int Nmax = min(10, W * H);
    int N = rnd.next(1, Nmax);

    // Random fill helper
    auto gen_random = [&](vector<pair<int,int>>& pts) {
        vector<pair<int,int>> all;
        all.reserve(W * H);
        for (int x = 1; x <= W; x++)
            for (int y = 1; y <= H; y++)
                all.emplace_back(x, y);
        shuffle(all.begin(), all.end());
        pts.assign(all.begin(), all.begin() + N);
    };

    vector<pair<int,int>> pts;
    int scenario = rnd.next(0, 5);

    switch (scenario) {
        case 0: {
            // Fully random distinct
            gen_random(pts);
            break;
        }
        case 1: {
            // Cluster around a random center
            int cx = rnd.next(1, W);
            int cy = rnd.next(1, H);
            set<pair<int,int>> st;
            int attempts = 0;
            while ((int)pts.size() < N && attempts < 1000) {
                attempts++;
                int dx = rnd.next(-2, 2);
                int dy = rnd.next(-2, 2);
                int x = cx + dx;
                int y = cy + dy;
                if (x < 1) x = 1;
                if (x > W) x = W;
                if (y < 1) y = 1;
                if (y > H) y = H;
                auto pr = make_pair(x, y);
                if (!st.count(pr)) {
                    st.insert(pr);
                    pts.push_back(pr);
                }
            }
            if ((int)pts.size() < N) {
                pts.clear();
                gen_random(pts);
            }
            break;
        }
        case 2: {
            // All on same row
            if (N > W) {
                gen_random(pts);
            } else {
                int y = rnd.next(1, H);
                vector<int> xs(W);
                iota(xs.begin(), xs.end(), 1);
                shuffle(xs.begin(), xs.end());
                for (int i = 0; i < N; i++)
                    pts.emplace_back(xs[i], y);
            }
            break;
        }
        case 3: {
            // All on same column
            if (N > H) {
                gen_random(pts);
            } else {
                int x = rnd.next(1, W);
                vector<int> ys(H);
                iota(ys.begin(), ys.end(), 1);
                shuffle(ys.begin(), ys.end());
                for (int i = 0; i < N; i++)
                    pts.emplace_back(x, ys[i]);
            }
            break;
        }
        case 4: {
            // Include corners first
            set<pair<int,int>> st2;
            vector<pair<int,int>> cornerList;
            auto addc = [&](int x, int y) {
                if (1 <= x && x <= W && 1 <= y && y <= H) {
                    if (!st2.count({x,y})) {
                        st2.insert({x,y});
                        cornerList.emplace_back(x,y);
                    }
                }
            };
            addc(1, 1);
            addc(1, H);
            addc(W, 1);
            addc(W, H);
            if ((int)cornerList.size() >= N) {
                // Just take first N corners
                pts.assign(cornerList.begin(), cornerList.begin() + N);
            } else {
                // Take all corners, then random rest
                pts = cornerList;
                set<pair<int,int>> st = st2;
                int attempts = 0;
                while ((int)pts.size() < N && attempts < 1000) {
                    attempts++;
                    int x = rnd.next(1, W);
                    int y = rnd.next(1, H);
                    auto pr = make_pair(x, y);
                    if (!st.count(pr)) {
                        st.insert(pr);
                        pts.push_back(pr);
                    }
                }
                if ((int)pts.size() < N) {
                    pts.clear();
                    gen_random(pts);
                }
            }
            break;
        }
        case 5: {
            // All on the boundary edges
            vector<pair<int,int>> bnds;
            if (W == 1 || H == 1) {
                // Degenerate: boundary is whole grid
                for (int x = 1; x <= W; x++)
                    for (int y = 1; y <= H; y++)
                        bnds.emplace_back(x, y);
            } else {
                for (int x = 1; x <= W; x++) {
                    bnds.emplace_back(x, 1);
                    bnds.emplace_back(x, H);
                }
                for (int y = 2; y <= H - 1; y++) {
                    bnds.emplace_back(1, y);
                    bnds.emplace_back(W, y);
                }
            }
            if ((int)bnds.size() >= N) {
                shuffle(bnds.begin(), bnds.end());
                pts.assign(bnds.begin(), bnds.begin() + N);
            } else {
                gen_random(pts);
            }
            break;
        }
        default: {
            gen_random(pts);
            break;
        }
    }

    // Output
    println(W, H);
    println(N);
    for (auto &p : pts)
        println(p.first, p.second);

    return 0;
}
