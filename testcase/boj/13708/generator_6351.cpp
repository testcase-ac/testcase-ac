#include "testlib.h"
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N for readability
    int N = rnd.next(2, 20);
    vector<pair<int,int>> pts;

    // Pattern type: 0=uniform, 1=line, 2=circle, 3=clusters
    int type = rnd.next(0, 3);

    if (type == 0) {
        // Uniform random points
        for (int i = 0; i < N; i++) {
            int x = rnd.next(0, 1000);
            int y = rnd.next(0, 1000);
            pts.emplace_back(x, y);
        }
    }
    else if (type == 1) {
        // Collinear on a line with small integer step
        vector<pair<int,int>> dirs = {{1,0},{0,1},{1,1},{1,-1}};
        auto d = rnd.any(dirs);
        int dx = d.first, dy = d.second;
        int bx, by;
        if (dx) bx = rnd.next(0, 1000 - (N-1));
        else bx = rnd.next(0, 1000);
        if (dy > 0) by = rnd.next(0, 1000 - (N-1));
        else if (dy < 0) by = rnd.next(N-1, 1000);
        else by = rnd.next(0, 1000);
        for (int i = 0; i < N; i++) {
            pts.emplace_back(bx + dx * i, by + dy * i);
        }
    }
    else if (type == 2 && N <= 12) {
        // Points on an integer circle (Pythagorean triple)
        vector<tuple<int,int,int>> triples = {
            {3,4,5}, {5,12,13}, {6,8,10}
        };
        auto t = rnd.any(triples);
        int a = get<0>(t), b = get<1>(t), c = get<2>(t);
        // Generate all 12 integer-circle-offsets
        vector<pair<int,int>> off;
        off.reserve(12);
        int signs[2] = {1, -1};
        for (int sx : signs)
            for (int sy : signs) {
                off.emplace_back(sx * a, sy * b);
                off.emplace_back(sx * b, sy * a);
            }
        off.emplace_back(c, 0);
        off.emplace_back(-c, 0);
        off.emplace_back(0, c);
        off.emplace_back(0, -c);
        // Choose N distinct offsets
        shuffle(off.begin(), off.end());
        off.resize(N);
        int cx = rnd.next(c, 1000 - c);
        int cy = rnd.next(c, 1000 - c);
        for (auto &p : off) {
            pts.emplace_back(cx + p.first, cy + p.second);
        }
    }
    else {
        // Clusters
        int C = rnd.next(1, min(4, N));
        vector<int> sz(C, 1);
        int rem = N - C;
        while (rem > 0) {
            int j = rnd.next(0, C-1);
            sz[j]++;
            rem--;
        }
        for (int i = 0; i < C; i++) {
            int cx = rnd.next(0, 1000);
            int cy = rnd.next(0, 1000);
            int spread = rnd.next(0, 50);
            for (int k = 0; k < sz[i]; k++) {
                int dx = rnd.next(-spread, spread);
                int dy = rnd.next(-spread, spread);
                int x = cx + dx;
                int y = cy + dy;
                x = max(0, min(1000, x));
                y = max(0, min(1000, y));
                pts.emplace_back(x, y);
            }
        }
    }

    // If circle case fell back (N>12), ensure size by uniform
    if ((int)pts.size() != N) {
        pts.clear();
        for (int i = 0; i < N; i++)
            pts.emplace_back(rnd.next(0, 1000), rnd.next(0, 1000));
    }

    // Shuffle final points
    shuffle(pts.begin(), pts.end());

    // Output
    println(N);
    for (auto &p : pts)
        println(p.first, p.second);

    return 0;
}
