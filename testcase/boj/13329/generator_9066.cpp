#include "testlib.h"
using namespace std;

void printTransformedSample(const vector<vector<pair<int, int>>> &base) {
    int s = rnd.next(1, 2);      // scale factor (1 or 2)
    int k = rnd.next(0, 2);      // horizontal shear factor (0,1,2)

    int n = (int)base.size();
    println(n);
    for (const auto &poly : base) {
        int m = (int)poly.size();
        printf("%d", m);
        for (auto [x, y] : poly) {
            long long nx = 1LL * s * (x + 1LL * k * y);
            long long ny = 1LL * s * y;
            printf(" %lld %lld", nx, ny);
        }
        printf("\n");
    }
}

void genRandomRectangles() {
    int n = rnd.next(1, 6);

    vector<vector<pair<long long, long long>>> polys;
    vector<pair<long long, long long>> allVerts;

    auto okWithAll = [&](long long x, long long y) -> bool {
        for (auto [px, py] : allVerts) {
            if (px * y - py * x == 0) return false;
        }
        return true;
    };

    for (int i = 0; i < n; ++i) {
        vector<pair<long long, long long>> poly;
        while (true) {
            int baseX = 20 * i + 5; // disjoint vertical stripes to avoid intersections
            long long x1 = baseX + rnd.next(0, 4);      // [baseX, baseX+4]
            long long x2 = x1 + rnd.next(1, 4);         // width 1..4
            long long y1 = rnd.next(1, 10);             // [1,10]
            long long y2 = y1 + rnd.next(1, 8);         // height 1..8

            vector<pair<long long, long long>> vs = {
                {x1, y1}, {x2, y1}, {x2, y2}, {x1, y2}
            };

            bool ok = true;
            // check collinearity within this polygon
            for (int a = 0; a < 4 && ok; ++a)
                for (int b = a + 1; b < 4 && ok; ++b)
                    if (vs[a].first * vs[b].second - vs[b].first * vs[a].second == 0)
                        ok = false;

            // check against all previous vertices
            for (auto &v : vs) {
                if (!ok) break;
                if (!okWithAll(v.first, v.second)) {
                    ok = false;
                    break;
                }
            }

            if (!ok) continue;

            poly = vs;
            for (auto &v : vs) allVerts.push_back(v);
            break;
        }
        polys.push_back(poly);
    }

    println(n);
    for (auto &poly : polys) {
        int m = (int)poly.size(); // always 4 here
        printf("%d", m);
        // vertices in CCW order: (x1,y1)->(x2,y1)->(x2,y2)->(x1,y2)
        for (auto &v : poly) {
            printf(" %lld %lld", v.first, v.second);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Predefined samples from statement
    vector<vector<pair<int, int>>> sample1 = {
        { {-2,13}, {9,12}, {7,15} },
        { {1,16}, {-1,18}, {-5,18}, {-6,16}, {-5,14} },
        { {-12,13}, {-13,11}, {-11,10}, {-7,12}, {-8,13} },
        { {-7,9}, {-5,7}, {0,7}, {1,9}, {-3,12} },
        { {9,9}, {6,10}, {3,9}, {4,6}, {9,7} }
    };

    vector<vector<pair<int, int>>> sample2 = {
        { {-800,500}, {-800,300}, {700,300}, {700,500} },
        { {-700,1100}, {-900,1100}, {-900,700}, {-700,700} },
        { {100,700}, {100,900}, {-500,900}, {-500,700} },
        { {300,700}, {600,700}, {600,1200}, {300,1200} }
    };

    int mode = rnd.next(0, 2); // 0: random rectangles, 1: transformed sample1, 2: transformed sample2

    if (mode == 0) {
        genRandomRectangles();
    } else if (mode == 1) {
        printTransformedSample(sample1);
    } else {
        printTransformedSample(sample2);
    }

    return 0;
}
