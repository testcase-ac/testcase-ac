#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int kMaxN = 200000;
    const long long kMaxTotalLength = 2000000LL;

    int n = inf.readInt(2, kMaxN, "n");
    inf.readEoln();
    ensuref(n % 2 == 0, "n must be even: %d", n);

    int wordLength = -1;
    long long totalLength = 0;
    for (int i = 0; i < n; ++i) {
        // CHECK: The statement says "words" but does not specify an alphabet, so any non-whitespace token is accepted.
        string word = inf.readToken("[^ ]+", "word");
        inf.readEoln();

        if (i == 0) {
            wordLength = static_cast<int>(word.size());
        } else {
            ensuref(static_cast<int>(word.size()) == wordLength,
                    "word %d length is %d, expected %d",
                    i + 1,
                    static_cast<int>(word.size()),
                    wordLength);
        }

        totalLength += static_cast<long long>(word.size());
        ensuref(totalLength <= kMaxTotalLength,
                "total word length exceeds %lld after word %d",
                kMaxTotalLength,
                i + 1);
    }

    inf.readEof();
}
