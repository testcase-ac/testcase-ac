#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of tanks / grid size
    int N = rnd.next(5, 20);
    vector<pair<int,int>> pos;

    // Pattern type for variability
    int type = rnd.next(0, 3);
    if (type == 0) {
        // Completely random unique positions
        vector<pair<int,int>> cells;
        for (int r = 1; r <= N; ++r)
            for (int c = 1; c <= N; ++c)
                cells.emplace_back(r, c);
        shuffle(cells.begin(), cells.end());
        pos.assign(cells.begin(), cells.begin() + N);
    } else if (type == 1) {
        // All on main diagonal
        for (int i = 1; i <= N; ++i)
            pos.emplace_back(i, i);
    } else if (type == 2) {
        // Clustered block plus some outside
        int minCluster = max(1, N/4);
        int mCluster = rnd.next(minCluster, N - 1);
        // find smallest k with k*k >= mCluster
        int k = 1;
        while (k * k < mCluster) ++k;
        int maxStart = N - k + 1;
        int rc = rnd.next(1, maxStart);
        int cc = rnd.next(1, maxStart);
        // fill cluster cells
        for (int i = 0; i < mCluster; ++i) {
            int dr = i / k, dc = i % k;
            pos.emplace_back(rc + dr, cc + dc);
        }
        // collect outside cells
        vector<pair<int,int>> outside;
        for (int r = 1; r <= N; ++r) {
            for (int c = 1; c <= N; ++c) {
                if (r < rc || r >= rc + k || c < cc || c >= cc + k)
                    outside.emplace_back(r, c);
            }
        }
        shuffle(outside.begin(), outside.end());
        int need = N - mCluster;
        for (int i = 0; i < need; ++i)
            pos.push_back(outside[i]);
    } else {
        // Near-solved: one per row but duplicates in some columns
        pos.resize(N);
        for (int i = 0; i < N; ++i)
            pos[i] = {i + 1, i + 1};
        int t = rnd.next(1, max(1, N/4));
        vector<int> idx(N);
        iota(idx.begin(), idx.end(), 0);
        shuffle(idx.begin(), idx.end());
        for (int ii = 0; ii < t; ++ii) {
            int i = idx[ii];
            int j;
            do {
                j = rnd.next(0, N - 1);
            } while (j == i);
            pos[i].second = pos[j].second;
        }
    }

    // Randomize input order (tank IDs)
    shuffle(pos.begin(), pos.end());

    // Output
    println(N);
    for (auto &p : pos)
        println(p.first, p.second);

    return 0;
}
