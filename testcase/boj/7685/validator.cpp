#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int case_count = 0;
    long long total_piles = 0;

    while (true) {
        int n = inf.readInt(0, 1000, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++case_count;
        // CHECK: The statement gives no number-of-cases limit; keep the local default cap.
        ensuref(case_count <= 100000, "too many test cases: %d", case_count);

        total_piles += n;
        // CHECK: The statement gives no total input-size limit; cap scalar input at local policy scale.
        ensuref(total_piles <= 5000000LL, "too many pile values: %lld", total_piles);

        setTestCase(case_count);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            inf.readInt(1, 1000000000, "k_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
