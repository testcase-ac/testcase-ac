#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(3, 5);
    for (int tc = 0; tc < T; tc++) {
        // Grid size
        int N = rnd.next(2, 10);
        int M = rnd.next(2, 10);

        // Max number of pairs small and hand-checkable
        int maxPairs = (N * M) / 2;
        if (maxPairs > 10) maxPairs = 10;
        if (maxPairs < 1) maxPairs = 1;
        int n = rnd.next(1, maxPairs);

        // Prepare all cells
        vector<pair<int,int>> allCells;
        allCells.reserve(N * M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                allCells.emplace_back(i, j);
            }
        }

        vector<pair<int,int>> childPos, housePos;
        bool placed = false;

        int type = rnd.next(0, 3);
        // Type 1: half-split by columns
        if (type == 1) {
            int mid = M / 2;
            vector<pair<int,int>> left, right;
            for (auto &p : allCells) {
                if (p.second < mid) left.push_back(p);
                else right.push_back(p);
            }
            if ((int)left.size() >= n && (int)right.size() >= n) {
                shuffle(left.begin(), left.end());
                shuffle(right.begin(), right.end());
                childPos.assign(left.begin(), left.begin() + n);
                housePos.assign(right.begin(), right.begin() + n);
                placed = true;
            }
        }
        // Type 2: half-split by rows
        if (!placed && type == 2) {
            int mid = N / 2;
            vector<pair<int,int>> top, bot;
            for (auto &p : allCells) {
                if (p.first < mid) top.push_back(p);
                else bot.push_back(p);
            }
            if ((int)top.size() >= n && (int)bot.size() >= n) {
                shuffle(top.begin(), top.end());
                shuffle(bot.begin(), bot.end());
                childPos.assign(top.begin(), top.begin() + n);
                housePos.assign(bot.begin(), bot.begin() + n);
                placed = true;
            }
        }
        // Type 3: cluster children, houses outside
        if (!placed && type == 3) {
            // determine minimal radius for cluster area >= n
            int drMin = 0;
            while ((2*drMin+1)*(2*drMin+1) < n) drMin++;
            int drMax = min((N-1)/2, (M-1)/2);
            if (drMin <= drMax) {
                int dr = rnd.next(drMin, drMax);
                // pick center so that cluster square fits
                int cx = rnd.next(dr, N-1-dr);
                int cy = rnd.next(dr, M-1-dr);
                vector<pair<int,int>> region, outside;
                region.reserve((2*dr+1)*(2*dr+1));
                outside.reserve(N*M);
                for (auto &p : allCells) {
                    if (abs(p.first - cx) <= dr && abs(p.second - cy) <= dr)
                        region.push_back(p);
                    else
                        outside.push_back(p);
                }
                if ((int)region.size() >= n && (int)outside.size() >= n) {
                    shuffle(region.begin(), region.end());
                    shuffle(outside.begin(), outside.end());
                    childPos.assign(region.begin(), region.begin() + n);
                    housePos.assign(outside.begin(), outside.begin() + n);
                    placed = true;
                }
            }
        }
        // Fallback or type 0: pure random
        if (!placed) {
            shuffle(allCells.begin(), allCells.end());
            childPos.assign(allCells.begin(), allCells.begin() + n);
            housePos.assign(allCells.begin() + n, allCells.begin() + 2*n);
        }

        // Build the grid
        vector<string> grid(N, string(M, '.'));
        for (auto &p : childPos) {
            grid[p.first][p.second] = 'm';
        }
        for (auto &p : housePos) {
            grid[p.first][p.second] = 'H';
        }

        // Output this test case
        println(N, M);
        for (int i = 0; i < N; i++) {
            println(grid[i]);
        }
    }
    // End marker
    println(0, 0);
    return 0;
}
