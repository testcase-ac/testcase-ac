#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of columns
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read the second row values, one per line
    for (int i = 1; i <= N; i++) {
        inf.readInt(1, N, "b_i");
        inf.readEoln();
    }

    // No extra characters after the last line
    inf.readEof();
    return 0;
}
