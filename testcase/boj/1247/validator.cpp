#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Problem constants
    const long long MINV = -9223372036854775807LL;
    const long long MAXV =  9223372036854775807LL;
    const int TEST_SETS = 3;

    for (int tc = 1; tc <= TEST_SETS; ++tc) {
        // Read N for this test set
        int N = inf.readInt(1, 100000, "N");
        inf.readEoln();

        // Read the N integers, each on its own line
        for (int i = 0; i < N; ++i) {
            // Name each value for clear error messages
            string name = "a_" + to_string(i+1);
            inf.readLong(MINV, MAXV, name);
            inf.readEoln();
        }
    }

    // No extra data after the three test sets
    inf.readEof();
    return 0;
}
