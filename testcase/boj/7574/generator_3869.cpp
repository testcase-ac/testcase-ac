#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N = rnd.next(1, 10);    // number of leaves
    int r = rnd.next(1, 5);     // leaf size
    int d = rnd.next(1, 10);    // max jump distance
    int maxDelta = rnd.next(r + 1, r + d + 5);

    vector<pair<int,int>> pos;
    pos.emplace_back(0, 0);  // always include the leaf covering (0,0)

    // Generate remaining leaves by attaching to existing ones
    for (int i = 1; i < N; i++) {
        bool placed = false;
        for (int tries = 0; tries < 1000 && !placed; tries++) {
            auto [px, py] = pos[rnd.next(0, (int)pos.size() - 1)];
            // Four directions
            vector<pair<int,int>> dirs = {{1,0}, {0,1}, {-1,0}, {0,-1}};
            auto dir = rnd.any(dirs);
            int delta = rnd.next(r + 1, maxDelta);
            int x = px + dir.first * delta;
            int y = py + dir.second * delta;
            if (x < 0 || y < 0) continue;
            // Check non-overlap and no touching
            bool ok = true;
            for (auto &q : pos) {
                int x2 = q.first, y2 = q.second;
                if (!(x + r < x2 || x2 + r < x || y + r < y2 || y2 + r < y)) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                pos.emplace_back(x, y);
                placed = true;
            }
        }
        if (!placed) {
            // Fallback: place it far to the right, non-overlapping
            int x = rnd.next((int)pos.size() * (r + d + 5), (int)pos.size() * (r + d + 5) + 5);
            int y = 0;
            pos.emplace_back(x, y);
        }
    }

    // Randomize input order
    shuffle(pos.begin(), pos.end());

    // Output in the problem format
    println(N, r);
    for (auto &p : pos) {
        println(p.first, p.second);
    }
    println(d);

    return 0;
}
