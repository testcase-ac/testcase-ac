#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 1000000;
    const int MAX_M = 1000000;
    const int MAX_CD = 1000000000;
    const int MAX_CASES = 100000;

    int case_cnt = 0;
    while (true) {
        // Read N and M
        int N = inf.readInt(0, MAX_N, "N");
        inf.readSpace();
        int M = inf.readInt(0, MAX_M, "M");
        inf.readEoln();

        if (N == 0 && M == 0) {
            break;
        }

        ++case_cnt;
        ensuref(case_cnt <= MAX_CASES, "Too many test cases: %d (max %d)", case_cnt, MAX_CASES);

        // Read N lines: Sang-geun's CDs
        vector<int> sang(N);
        for (int i = 0; i < N; ++i) {
            sang[i] = inf.readInt(0, MAX_CD, "sang_cd");
            inf.readEoln();
        }
        // Check strictly increasing order (no duplicates)
        for (int i = 1; i < N; ++i) {
            ensuref(sang[i] > sang[i-1], "Sang-geun's CD numbers must be strictly increasing at index %d: %d <= %d", i, sang[i], sang[i-1]);
        }

        // Read M lines: Sun-young's CDs
        vector<int> sun(M);
        for (int i = 0; i < M; ++i) {
            sun[i] = inf.readInt(0, MAX_CD, "sun_cd");
            inf.readEoln();
        }
        // Check strictly increasing order (no duplicates)
        for (int i = 1; i < M; ++i) {
            ensuref(sun[i] > sun[i-1], "Sun-young's CD numbers must be strictly increasing at index %d: %d <= %d", i, sun[i], sun[i-1]);
        }
    }

    inf.readEof();
}
