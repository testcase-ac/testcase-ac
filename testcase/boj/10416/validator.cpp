#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MAX = 15;
    const int SUM_MAX = 30;

    while (true) {
        int n = inf.readInt(0, N_MAX, "n");
        if (n == 0) {
            inf.readEoln();
            break;
        }

        int sum = 0;
        for (int i = 0; i < n; ++i) {
            inf.readSpace();
            int x = inf.readInt(0, SUM_MAX, "rating");
            sum += x;
        }
        ensuref(sum <= SUM_MAX, "sum of ratings is %d, expected at most %d", sum, SUM_MAX);
        inf.readEoln();
    }

    inf.readEof();
}
