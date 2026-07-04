#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 6);
    int m = rnd.next(2, 6);
    vector<vector<int>> fuel(n, vector<int>(m));

    if (mode == 0) {
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, 100);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                fuel[i][j] = rnd.next(lo, hi);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                fuel[i][j] = 1 + i + j + rnd.next(0, 8);
    } else if (mode == 2) {
        int cheapCol = rnd.next(0, m - 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int distance = abs(j - cheapCol);
                fuel[i][j] = rnd.next(1 + distance, 12 + distance * 8);
            }
            cheapCol += rnd.next(-1, 1);
            if (cheapCol < 0) cheapCol = 0;
            if (cheapCol >= m) cheapCol = m - 1;
        }
    } else if (mode == 3) {
        int high = rnd.next(70, 100);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                fuel[i][j] = rnd.next(1, 5);
        int blocks = rnd.next(1, n * m / 2);
        for (int k = 0; k < blocks; ++k)
            fuel[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = high;
    } else {
        vector<int> rowBase(n), colBase(m);
        for (int i = 0; i < n; ++i) rowBase[i] = rnd.next(1, 35);
        for (int j = 0; j < m; ++j) colBase[j] = rnd.next(0, 35);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int value = rowBase[i] + colBase[j] + rnd.next(0, 25);
                if (value > 100) value = 100;
                fuel[i][j] = value;
            }
        }
    }

    println(n, m);
    for (const auto& row : fuel)
        println(row);

    return 0;
}
