#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of elements
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // Read A[1] through A[N], one per line
    for (int i = 1; i <= N; i++) {
        inf.readInt(0, 1000000, "A_i");
        inf.readEoln();
    }

    // No extra content
    inf.readEof();
    return 0;
}
