#include "testlib.h"
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for skewing N: -2..2 gives min/med/max bias
    vector<int> skew = {-2, -1, 0, 1, 2};
    int t = rnd.any(skew);
    // rnd.wnext(9, t) gives 0..8 skewed, +2 gives N in [2..10]
    int N = 2 + rnd.wnext(9, t);

    // Probability of uppercase vs lowercase
    double pUpper = rnd.next(0.0, 1.0);

    // Generate grid
    vector<string> grid(N, string(N, 'A'));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (rnd.next() < pUpper) {
                grid[i][j] = char('A' + rnd.next(0, 25));
            } else {
                grid[i][j] = char('a' + rnd.next(0, 25));
            }
        }
    }

    // Hyper-parameter for skewing K
    vector<int> skewK = {-1, 0, 1};
    int tk = rnd.any(skewK);
    int K = rnd.wnext(3, tk) + 1; // yields 1..3

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        printf("%s\n", grid[i].c_str());
    }
    println(K);

    return 0;
}
