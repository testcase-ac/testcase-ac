#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small dimensions for hand-checkable output
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);

    // Prepare empty grid
    vector<string> grid(n, string(m, '0'));

    // Five generation modes for diversity
    int mode = rnd.next(0, 4);
    switch (mode) {
    case 0: {
        // Random fill with biased density
        int weight = rnd.next(-3, 3);
        int pInt = rnd.wnext(101, weight); // [0..100]
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (rnd.next(100) < pInt)
                    grid[i][j] = '1';
        break;
    }
    case 1: {
        // All zeros or all ones
        char c = rnd.next(2) ? '1' : '0';
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                grid[i][j] = c;
        break;
    }
    case 2: {
        // Stripes pattern: either row-wise or column-wise
        if (rnd.next(2) == 0) {
            for (int i = 0; i < n; i++) {
                char c = (i % 2 == 0 ? '1' : '0');
                for (int j = 0; j < m; j++)
                    grid[i][j] = c;
            }
        } else {
            for (int j = 0; j < m; j++) {
                char c = (j % 2 == 0 ? '1' : '0');
                for (int i = 0; i < n; i++)
                    grid[i][j] = c;
            }
        }
        break;
    }
    case 3: {
        // Main diagonal of ones
        int mn = min(n, m);
        for (int i = 0; i < mn; i++)
            grid[i][i] = '1';
        break;
    }
    case 4: {
        // Random fill, then force a square of ones
        int weight = rnd.next(-3, 3);
        int pInt = rnd.wnext(101, weight);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (rnd.next(100) < pInt)
                    grid[i][j] = '1';
        int k = rnd.next(1, min(n, m));       // size of forced square
        int x = rnd.next(0, n - k);          // top-left row
        int y = rnd.next(0, m - k);          // top-left col
        for (int i = x; i < x + k; i++)
            for (int j = y; j < y + k; j++)
                grid[i][j] = '1';
        break;
    }
    }

    // Output in required format
    println(n, m);
    for (int i = 0; i < n; i++)
        println(grid[i]);

    return 0;
}
