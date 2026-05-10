#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(4, 100000, "N");
    inf.readEoln();

    // 2. Read A_1..A_N
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        A[i] = inf.readInt(-1000, 1000, "A_i");
        if (i < N - 1)
            inf.readSpace();
        else
            inf.readEoln();
    }

    inf.readEof();
}
