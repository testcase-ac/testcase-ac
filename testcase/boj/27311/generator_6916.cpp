#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(6, 10);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        bool makeHeart = rnd.next(0, 1) == 0;
        int R, C;
        vector<string> grid;
        if (makeHeart) {
            // Good heart case
            int N = rnd.next(2, 8);
            int M = rnd.next(1, N-1);
            R = rnd.next(N, 10);
            C = rnd.next(N, 10);
            grid.assign(R, string(C, '.'));
            int corner = rnd.next(0, 3);
            int dr = rnd.next(0, R - N);
            int dc = rnd.next(0, C - N);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    bool inCut = false;
                    if (corner == 0 && i < M && j < M) inCut = true;         // top-left
                    if (corner == 1 && i < M && j >= N - M) inCut = true;    // top-right
                    if (corner == 2 && i >= N - M && j < M) inCut = true;    // bottom-left
                    if (corner == 3 && i >= N - M && j >= N - M) inCut = true;// bottom-right
                    if (!inCut) grid[dr + i][dc + j] = '#';
                }
            }
        } else {
            // Non-heart cases
            int type = rnd.next(0, 4);
            if (type == 0) {
                // empty
                R = rnd.next(2, 10);
                C = rnd.next(2, 10);
                grid.assign(R, string(C, '.'));
            } else if (type == 1) {
                // full
                R = rnd.next(2, 10);
                C = rnd.next(2, 10);
                grid.assign(R, string(C, '#'));
            } else if (type == 2) {
                // random sparse
                R = rnd.next(2, 10);
                C = rnd.next(2, 10);
                double p = rnd.next(1, 4) / 10.0; // 0.1 to 0.4
                grid.assign(R, string(C, '.'));
                for (int i = 0; i < R; i++)
                    for (int j = 0; j < C; j++)
                        if (rnd.next() < p) grid[i][j] = '#';
            } else if (type == 3) {
                // two separate hearts
                // first heart
                int N1 = rnd.next(2, 6), M1 = rnd.next(1, N1-1);
                int N2 = rnd.next(2, 6), M2 = rnd.next(1, N2-1);
                int maxN = max(N1, N2);
                R = rnd.next(maxN, 10);
                C = rnd.next(maxN, 10);
                grid.assign(R, string(C, '.'));
                vector<pair<int,int>> offs;
                // place first
                int dr1 = rnd.next(0, R - N1), dc1 = rnd.next(0, C - N1);
                int cor1 = rnd.next(0, 3);
                // place second, avoid overlap
                int dr2, dc2, cor2;
                for (int tries = 0; tries < 20; tries++) {
                    dr2 = rnd.next(0, R - N2);
                    dc2 = rnd.next(0, C - N2);
                    bool ov = false;
                    if (dr2 + N2 - 1 < dr1 || dr1 + N1 - 1 < dr2 ||
                        dc2 + N2 - 1 < dc1 || dc1 + N1 - 1 < dc2) {
                        ov = false;
                    } else ov = true;
                    if (!ov) break;
                }
                cor2 = rnd.next(0, 3);
                auto place = [&](int dr, int dc, int N, int M, int corner){
                    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
                        bool inCut = false;
                        if (corner == 0 && i < M && j < M) inCut = true;
                        if (corner == 1 && i < M && j >= N - M) inCut = true;
                        if (corner == 2 && i >= N - M && j < M) inCut = true;
                        if (corner == 3 && i >= N - M && j >= N - M) inCut = true;
                        if (!inCut) grid[dr + i][dc + j] = '#';
                    }
                };
                place(dr1, dc1, N1, M1, cor1);
                place(dr2, dc2, N2, M2, cor2);
            } else {
                // almost-heart: remove one #
                int N = rnd.next(2, 8);
                int M = rnd.next(1, N-1);
                R = rnd.next(N, 10);
                C = rnd.next(N, 10);
                grid.assign(R, string(C, '.'));
                int corner = rnd.next(0, 3);
                int dr = rnd.next(0, R - N);
                int dc = rnd.next(0, C - N);
                vector<pair<int,int>> cells;
                for (int i = 0; i < N; i++)
                    for (int j = 0; j < N; j++) {
                        bool inCut = false;
                        if (corner == 0 && i < M && j < M) inCut = true;
                        if (corner == 1 && i < M && j >= N - M) inCut = true;
                        if (corner == 2 && i >= N - M && j < M) inCut = true;
                        if (corner == 3 && i >= N - M && j >= N - M) inCut = true;
                        if (!inCut) {
                            grid[dr + i][dc + j] = '#';
                            cells.emplace_back(dr+i, dc+j);
                        }
                    }
                if (!cells.empty()) {
                    auto p = rnd.any(cells);
                    grid[p.first][p.second] = '.';
                }
            }
        }
        // Output this test
        println(R, C);
        for (int i = 0; i < R; i++) {
            println(grid[i]);
        }
    }
    return 0;
}
