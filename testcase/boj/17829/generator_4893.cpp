#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N = 2, 4, or 8 with a bias towards larger sizes
    int exp = rnd.wnext(3, 1);  // returns 0..2
    int N = 1 << (exp + 1);

    // Three types of value distributions for diversity
    // 0: small range [-10,10]
    // 1: full allowed range [-10000,10000]
    // 2: structured ascending rows with slight noise
    int typ = rnd.next(0, 2);

    // Build the matrix
    vector<vector<int>> mat(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (typ == 0) {
                mat[i][j] = rnd.next(-10, 10);
            } else if (typ == 1) {
                mat[i][j] = rnd.next(-10000, 10000);
            } else {
                // ascending each row with small perturbation
                mat[i][j] = (j + 1) + rnd.next(-1, 1);
            }
        }
    }

    // Randomly shuffle rows and/or columns for additional structure
    if (rnd.next() < 0.5) {
        shuffle(mat.begin(), mat.end());
    }
    if (rnd.next() < 0.5) {
        for (auto &row : mat) {
            shuffle(row.begin(), row.end());
        }
    }

    // Output
    println(N);
    for (auto &row : mat) {
        println(row);
    }
    return 0;
}
