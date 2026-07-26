#include "testlib.h"
#include <string>
using namespace std;

bool isSubsequence(const string& subsequence, const string& sequence) {
    size_t i = 0;
    for (char c : sequence)
        if (i < subsequence.size() && subsequence[i] == c) ++i;
    return i == subsequence.size();
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "t");
    inf.readEoln();

    long long sumX = 0;
    long long sumY = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);
        string x = inf.readToken("[a-z]+", "x");
        inf.readEoln();
        string y = inf.readToken("[a-z]+", "y");
        inf.readEoln();
        string w = inf.readToken("[a-z]+", "w");
        inf.readEoln();

        sumX += x.size();
        sumY += y.size();
        ensuref(sumX <= 200000, "sum of |X| exceeds 200000");
        ensuref(sumY <= 200000, "sum of |Y| exceeds 200000");
        ensuref(isSubsequence(w, x), "W is not a subsequence of X in test case %d", tc);
        ensuref(isSubsequence(w, y), "W is not a subsequence of Y in test case %d", tc);
    }

    inf.readEof();
}
