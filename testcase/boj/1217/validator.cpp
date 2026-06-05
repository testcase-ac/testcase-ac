#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 200000;
    const int MAX_M = 20000;
    // CHECK: The statement does not bound the number of datasets; use the local
    // default practical cap for multi-case inputs.
    const int MAX_CASES = 100000;
    // CHECK: The statement gives a per-dataset rule cap but no total cap.
    // Keep total scalar input safely below the local practical token limit.
    const long long MAX_TOTAL_RULES = 2000000;

    int caseCount = 0;
    long long totalRules = 0;

    while (true) {
        int n = inf.readInt(0, MAX_N, "N");
        inf.readSpace();
        int m = inf.readInt(0, MAX_M, "M");
        inf.readEoln();

        if (n == 0 && m == 0) {
            break;
        }

        ++caseCount;
        setTestCase(caseCount);
        ensuref(caseCount <= MAX_CASES, "too many datasets: %d", caseCount);

        // CHECK: Only 0 0 is described as the terminator; a real dataset needs
        // at least one symptom type so signed states can refer to 1..M.
        ensuref(m >= 1, "non-terminating dataset %d has M = 0", caseCount);

        totalRules += n;
        ensuref(totalRules <= MAX_TOTAL_RULES,
                "total number of rules exceeds %lld at dataset %d",
                MAX_TOTAL_RULES,
                caseCount);

        for (int i = 1; i <= n; ++i) {
            int a = inf.readInt(-m, m, "state_a");
            inf.readSpace();
            int b = inf.readInt(-m, m, "state_b");
            inf.readEoln();

            ensuref(a != 0, "dataset %d rule %d has zero first state", caseCount, i);
            ensuref(b != 0, "dataset %d rule %d has zero second state", caseCount, i);
        }
    }

    inf.readEof();
    return 0;
}
