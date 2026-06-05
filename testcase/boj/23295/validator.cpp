#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();
    (void)t;

    long long totalK = 0;
    for (int participant = 1; participant <= n; ++participant) {
        int k = inf.readInt(1, 500000, "K");
        inf.readEoln();

        totalK += k;
        ensuref(totalK <= 500000,
                "sum of K exceeds 500000 after participant %d: %lld",
                participant,
                totalK);

        int previousEnd = -1;
        for (int interval = 1; interval <= k; ++interval) {
            int start = inf.readInt(0, 99999, "S_i");
            inf.readSpace();
            int end = inf.readInt(start + 1, 100000, "E_i");
            inf.readEoln();

            if (interval > 1) {
                ensuref(previousEnd < start,
                        "participant %d interval %d must start after previous end: previous E=%d, S=%d",
                        participant,
                        interval,
                        previousEnd,
                        start);
            }
            previousEnd = end;
        }
    }

    inf.readEof();
}
