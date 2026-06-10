#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    string stalls = inf.readToken("[01]{2,100000}", "stalls");
    inf.readEoln();
    inf.readEof();

    ensuref((int)stalls.size() == n,
            "stalls length must be n: length=%d, n=%d", (int)stalls.size(), n);

    int emptyCount = 0;
    for (char c : stalls) {
        if (c == '0') {
            ++emptyCount;
        }
    }
    ensuref(emptyCount >= 2, "stalls must contain at least two zeroes");
}
