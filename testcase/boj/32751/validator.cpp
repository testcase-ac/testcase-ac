#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read A, B, C, D
    int A = inf.readInt(0, 100000, "A");
    inf.readSpace();
    int B = inf.readInt(0, 100000, "B");
    inf.readSpace();
    int C = inf.readInt(0, 100000, "C");
    inf.readSpace();
    int D = inf.readInt(0, 100000, "D");
    inf.readEoln();

    // Sum constraint: 1 <= A+B+C+D <= 100000
    long long sum = (long long)A + B + C + D;
    ensuref(sum >= 1,
            "Sum of A, B, C, D must be at least 1, but got %lld", sum);
    ensuref(sum <= 100000,
            "Sum of A, B, C, D must be at most 100000, but got %lld", sum);

    // Read S
    // S must be length N, and only 'a','b','c','d'
    string S = inf.readToken("[a-d]+", "S");
    ensuref((int)S.length() == N,
            "Length of S must be %d, but got %d", N, (int)S.length());
    inf.readEoln();

    inf.readEof();
    return 0;
}
