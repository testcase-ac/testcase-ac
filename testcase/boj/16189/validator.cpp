#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read string s: only lowercase letters, length between 1 and 250000
    string s = inf.readToken("[a-z]+", "s");
    ensuref((int)s.size() >= 1 && (int)s.size() <= 250000,
            "Length of s must be between 1 and 250000, found %d", (int)s.size());
    inf.readEoln();

    // Read integer k: 1 <= k <= 1e18
    long long k = inf.readLong(1LL, 1000000000000000000LL, "k");
    inf.readEoln();

    // No extra input
    inf.readEof();
    return 0;
}
