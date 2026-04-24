#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Read A_i
    vector<int> A = inf.readInts(N, 1, 100, "A");
    inf.readEoln();

    // Read B_i
    vector<int> B = inf.readInts(M, 1, 100, "B");
    inf.readEoln();

    // Check global sum constraint: sum A == sum B
    long long sumA = 0, sumB = 0;
    for (int i = 0; i < N; i++) sumA += A[i];
    for (int i = 0; i < M; i++) sumB += B[i];
    ensuref(sumA == sumB,
            "Sum of A (=%lld) must equal sum of B (=%lld)", sumA, sumB);

    // Read cost matrix C (M rows, each with N entries)
    for (int i = 0; i < M; i++) {
        // Name each row for better error messages
        string rowName = "C_row_" + to_string(i+1);
        vector<int> C = inf.readInts(N, 1, 1000, rowName.c_str());
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
