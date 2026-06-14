#include "testlib.h"

#include <string>

using namespace std;

const int MAX_N = 200000;
const int MAX_Q = 200000;
const int MAX_COLOR = 1000000000;
const int MAX_TOTAL = 200000;

int readColorListLine(int maxCount, const string& countName, const string& colorName) {
    int count = inf.readInt(0, maxCount, countName);
    for (int i = 0; i < count; ++i) {
        inf.readSpace();
        inf.readInt(1, MAX_COLOR, colorName);
    }
    inf.readEoln();
    return count;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, MAX_N, "N");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(1, MAX_COLOR, "initial_color");
    }
    inf.readEoln();

    int q = inf.readInt(1, MAX_Q, "Q");
    inf.readEoln();

    int totalA = 0;
    int totalB = 0;
    for (int i = 0; i < q; ++i) {
        setTestCase(i + 1);

        int a = readColorListLine(MAX_N, "a_i", "A_i_color");
        totalA += a;
        ensuref(totalA <= MAX_TOTAL, "sum of a_i exceeds %d", MAX_TOTAL);

        int b = readColorListLine(MAX_N, "b_i", "B_i_color");
        totalB += b;
        ensuref(totalB <= MAX_TOTAL, "sum of b_i exceeds %d", MAX_TOTAL);
    }

    inf.readEof();
}
