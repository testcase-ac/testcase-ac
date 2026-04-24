#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of meetings
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read each meeting's start and end time
    for (int i = 0; i < N; i++) {
        long long st = inf.readLong(0LL, 2147483647LL, "start_time");
        inf.readSpace();
        long long en = inf.readLong(0LL, 2147483647LL, "end_time");
        inf.readEoln();
        ensuref(st <= en,
                "Meeting %d has start time %lld greater than end time %lld",
                i, st, en);
    }

    inf.readEof();
    return 0;
}
