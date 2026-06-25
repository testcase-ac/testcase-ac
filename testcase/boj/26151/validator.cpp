#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace {

const long long LIM = 1000000000000000000LL;
const int MAX_LEVEL = 60;

const string NATO[26] = {
    "ALFA", "BRAVO", "CHARLIE", "DELTA", "ECHO", "FOXTROT", "GOLF",
    "HOTEL", "INDIA", "JULIETT", "KILO", "LIMA", "MIKE", "NOVEMBER",
    "OSCAR", "PAPA", "QUEBEC", "ROMEO", "SIERRA", "TANGO", "UNIFORM",
    "VICTOR", "WHISKEY", "XRAY", "YANKEE", "ZULU"};

long long addCap(long long a, long long b) {
    if (a >= LIM || b >= LIM || a > LIM - b) {
        return LIM;
    }
    return a + b;
}

long long transformedLength(const string& s,
                            const vector<vector<long long>>& len,
                            int level) {
    long long result = 0;
    for (char c : s) {
        result = addCap(result, len[level][c - 'A']);
    }
    return result;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<vector<long long>> len(MAX_LEVEL + 1, vector<long long>(26, 1));
    for (int level = 1; level <= MAX_LEVEL; ++level) {
        for (int c = 0; c < 26; ++c) {
            len[level][c] = 0;
            for (char out : NATO[c]) {
                len[level][c] = addCap(len[level][c], len[level - 1][out - 'A']);
            }
        }
    }

    string s = inf.readToken("[A-Z]{1,200000}", "S");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    int level = 0;
    long long currentLength = transformedLength(s, len, level);
    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 2, "query_type");
        inf.readSpace();
        if (type == 1) {
            long long x = inf.readLong(1LL, LIM, "x");
            level = static_cast<int>(min<long long>(MAX_LEVEL, level + x));
            currentLength = transformedLength(s, len, level);
        } else {
            long long p = inf.readLong(1LL, LIM, "p");
            ensuref(p <= currentLength,
                    "query %d has p=%lld greater than current length %lld",
                    i, p, currentLength);
        }
        inf.readEoln();
    }

    inf.readEof();
}
