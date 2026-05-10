#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Read array a_1 ... a_N
    vector<long long> a = inf.readLongs(N, 1LL, 1000000000LL, "a_i");
    inf.readEoln();

    // No additional global properties to check; problem has no extra guarantees
    // such as existence of solution beyond trivial (always can do nothing).

    inf.readEof();
}
