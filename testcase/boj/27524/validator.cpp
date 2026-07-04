#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int kMaxQ = 300000;
    constexpr int kMaxTotalStringLength = 1000000;
    constexpr long long kMinScore = -1000000000LL;
    constexpr long long kMaxScore = 1000000000LL;

    int q = inf.readInt(1, kMaxQ, "Q");
    inf.readEoln();

    int queryCount = 0;
    int totalStringLength = 0;

    for (int i = 1; i <= q; ++i) {
        string op = inf.readToken("[<>+-]", "query_type");

        if (op == "+" || op == "-") {
            ++queryCount;
            inf.readEoln();
            continue;
        }

        inf.readSpace();
        string str = inf.readToken("[a-z]{1,1000000}", "str");
        totalStringLength += static_cast<int>(str.size());
        ensuref(totalStringLength <= kMaxTotalStringLength,
                "total length of strings exceeds %d at query %d",
                kMaxTotalStringLength, i);

        inf.readSpace();
        inf.readLong(kMinScore, kMaxScore, "X");
        inf.readEoln();
    }

    ensuref(queryCount > 0, "at least one + or - query must exist");
    inf.readEof();
}
