#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of lands
    int n = inf.readInt(1, 200, "n");
    inf.readEoln();

    // Constants for soldier number bounds: |Nij| <= 2^31
    const long long MIN_N = -(1LL << 31);
    const long long MAX_N =  (1LL << 31);

    for (int i = 0; i < n; i++) {
        // Number of soldiers on land i
        int Ti = inf.readInt(0, 100000, "Ti");
        if (Ti > 0) {
            // Exactly one space before the list of soldier numbers
            inf.readSpace();
            // Read exactly Ti soldier numbers, each in [MIN_N, MAX_N]
            inf.readLongs(Ti, MIN_N, MAX_N, "Nij");
        }
        // End of this line
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
