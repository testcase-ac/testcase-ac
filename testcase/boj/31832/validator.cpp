#include "testlib.h"

#include <string>

using namespace std;

bool isGoodTeamName(const string& s) {
    int lower = 0;
    int upper = 0;
    bool hasNonDigit = false;

    for (char c : s) {
        if ('a' <= c && c <= 'z') {
            ++lower;
            hasNonDigit = true;
        } else if ('A' <= c && c <= 'Z') {
            ++upper;
            hasNonDigit = true;
        } else if (c == '-') {
            hasNonDigit = true;
        }
    }

    return upper <= lower && s.size() <= 10 && hasNonDigit;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    int goodCount = 0;
    for (int i = 1; i <= n; ++i) {
        string s = inf.readToken("[a-zA-Z0-9-]{1,20}", "S_i");
        inf.readEoln();

        if (isGoodTeamName(s)) {
            ++goodCount;
        }
    }

    ensuref(goodCount == 1, "expected exactly one valid team name, found %d", goodCount);

    inf.readEof();
    return 0;
}
