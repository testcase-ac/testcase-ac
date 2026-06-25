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

vector<vector<long long>> buildLengths() {
    vector<vector<long long>> len(MAX_LEVEL + 1, vector<long long>(26, 1));
    for (int level = 1; level <= MAX_LEVEL; ++level) {
        for (int c = 0; c < 26; ++c) {
            len[level][c] = 0;
            for (char out : NATO[c]) {
                len[level][c] = addCap(len[level][c], len[level - 1][out - 'A']);
            }
        }
    }
    return len;
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

string randomString() {
    vector<string> patterns = {
        "A", "Z", "HCPC", "HIBYE", "AZ", "JULIETT", "NATO", "XYZ"};
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        return rnd.any(patterns);
    }

    int n = rnd.next(1, mode <= 2 ? 8 : 28);
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (mode == 1) alphabet = "AEIOU";
    if (mode == 2) alphabet = "ABCXYZ";
    if (mode == 3) alphabet = "HJCPENATO";

    string s;
    for (int i = 0; i < n; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

long long randomPosition(long long currentLength) {
    vector<long long> candidates = {1, currentLength};
    if (currentLength >= 2) {
        candidates.push_back(2);
        candidates.push_back(currentLength - 1);
    }
    if (currentLength >= 3) {
        candidates.push_back((currentLength + 1) / 2);
    }
    if (currentLength > 1) {
        candidates.push_back(rnd.next(1LL, currentLength));
    }
    return rnd.any(candidates);
}

long long randomTransformStep() {
    int mode = rnd.next(0, 5);
    if (mode <= 2) return rnd.next(1LL, 4LL);
    if (mode == 3) return rnd.next(5LL, 20LL);
    if (mode == 4) return rnd.next(55LL, 80LL);
    return rnd.next(100000000000000000LL, LIM);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<vector<long long>> len = buildLengths();
    string s = randomString();
    int q = rnd.next(6, 35);

    println(s, q);

    int level = 0;
    long long currentLength = transformedLength(s, len, level);
    bool emittedQuery = false;

    for (int i = 0; i < q; ++i) {
        bool mustAsk = (i == q - 1 && !emittedQuery);
        bool doTransform = !mustAsk && (i == 0 || rnd.next(0, 99) < 45);

        if (doTransform) {
            long long x = randomTransformStep();
            println(1, x);
            level = static_cast<int>(min<long long>(MAX_LEVEL, level + x));
            currentLength = transformedLength(s, len, level);
        } else {
            println(2, randomPosition(currentLength));
            emittedQuery = true;
        }
    }

    return 0;
}
