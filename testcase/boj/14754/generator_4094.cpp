#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for dimensions
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);

    // Prepare a pool of unique base values
    int NM = N * M;
    vector<int> pool(NM);
    for (int i = 0; i < NM; ++i) pool[i] = i;
    shuffle(pool.begin(), pool.end());

    // Step size to spread values up to ~1e9
    int step = rnd.next(1, 1000);

    // Build the grid with distinct heights
    vector<vector<long long>> a(N, vector<long long>(M));
    int idx = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            // Each height = base * step + small random offset
            a[i][j] = 1LL * pool[idx++] * step + rnd.next(0, step - 1);
        }
    }

    // Output the test case
    println(N, M);
    for (int i = 0; i < N; ++i) {
        println(a[i]);
    }
    return 0;
}
