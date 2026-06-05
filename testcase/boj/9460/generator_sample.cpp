#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxCoord = 100000000;
    const int maxK = 10000;

    int t = rnd.next(3, 8);
    vector<vector<pair<int, int>>> cases;
    vector<int> ks;

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n = (mode == 4 ? rnd.next(12, 28) : rnd.next(2, 12));
        vector<int> xs;
        int baseX = rnd.next(-200, 200);
        int step = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            xs.push_back(baseX + i * step + rnd.next(0, step - 1));
        }
        shuffle(xs.begin(), xs.end());

        vector<pair<int, int>> points;
        points.reserve(n);
        if (mode == 0) {
            int y = rnd.next(-20, 20);
            for (int i = 0; i < n; ++i) points.emplace_back(xs[i], y);
        } else if (mode == 1) {
            int low = rnd.next(-80, -20);
            int high = rnd.next(20, 80);
            for (int i = 0; i < n; ++i) {
                points.emplace_back(xs[i], (i % 2 == 0 ? low : high) + rnd.next(-2, 2));
            }
        } else if (mode == 2) {
            int bands = rnd.next(2, min(5, n));
            vector<int> centers;
            for (int i = 0; i < bands; ++i) centers.push_back(rnd.next(-90, 90));
            sort(centers.begin(), centers.end());
            for (int i = 0; i < n; ++i) {
                int center = centers[i % bands];
                points.emplace_back(xs[i], center + rnd.next(-4, 4));
            }
        } else if (mode == 3) {
            int start = rnd.next(-60, 60);
            int slope = rnd.next(-9, 9);
            if (slope == 0) slope = 1;
            for (int i = 0; i < n; ++i) {
                points.emplace_back(xs[i], start + slope * i + rnd.next(-3, 3));
            }
        } else if (mode == 4) {
            for (int i = 0; i < n; ++i) {
                int y = rnd.next(-maxCoord, maxCoord);
                points.emplace_back(xs[i], y);
            }
        } else {
            int y1 = rnd.next(-maxCoord, -maxCoord + 1000);
            int y2 = rnd.next(maxCoord - 1000, maxCoord);
            for (int i = 0; i < n; ++i) points.emplace_back(xs[i], (i % 3 == 0 ? y1 : y2));
        }

        int kMode = rnd.next(0, 4);
        int k;
        if (kMode == 0) {
            k = 1;
        } else if (kMode == 1) {
            k = rnd.next(1, n);
        } else if (kMode == 2) {
            k = n;
        } else if (kMode == 3) {
            k = rnd.next(n, maxK);
        } else {
            k = maxK;
        }

        cases.push_back(points);
        ks.push_back(k);
    }

    println(t);
    for (int tc = 0; tc < t; ++tc) {
        println((int)cases[tc].size(), ks[tc]);
        for (int i = 0; i < (int)cases[tc].size(); ++i) {
            if (i) cout << ' ';
            cout << cases[tc][i].first << ' ' << cases[tc][i].second;
        }
        cout << '\n';
    }

    return 0;
}
