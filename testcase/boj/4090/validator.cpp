#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int case_cnt = 0;
    while (true) {
        int x = inf.readInt(0, 1000000, "X");
        inf.readEoln();

        if (x == 0) {
            break;
        }

        ++case_cnt;
        ensuref(x >= 10, "X=%d is below 10 at case %d", x, case_cnt);
        ensuref(case_cnt <= 100000, "too many test cases: %d", case_cnt);
    }

    inf.readEof();
}
