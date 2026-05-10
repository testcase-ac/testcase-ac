#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    long long N = inf.readLong(1LL, 10000000000000LL, "N");
    inf.readEoln();

    // No further constraints to check, as the game is always playable for any N in [1, 1e13]
    // No global property to check (e.g., "answer always exists" is trivial here)

    inf.readEof();
}
