#include "testlib.h"
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a generation mode for diversity
    int mode = rnd.next(0, 3);
    vector<vector<int>> a(5, vector<int>(5));

    if (mode == 0) {
        // Fully random digits
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                a[i][j] = rnd.next(0, 9);
    }
    else if (mode == 1) {
        // Constant grid
        int d = rnd.next(0, 9);
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                a[i][j] = d;
    }
    else if (mode == 2) {
        // Row-wise constant
        vector<int> rowDig(5);
        for (int i = 0; i < 5; i++)
            rowDig[i] = rnd.next(0, 9);
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                a[i][j] = rowDig[i];
    }
    else {
        // Cluster-based pattern with small noise
        int k = rnd.next(2, 4);
        vector<pair<int,int>> centers;
        vector<int> centerDig;
        while ((int)centers.size() < k) {
            int x = rnd.next(0, 4), y = rnd.next(0, 4);
            bool ok = true;
            for (auto &p : centers)
                if (p.first == x && p.second == y) { ok = false; break; }
            if (!ok) continue;
            centers.emplace_back(x, y);
            centerDig.push_back(rnd.next(0, 9));
        }
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                int best = 0;
                int md = abs(i - centers[0].first) + abs(j - centers[0].second);
                for (int t = 1; t < k; t++) {
                    int d = abs(i - centers[t].first) + abs(j - centers[t].second);
                    if (d < md) {
                        md = d;
                        best = t;
                    }
                }
                int val = centerDig[best] + rnd.next(-1, 1);
                if (val < 0) val = 0;
                if (val > 9) val = 9;
                a[i][j] = val;
            }
        }
    }

    // Output the 5x5 board
    for (int i = 0; i < 5; i++)
        println(a[i]);

    return 0;
}
