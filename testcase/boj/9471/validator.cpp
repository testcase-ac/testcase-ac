#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read number of test cases P
    int P = inf.readInt(1, 1000, "P");
    inf.readEoln();

    vector<bool> seenN(P + 1, false);
    const int MAX_SUM = 500000;
    long long totalPeriod = 0;

    for (int tc = 0; tc < P; tc++) {
        setTestCase(tc + 1);
        // Read test case number N and parameter M
        int N = inf.readInt(1, P, "N");
        inf.readSpace();
        int M = inf.readInt(2, 1000000, "M");
        inf.readEoln();

        // Check N is unique
        ensuref(!seenN[N], "Duplicate test case number: %d", N);
        seenN[N] = true;

        // Compute Pisano period k(M), but abort early if exceeding budget
        int prev = 1 % M;
        int curr = 1 % M;
        int period = 0;
        int remain = MAX_SUM - totalPeriod;
        // We know k(M) is even for M>2, but we compute directly
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

    // Ensure all test case numbers 1..P appeared
    for (int i = 1; i <= P; i++) {
        ensuref(seenN[i], "Missing test case number: %d", i);
    }
    // Final sum check (redundant due to early checks, but for clarity)
    ensuref(totalPeriod <= MAX_SUM,
            "Sum of all k(M) = %lld exceeds %d",
            totalPeriod, MAX_SUM);

    inf.readEof();
    return 0;
}
