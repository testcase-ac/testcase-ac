#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of people
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // Heights of each person, one per line
    // Each height is given in nanometers and is less than 2^31.
    // We assume height > 0.
    for (int i = 0; i < N; i++) {
        long long h = inf.readLong(1LL, 2147483647LL, "height");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
