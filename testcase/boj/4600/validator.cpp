#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_B = 20;
    const int MAX_P = 20;
    const int MAX_C = 5;
    const int MAX_T = 100;
    const int MIN_B = 1;
    const int MIN_P = 1;
    const int MIN_C = 1;
    const int MIN_T = 1;

    int test_case_count = 0;

    while (true) {
        // Peek the next two integers to check for 0 0 (end of input)
        int b = inf.readInt(-MAX_B, 0, "B"); // allow 0 for end marker
        inf.readSpace();
        int p = inf.readInt(0, MAX_P, "P"); // allow 0 for end marker
        inf.readEoln();

        if (b == 0 && p == 0) {
            break;
        }

        // Now validate b and p for a real test case
        ensuref(b <= -MIN_B && b >= -MAX_B, "B (number of bridges) must be negative and in range [-%d, -%d], got %d", MAX_B, MIN_B, b);
        ensuref(p >= MIN_P && p <= MAX_P, "P (number of people) must be in range [%d, %d], got %d", MIN_P, MAX_P, p);

        ++test_case_count;
        ensuref(test_case_count <= 100000, "Too many test cases: %d", test_case_count);

        int B = -b; // positive number of bridges

        for (int i = 0; i < B; ++i) {
            int c = inf.readInt(MIN_C, MAX_C, "C");
            inf.readSpace();
            int t = inf.readInt(MIN_T, MAX_T, "T");
            inf.readEoln();
        }
    }

    inf.readEof();
}
