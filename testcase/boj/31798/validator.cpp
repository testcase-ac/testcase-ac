#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(0, 10000, "a");
    inf.readSpace();
    int b = inf.readInt(0, 10000, "b");
    inf.readSpace();
    int c = inf.readInt(0, 10000, "c");
    inf.readEoln();

    int zeroCount = (a == 0) + (b == 0) + (c == 0);
    ensuref(zeroCount == 1, "exactly one of a, b, c must be 0");

    long long answer = 0;
    if (a == 0) {
        answer = 1LL * c * c - b;
    } else if (b == 0) {
        answer = 1LL * c * c - a;
    } else {
        long long sum = 1LL * a + b;
        long long root = 0;
        while ((root + 1) * (root + 1) <= sum) {
            ++root;
        }
        ensuref(root * root == sum, "a + b must be a perfect square when c is 0");
        answer = root;
    }

    ensuref(answer > 0, "the missing value must be a positive integer");
    inf.readEof();
}
