#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int N = 8;
    // Initialize empty board
    vector<vector<int>> a(N, vector<int>(N, 0));

    // Hyper-parameter: embed some horizontal merging sequences
    int hCount = rnd.next(1, 3);
    vector<int> lengths = {2, 3, 4};
    for (int i = 0; i < hCount; i++) {
        int r = rnd.next(0, N - 1);
        int len = rnd.any(lengths);
        int sc = rnd.next(0, N - len);
        int exp = rnd.next(1, 5); // 2^1 .. 2^5
        int v = 1 << exp;
        for (int c = sc; c < sc + len; c++) {
            if (a[r][c] == 0) a[r][c] = v;
        }
    }

    // Hyper-parameter: embed some vertical merging sequences
    int vCount = rnd.next(1, 3);
    for (int i = 0; i < vCount; i++) {
        int c = rnd.next(0, N - 1);
        int len = rnd.any(lengths);
        int sr = rnd.next(0, N - len);
        int exp = rnd.next(1, 5);
        int v = 1 << exp;
        for (int r = sr; r < sr + len; r++) {
            if (a[r][c] == 0) a[r][c] = v;
        }
    }

    // Hyper-parameter: random fill density
    vector<double> densities = {0.2, 0.4, 0.6};
    double p = rnd.any(densities);
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (a[r][c] == 0 && rnd.next() < p) {
                int exp = rnd.next(1, 8); // 2^1 .. 2^8
                a[r][c] = 1 << exp;
            }
        }
    }

    // Output the board
    for (int r = 0; r < N; r++) {
        println(a[r]);
    }

    // Random direction
    string dirs = "UDLR";
    char dir = rnd.any(dirs);
    printf("%c\n", dir);

    return 0;
}
