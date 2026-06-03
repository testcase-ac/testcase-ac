#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for the number of test cases.
    int testCases = inf.readInt(1, 100000, "testCases");
    inf.readEoln();

    long long totalStringLength = 0;
    for (int tc = 1; tc <= testCases; ++tc) {
        setTestCase(tc);

        string word = inf.readToken("[A-Z]{1,10000}", "W");
        inf.readEoln();

        string text = inf.readToken("[A-Z]{1,1000000}", "T");
        inf.readEoln();

        ensuref(word.size() <= text.size(),
                "|W| must not exceed |T|, got |W|=%d and |T|=%d",
                static_cast<int>(word.size()), static_cast<int>(text.size()));

        totalStringLength += static_cast<long long>(word.size()) +
                             static_cast<long long>(text.size());
        // CHECK: The statement has per-case string bounds but no total input-size bound.
        ensuref(totalStringLength <= 10000000LL,
                "total string length exceeds practical cap: %lld", totalStringLength);
    }

    inf.readEof();
}
