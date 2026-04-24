#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 3000, "N");
    inf.readEoln();

    // Read A_i for i = 1..N
    for (int i = 1; i <= N; i++) {
        long long Ai = inf.readLong(1LL, 100000LL, "A_i");
        inf.readEoln();
    }

    // Read M
    int M = inf.readInt(0, 100, "M");
    inf.readEoln();

    // Read B_i for i = 1..M
    for (int i = 1; i <= M; i++) {
        long long Bi = inf.readLong(1LL, 100000LL, "B_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
