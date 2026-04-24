#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 3);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Small number of cafes
        int N = rnd.next(2, 10);
        vector<pair<int,int>> path;
        set<pair<int,int>> vis;
        // Build a random monotone simple path of length N
        while (true) {
            path.clear();
            vis.clear();
            path.emplace_back(0, 0);
            vis.insert({0, 0});
            int last_dir = 0; // 1=E,2=N,3=S
            bool fail = false;
            while ((int)path.size() < N) {
                vector<int> cand;
                int x = path.back().first, y = path.back().second;
                // East
                {
                    int nx = x + 1, ny = y;
                    if (!vis.count({nx, ny}))
                        cand.push_back(1);
                }
                // North (no immediate 180-turn)
                if (last_dir != 3) {
                    int nx = x, ny = y + 1;
                    if (!vis.count({nx, ny}))
                        cand.push_back(2);
                }
                // South (no immediate 180-turn)
                if (last_dir != 2) {
                    int nx = x, ny = y - 1;
                    if (!vis.count({nx, ny}))
                        cand.push_back(3);
                }
                if (cand.empty()) {
                    fail = true;
                    break;
                }
                int d = rnd.any(cand);
                if (d == 1) {
                    x += 1;
                } else if (d == 2) {
                    y += 1;
                } else {
                    y -= 1;
                }
                path.emplace_back(x, y);
                vis.insert({x, y});
                last_dir = d;
            }
            if (!fail && (int)path.size() == N) break;
        }
        // Shuffle input order of cafes
        vector<int> idx(N);
        iota(idx.begin(), idx.end(), 0);
        shuffle(idx.begin(), idx.end());
        // Output this test case
        println(N);
        for (int i = 0; i < N; i++) {
            auto &p = path[idx[i]];
            println(p.first, p.second);
        }
        int maxQ = min(N, 10);
        int m = rnd.next(1, maxQ);
        vector<int> qs;
        qs.push_back(m);
        for (int i = 0; i < m; i++) {
            qs.push_back(rnd.next(1, N));
        }
        println(qs);
    }
    return 0;
}
