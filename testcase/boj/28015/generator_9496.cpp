#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(1, 10);
    int N, M;
    vector<vector<int>> a;

    switch (type) {
        case 1: { // All zeros
            N = rnd.next(2, 10);
            M = rnd.next(2, 10);
            a.assign(N, vector<int>(M, 0));
            break;
        }
        case 2: { // Single color random
            N = rnd.next(2, 12);
            M = rnd.next(2, 12);
            a.assign(N, vector<int>(M, 0));
            int c = rnd.next(1, 2);
            double densChoices[3] = {0.25, 0.5, 0.75};
            double dens = densChoices[rnd.next(0, 2)];
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < M; ++j)
                    if (rnd.next() < dens)
                        a[i][j] = c;
            break;
        }
        case 3: { // Random with both colors and zeros
            N = rnd.next(3, 12);
            M = rnd.next(3, 12);
            a.assign(N, vector<int>(M, 0));
            double p0Choices[3] = {0.2, 0.3, 0.4};
            double p0 = p0Choices[rnd.next(0, 2)];
            double rest = 1.0 - p0;
            double r = 0.3 + 0.4 * rnd.next(); // in [0.3,0.7)
            double p1 = rest * r;
            double p2 = rest - p1;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    double x = rnd.next();
                    if (x < p0) a[i][j] = 0;
                    else if (x < p0 + p1) a[i][j] = 1;
                    else a[i][j] = 2;
                }
            }
            break;
        }
        case 4: { // Horizontal stripe-like
            N = rnd.next(3, 10);
            M = rnd.next(4, 12);
            a.assign(N, vector<int>(M, 0));
            bool useSegments = rnd.next(0, 1);
            if (!useSegments) {
                for (int i = 0; i < N; ++i) {
                    int v = rnd.next(0, 2);
                    for (int j = 0; j < M; ++j) a[i][j] = v;
                }
            } else {
                for (int i = 0; i < N; ++i) {
                    int s = rnd.next(1, 3);
                    for (int k = 0; k < s; ++k) {
                        int l = rnd.next(0, M - 1);
                        int r = rnd.next(l, M - 1);
                        int col = rnd.next(1, 2);
                        for (int j = l; j <= r; ++j) a[i][j] = col;
                    }
                }
            }
            break;
        }
        case 5: { // Vertical stripe-like
            N = rnd.next(4, 10);
            M = rnd.next(3, 8);
            a.assign(N, vector<int>(M, 0));
            for (int j = 0; j < M; ++j) {
                int colType = rnd.next(0, 1);
                if (colType == 0) { // full column
                    int v = rnd.next(0, 2);
                    for (int i = 0; i < N; ++i) a[i][j] = v;
                } else { // single segment in column
                    int l = rnd.next(0, N - 1);
                    int r = rnd.next(l, N - 1);
                    int c = rnd.next(1, 2);
                    for (int i = l; i <= r; ++i) a[i][j] = c;
                }
            }
            break;
        }
        case 6: { // Checkerboard-ish
            N = M = rnd.next(3, 6);
            a.assign(N, vector<int>(M, 0));
            bool useZeros = rnd.next(0, 1);
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    int v = ((i + j) % 2 == 0) ? 1 : 2;
                    if (useZeros && rnd.next(0, 4) == 0) v = 0;
                    a[i][j] = v;
                }
            }
            break;
        }
        case 7: { // Two overlapping rectangles of different colors
            N = rnd.next(5, 10);
            M = rnd.next(5, 10);
            a.assign(N, vector<int>(M, 0));

            int h1 = rnd.next(2, N);
            int w1 = rnd.next(2, M);
            int top1 = rnd.next(0, N - h1);
            int left1 = rnd.next(0, M - w1);
            int bottom1 = top1 + h1 - 1;
            int right1 = left1 + w1 - 1;
            int c1 = rnd.next(1, 2);
            for (int i = top1; i <= bottom1; ++i)
                for (int j = left1; j <= right1; ++j)
                    a[i][j] = c1;

            int h2 = rnd.next(1, N);
            int w2 = rnd.next(1, M);
            int top2 = rnd.next(0, N - h2);
            int left2 = rnd.next(0, M - w2);
            int bottom2 = top2 + h2 - 1;
            int right2 = left2 + w2 - 1;
            int c2 = 3 - c1;
            for (int i = top2; i <= bottom2; ++i)
                for (int j = left2; j <= right2; ++j)
                    a[i][j] = c2;

            break;
        }
        case 8: { // Narrow grid (N=2 or M=2)
            if (rnd.next(0, 1) == 0) {
                N = 2;
                M = rnd.next(5, 12);
            } else {
                M = 2;
                N = rnd.next(5, 12);
            }
            a.assign(N, vector<int>(M, 0));
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < M; ++j) {
                    int v = rnd.next(0, 2); // roughly equal chance 0,1,2
                    a[i][j] = v;
                }
            break;
        }
        case 9: { // Medium dense random, ensure both colors
            N = rnd.next(10, 15);
            M = rnd.next(10, 15);
            a.assign(N, vector<int>(M, 0));
            int cnt1 = 0, cnt2 = 0;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    int v = rnd.next(0, 2);
                    a[i][j] = v;
                    if (v == 1) ++cnt1;
                    if (v == 2) ++cnt2;
                }
            }
            vector<pair<int,int>> cells;
            cells.reserve(N * M);
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < M; ++j)
                    cells.push_back({i, j});
            shuffle(cells.begin(), cells.end());
            int idx = 0;
            if (cnt1 == 0) {
                a[cells[idx].first][cells[idx].second] = 1;
                ++idx;
            }
            if (cnt2 == 0) {
                if (idx >= (int)cells.size()) idx = 0;
                a[cells[idx].first][cells[idx].second] = 2;
            }
            break;
        }
        case 10: { // Hand-crafted tricky pattern
            N = 4;
            M = 7;
            int temp[4][7] = {
                {1, 1, 0, 2, 2, 0, 1},
                {0, 1, 2, 2, 1, 0, 0},
                {2, 2, 1, 0, 1, 1, 2},
                {0, 0, 1, 2, 0, 2, 2}
            };
            a.assign(N, vector<int>(M, 0));
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < M; ++j)
                    a[i][j] = temp[i][j];
            break;
        }
    }

    println(N, M);
    for (int i = 0; i < N; ++i)
        println(a[i]);

    return 0;
}
