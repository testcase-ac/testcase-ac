#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCount = rnd.next(1, 5);

    for (int tc = 0; tc < testCount; ++tc) {
        int mode = rnd.next(0, 6);
        int n = rnd.next(1, 12);
        int m = rnd.next(1, 12);
        vector<vector<int>> a(n, vector<int>(m, 0));

        if (mode == 0) {
            // all zeros
        } else if (mode == 1) {
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    a[i][j] = 1;
        } else if (mode == 2) {
            int p = rnd.next(10, 35);
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    a[i][j] = rnd.next(100) < p;
        } else if (mode == 3) {
            int p = rnd.next(60, 90);
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    a[i][j] = rnd.next(100) < p;
        } else if (mode == 4) {
            bool rowStripe = rnd.next(0, 1);
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    a[i][j] = rowStripe ? (i % 2 == 0) : (j % 2 == 0);
        } else if (mode == 5) {
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    a[i][j] = 1;

            int holes = rnd.next(1, max(1, min(n, m)));
            for (int h = 0; h < holes; ++h) {
                int r = rnd.next(0, n - 1);
                int c = rnd.next(0, m - 1);
                a[r][c] = 0;
            }
        } else {
            int side = rnd.next(1, min(n, m));
            int top = rnd.next(0, n - side);
            int left = rnd.next(0, m - side);

            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    a[i][j] = rnd.next(100) < 20;

            for (int i = top; i < top + side; ++i)
                for (int j = left; j < left + side; ++j)
                    a[i][j] = 1;
        }

        println(n, m);
        for (int i = 0; i < n; ++i)
            println(a[i]);
    }

    println(0, 0);
    return 0;
}
