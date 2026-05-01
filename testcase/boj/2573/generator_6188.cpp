#include "testlib.h"
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose grid size
    int N = rnd.next(5, 15);
    int M = rnd.next(5, 15);
    int innerH = N - 2, innerW = M - 2;
    vector<vector<int>> a(N, vector<int>(M, 0));
    vector<vector<bool>> used(N, vector<bool>(M, false));

    // Pick a shape pattern: 0=tree, 1=solid rect, 2=ring
    int pattern = rnd.next(0, 2);
    if (pattern == 0) {
        // Random spanning-tree shape
        int maxCells = innerH * innerW;
        int t = rnd.any(vector<int>{-3, 0, 3});
        int k0 = rnd.wnext(maxCells, t);
        int K = max(1, k0 + 1);
        int sr = rnd.next(1, N - 2);
        int sc = rnd.next(1, M - 2);
        vector<pair<int,int>> frontier;
        used[sr][sc] = true;
        frontier.emplace_back(sr, sc);
        int cnt = 1;
        while (cnt < K && !frontier.empty()) {
            int sz = frontier.size();
            int idx = rnd.next(0, sz - 1);
            auto [r, c] = frontier[idx];
            vector<pair<int,int>> nbr;
            if (r > 1 && !used[r-1][c]) nbr.emplace_back(r-1, c);
            if (r+1 < N-1 && !used[r+1][c]) nbr.emplace_back(r+1, c);
            if (c > 1 && !used[r][c-1]) nbr.emplace_back(r, c-1);
            if (c+1 < M-1 && !used[r][c+1]) nbr.emplace_back(r, c+1);
            if (nbr.empty()) {
                frontier.erase(frontier.begin() + idx);
            } else {
                auto pr = rnd.any(nbr);
                used[pr.first][pr.second] = true;
                frontier.push_back(pr);
                cnt++;
            }
        }
    }
    else if (pattern == 1) {
        // Solid rectangle
        int h = rnd.next(2, innerH);
        int w = rnd.next(2, innerW);
        int x0 = rnd.next(1, N - 1 - h);
        int y0 = rnd.next(1, M - 1 - w);
        for (int i = x0; i < x0 + h; i++)
            for (int j = y0; j < y0 + w; j++)
                used[i][j] = true;
    }
    else {
        // Ring (perimeter of a rectangle), fallback to rect if too small
        if (innerH < 4 || innerW < 4) {
            int h = rnd.next(2, innerH);
            int w = rnd.next(2, innerW);
            int x0 = rnd.next(1, N - 1 - h);
            int y0 = rnd.next(1, M - 1 - w);
            for (int i = x0; i < x0 + h; i++)
                for (int j = y0; j < y0 + w; j++)
                    used[i][j] = true;
        } else {
            int h = rnd.next(4, innerH);
            int w = rnd.next(4, innerW);
            int x0 = rnd.next(1, N - 1 - h);
            int y0 = rnd.next(1, M - 1 - w);
            for (int i = x0; i < x0 + h; i++)
                for (int j = y0; j < y0 + w; j++)
                    if (i == x0 || i == x0 + h - 1 || j == y0 || j == y0 + w - 1)
                        used[i][j] = true;
        }
    }

    // Assign heights in [1..10], with uniform or skewed distribution
    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < M - 1; j++) {
            if (used[i][j]) {
                if (rnd.next(0, 1) == 0) {
                    a[i][j] = rnd.next(1, 10);
                } else {
                    int tt = rnd.any(vector<int>{-3, 3});
                    a[i][j] = rnd.wnext(10, tt) + 1;
                }
            }
        }
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++)
        println(a[i]);

    return 0;
}
