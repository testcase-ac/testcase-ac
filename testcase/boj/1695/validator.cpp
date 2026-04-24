#include "testlib.h"
#include <climits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 5000, "N");
    inf.readEoln();

    // Read the sequence of N integers, each within 32-bit int range
    for (int i = 0; i < N; i++) {
        long long x = inf.readLong(-2147483648LL, 2147483647LL, "a_i");
        if (i + 1 < N) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    // No extra data
    inf.readEof();
    return 0;
}
