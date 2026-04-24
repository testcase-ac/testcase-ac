#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases K
    int K = inf.readInt(1, 50000, "K");
    inf.readEoln();

    // For each test case, read N and M
    for (int i = 0; i < K; i++) {
        int N = inf.readInt(1, 1000000, "N_i");
        inf.readSpace();
        int M = inf.readInt(1, 1000000, "M_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
