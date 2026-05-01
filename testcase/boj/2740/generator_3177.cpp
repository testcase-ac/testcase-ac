#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for dimensions biased towards small but allow up to 10
    int N = rnd.wnext(10, -1) + 1;  // 1..10, bias small
    int M = rnd.wnext(10, -1) + 1;
    int K = rnd.wnext(10, -1) + 1;

    // Hyper-parameter for element magnitude, bias small but sometimes full range
    int maxAbs = rnd.wnext(101, -1); // 0..100, bias small
    if (rnd.next(0, 9) == 0) // 10% chance to force full range
        maxAbs = 100;

    // Generate matrix A (N x M)
    vector<vector<int>> A(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A[i][j] = rnd.next(-maxAbs, maxAbs);
        }
    }

    // Generate matrix B (M x K)
    vector<vector<int>> B(M, vector<int>(K));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            B[i][j] = rnd.next(-maxAbs, maxAbs);
        }
    }

    // Output in required format
    println(N, M);
    for (auto &row : A) println(row);
    println(M, K);
    for (auto &row : B) println(row);

    return 0;
}
