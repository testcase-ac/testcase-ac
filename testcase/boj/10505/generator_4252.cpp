#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Choose number of wheels
        int n = rnd.next(1, 10);
        // Partition into components
        int comp_cnt = rnd.next(1, n);
        vector<int> sizes(comp_cnt, 1);
        int rem = n - comp_cnt;
        while (rem > 0) {
            int i = rnd.next(0, comp_cnt - 1);
            sizes[i]++;
            rem--;
        }
        // Directions for chains
        int dxs[4] = {1, 0, -1, 0};
        int dys[4] = {0, 1, 0, -1};

        // Collect wheels
        struct Wheel { int x, y, r; };
        vector<Wheel> wheels;
        wheels.reserve(n);

        for (int ci = 0; ci < comp_cnt; ci++) {
            int k = sizes[ci];
            // Base grid offset to avoid inter-component overlap
            int bx = (ci % 5) * 300 - 600;
            int by = (ci / 5) * 300 - 300;
            // Choose chain direction
            int dir = rnd.next(0, 3);
            int dx = dxs[dir], dy = dys[dir];
            // Generate radii
            vector<int> r(k);
            for (int i = 0; i < k; i++) {
                r[i] = rnd.next(1, 10);
            }
            // Place the chain
            vector<pair<int,int>> pos(k);
            // First wheel
            pos[0].first = bx + rnd.next(-20, 20);
            pos[0].second = by + rnd.next(-20, 20);
            // Build chain
            for (int i = 1; i < k; i++) {
                int prevx = pos[i-1].first;
                int prevy = pos[i-1].second;
                int sumr = r[i-1] + r[i];
                pos[i].first  = prevx + dx * sumr;
                pos[i].second = prevy + dy * sumr;
            }
            // Append to global list
            for (int i = 0; i < k; i++) {
                wheels.push_back({pos[i].first, pos[i].second, r[i]});
            }
        }

        // Output this test case
        println(n);
        for (auto &w : wheels) {
            println(w.x, w.y, w.r);
        }
    }
    return 0;
}
