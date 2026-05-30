#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int P = inf.readInt(1, 1000, "P");
    inf.readEoln();

    const int MAX_SUM = 500000;
    long long totalPeriod = 0;

    for (int tc = 0; tc < P; tc++) {
        setTestCase(tc + 1);
        // CHECK: The statement calls N the data set number but gives no bound,
        // ordering, or uniqueness rule. Cap it at the same scale as P.
        inf.readInt(1, 1000, "N");
        inf.readSpace();
        int M = inf.readInt(2, 1000000, "M");
        inf.readEoln();

        int prev = 1 % M;
        int curr = 1 % M;
        int period = 0;
        int remain = MAX_SUM - totalPeriod;
        while (true) {
            int nxt = prev + curr;
            if (nxt >= M) nxt %= M;
            prev = curr;
            curr = nxt;
            period++;
            ensuref(period <= remain,
                    "Pisano period k(%d) = %d exceeds remaining limit %d",
                    M, period, remain);
            if (prev == 1 && curr == 1) {
                break;
            }
        }
        totalPeriod += period;
    }

    ensuref(totalPeriod <= MAX_SUM,
            "Sum of all k(M) = %lld exceeds %d",
            totalPeriod, MAX_SUM);

    inf.readEof();
    return 0;
}
