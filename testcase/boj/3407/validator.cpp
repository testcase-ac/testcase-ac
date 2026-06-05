#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not specify T; use the local default cap.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalLength = 0;
    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        string word = inf.readToken("[a-z]{1,50000}", "word");
        inf.readEoln();

        totalLength += static_cast<long long>(word.size());
        // CHECK: The statement has only a per-word length cap; keep total string input practical.
        ensuref(totalLength <= 10000000LL,
                "total word length exceeds practical cap: %lld",
                totalLength);
    }

    inf.readEof();
}
