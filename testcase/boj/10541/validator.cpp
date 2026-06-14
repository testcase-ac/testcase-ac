#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long maxN = 1000000000000000000LL;
    const int maxWordLength = 1000000;
    const int maxK = 50000;

    long long n = inf.readLong(1LL, maxN, "N");
    inf.readEoln();

    string word = inf.readToken("[A-Z]+", "word");
    ensuref((int)word.size() <= maxWordLength, "word length is %d, exceeds %d",
            (int)word.size(), maxWordLength);
    inf.readEoln();

    int k = inf.readInt(1, maxK, "K");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        long long a = inf.readLong(1LL, n, "a_i");
        inf.readSpace();
        inf.readToken("[A-Z]", "c_i");
        inf.readEoln();
    }

    inf.readEof();
}
