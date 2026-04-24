#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read sequence A of length N
    // Each A_i must be between 0 and 2e9 inclusive
    vector<long long> A = inf.readLongs((long long)N, 0LL, 2000000000LL, "A_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
