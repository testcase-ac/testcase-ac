#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for the number of test cases.
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int zero_count = 0;
        for (int row = 1; row <= 9; ++row) {
            string line = inf.readLine("[0-9]{9}", "row");
            for (char ch : line) {
                if (ch == '0') {
                    ++zero_count;
                }
            }
        }

        ensuref(zero_count == 5, "test case %d has %d zeroes, expected 5", tc, zero_count);
    }

    inf.readEof();
}
