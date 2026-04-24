#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small dimensions
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 10);
    vector<vector<int>> grid(n, vector<int>(m, 0));

    // Hyper-parameter: number of random lines
    int lineCnt = rnd.next(0, 3);
    for (int it = 0; it < lineCnt; it++) {
        bool horizontal = rnd.next(0, 1);
        int len = rnd.next(1, horizontal ? m : n);
        if (horizontal) {
            int i = rnd.next(0, n - 1);
            int j0 = rnd.next(0, m - len);
            for (int j = j0; j < j0 + len; j++)
                grid[i][j] = 1;
        } else {
            int i0 = rnd.next(0, n - len);
            int j = rnd.next(0, m - 1);
            for (int i = i0; i < i0 + len; i++)
                grid[i][j] = 1;
        }
    }

    // Hyper-parameter: number of small rectangles
    int rectCnt = rnd.next(0, 3);
    for (int it = 0; it < rectCnt; it++) {
        int h = rnd.next(1, min(3, n));
        int w = rnd.next(1, min(3, m));
        int i0 = rnd.next(0, n - h);
        int j0 = rnd.next(0, m - w);
        for (int i = i0; i < i0 + h; i++)
            for (int j = j0; j < j0 + w; j++)
                grid[i][j] = 1;
    }

    // Hyper-parameter: noise density
    double p_noise = rnd.wnext(101, rnd.next(-2, 2)) / 100.0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (rnd.next() < p_noise)
                grid[i][j] = 1;
        }
    }

    // Output
    println(n, m);
    for (int i = 0; i < n; i++) {
        println(grid[i]);
    }
    return 0;
}
