#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int kMinValue = -2147483647 - 1;
    constexpr int kMaxValue = 2147483647;
    // CHECK: The statement gives an EOF-terminated list with no count, so cap it
    // at the local default maximum for unspecified testcase counts.
    constexpr int kMaxCount = 100000;

    int count = 0;
    while (!inf.eof()) {
        ++count;
        ensuref(count <= kMaxCount, "too many integers: more than %d", kMaxCount);
        inf.readInt(kMinValue, kMaxValue, "n");
        inf.readEoln();
    }

    ensuref(count > 0, "input must contain at least one integer");
    inf.readEof();
}
