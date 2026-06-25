#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();

    long long sumA = 0;
    long long sumB = 0;
    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(0, 100000, "A_i");
        inf.readSpace();
        int b = inf.readInt(0, 100000, "B_i");
        inf.readEoln();

        ensuref(1 <= a + b && a + b <= 100000,
                "voter %d has invalid total votes: %d", i, a + b);
        sumA += a;
        sumB += b;
    }

    ensuref(sumB > sumA, "sum of B_i must be greater than sum of A_i");

    inf.readEof();
}
