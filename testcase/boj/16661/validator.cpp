#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20, "t");
    inf.readEoln();

    int total_n = 0, total_m = 0;

    for (int testcase = 0; testcase < t; ++testcase) {
        setTestCase(testcase + 1);

        int n = inf.readInt(1, 150, "n");
        inf.readSpace();
        int m = inf.readInt(1, 150, "m");
        inf.readEoln();

        ensuref(n + m <= 150, "In test case %d: n + m = %d + %d = %d > 150", testcase + 1, n, m, n + m);

        total_n += n;
        total_m += m;

        vector<string> allowed(n);
        for (int i = 0; i < n; ++i) {
            allowed[i] = inf.readLine("[01]{"+to_string(m)+"}", "allowed_row");
            ensuref((int)allowed[i].size() == m, "In test case %d, row %d: length is %d, expected %d", testcase+1, i+1, (int)allowed[i].size(), m);
        }
    }

    ensuref(total_n + total_m <= 150, "Sum of n + m over all test cases exceeds 150: %d + %d = %d", total_n, total_m, total_n + total_m);

    inf.readEof();
}
