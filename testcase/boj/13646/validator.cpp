#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long N_MIN = 3LL;
    const long long N_MAX = (1LL << 31) - 1;  // Strictly less than 2^31

    int tc = 0;
    // Read test cases until EOF
    while (true) {
        if (inf.eof())
            break;
        long long N = inf.readLong(N_MIN, N_MAX, "N");
        inf.readEoln();
        ++tc;
        ensuref(tc <= 100000,
                "Number of test cases exceeds the limit of 100000: %d", tc);
    }

    inf.readEof();
    return 0;
}
