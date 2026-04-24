#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: size N of the table
    int N = rnd.next(1, 10);

    // Choose a random range size R using a weighted next for diversity
    int Rlo = N * N;
    int Rhi = N * N * 5;
    int diff = Rhi - Rlo;
    int t = rnd.next(-2, 2);
    int rangeSz = rnd.wnext(diff + 1, t) + Rlo;
    int R = rangeSz;

    // Build a pool of distinct integers in [-R, R]
    vector<int> pool;
    pool.reserve(2 * R + 1);
    for (int x = -R; x <= R; ++x) {
        pool.push_back(x);
    }
    shuffle(pool.begin(), pool.end());
    pool.resize(N * N);

    // Fill columns so that each column is strictly increasing
    vector<vector<int>> a(N, vector<int>(N));
    for (int j = 0; j < N; ++j) {
        vector<int> col;
        for (int i = 0; i < N; ++i) {
            col.push_back(pool[j * N + i]);
        }
        sort(col.begin(), col.end());  // ensures strictly increasing since pool has unique values
        for (int i = 0; i < N; ++i) {
            a[i][j] = col[i];
        }
    }

    // Randomly permute columns to add diversity
    vector<int> colOrd(N);
    for (int i = 0; i < N; ++i) colOrd[i] = i;
    shuffle(colOrd.begin(), colOrd.end());

    // Output the test case
    println(N);
    for (int i = 0; i < N; ++i) {
        vector<int> row;
        for (int j = 0; j < N; ++j) {
            row.push_back(a[i][colOrd[j]]);
        }
        println(row);
    }

    return 0;
}
