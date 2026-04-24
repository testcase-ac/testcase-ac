#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // small dimensions
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);
    vector<string> grid(N, string(M, 'A'));
    string letters = "ABCDF";

    // choose a pattern for diversity
    int pat = rnd.next(0, 3);
    if (pat == 0) {
        // fully random
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                grid[i][j] = rnd.any(letters);
    } else if (pat == 1) {
        // vertical stripes
        int stripes = rnd.next(1, min(M, 5));
        int base = M / stripes, extra = M % stripes;
        vector<int> widths(stripes, base);
        for (int i = 0; i < extra; i++) widths[i]++;
        vector<char> stripeLetter(stripes);
        for (int i = 0; i < stripes; i++)
            stripeLetter[i] = rnd.any(letters);

        int col = 0;
        for (int s = 0; s < stripes; s++) {
            for (int j = 0; j < widths[s]; j++, col++) {
                for (int i = 0; i < N; i++)
                    grid[i][col] = stripeLetter[s];
            }
        }
    } else if (pat == 2) {
        // checkerboard of two distinct letters
        char l1 = rnd.any(letters);
        char l2;
        do { l2 = rnd.any(letters); } while (l2 == l1);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                grid[i][j] = ((i + j) % 2 == 0 ? l1 : l2);
    } else {
        // border-heavy pattern
        char border = rnd.any(letters);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (i == 0 || i == N - 1 || j == 0 || j == M - 1)
                    grid[i][j] = border;
                else
                    grid[i][j] = rnd.any(letters);
            }
        }
    }

    // small random noise to break patterns
    int noise = rnd.next(0, (N * M) / 10);
    for (int k = 0; k < noise; k++) {
        int i = rnd.next(0, N - 1);
        int j = rnd.next(0, M - 1);
        grid[i][j] = rnd.any(letters);
    }

    // output
    println(N, M);
    for (int i = 0; i < N; i++)
        printf("%s\n", grid[i].c_str());

    return 0;
}
