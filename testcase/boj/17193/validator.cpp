#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of cows, must satisfy 2 <= N <= 7500
    int N = inf.readInt(2, 7500, "N");
    inf.readSpace();
    // Read K: number of groups, must satisfy 2 <= K <= N
    int K = inf.readInt(2, N, "K");
    inf.readEoln();

    // No further global properties to check: input is just two integers.
    inf.readEof();
    return 0;
}
