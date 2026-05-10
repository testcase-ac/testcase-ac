#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K and G
    int K = inf.readInt(1, 60, "K");
    inf.readSpace();
    int G = inf.readInt(1, 200000, "G");
    inf.readEoln();

    // Compute max leaf index
    long long max_leaf = 1LL << (K - 1);

    for (int i = 0; i < G; ++i) {
        long long a = inf.readLong(1LL, max_leaf, "a");
        inf.readSpace();
        long long b = inf.readLong(a, max_leaf, "b");
        inf.readEoln();

        // No further global properties to check: the range [a, b] is arbitrary in [1, 2^{K-1}]
    }

    inf.readEof();
}
