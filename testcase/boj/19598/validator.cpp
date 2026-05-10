#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of meetings N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // For each meeting, read start and end times
    for (int i = 1; i <= N; i++) {
        long long start = inf.readLong(0LL, 2147483647LL, "start_" + to_string(i));
        inf.readSpace();
        long long endt  = inf.readLong(0LL, 2147483647LL, "end_"   + to_string(i));
        inf.readEoln();

        // Check that start < end
        ensuref(start < endt,
                "Meeting %d has invalid times: start = %lld, end = %lld (start must be < end)",
                i, start, endt);
    }

    inf.readEof();
    return 0;
}
