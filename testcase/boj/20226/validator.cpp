#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long P_MIN = 1;
    const long long P_MAX = 999999999999999LL; // p < 10^15
    const int DATASET_LIMIT = 300;

    int cnt = 0;
    while (true) {
        // Read p, allowing 0 for the sentinel, or [1, P_MAX] for actual datasets
        long long p = inf.readLong(0LL, P_MAX, "p");
        inf.readEoln();
        if (p == 0) break;
        // It's a real dataset
        cnt++;
        ensuref(cnt <= DATASET_LIMIT,
                "Number of datasets exceeds the limit %d: found at least %d",
                DATASET_LIMIT, cnt);
        // p > 0 is guaranteed by readLong lower bound = 0 and p != 0 here
    }

    inf.readEof();
    return 0;
}
