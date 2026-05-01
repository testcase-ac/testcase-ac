#include "testlib.h"
#include <vector>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of baskets N between 1 and 12
    int N = rnd.next(1, 12);
    // Number of operations M, up to roughly 2*N, with bias for small or large ranges
    int maxM = max(1, N * 2);
    int biasM = rnd.any(vector<int>{-1, 1});
    int M = rnd.wnext(maxM, biasM) + 1;

    vector<tuple<int, int, int>> ops;
    ops.reserve(M);
    for (int t = 0; t < M; t++) {
        // Decide segment length with bias towards small or large
        int biasLen = rnd.any(vector<int>{-1, 1});
        int len = rnd.wnext(N, biasLen) + 1;  // length in [1, N]
        int i = rnd.next(1, N - len + 1);
        int j = i + len - 1;
        int k = rnd.next(1, N);
        ops.emplace_back(i, j, k);
    }

    // Output
    println(N, M);
    for (auto &op : ops) {
        int i, j, k;
        tie(i, j, k) = op;
        println(i, j, k);
    }

    return 0;
}
