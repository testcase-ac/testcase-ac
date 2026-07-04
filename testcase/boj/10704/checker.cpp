#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int n, k;

struct Output {
    bool impossible;
    vector<int> sequence;
};

int parseIntToken(InStream& stream, const string& token, int index, TResult verdict) {
    if (token.empty()) {
        stream.quitf(verdict, "empty token for sequence[%d]", index);
    }

    int start = 0;
    if (token[0] == '+') {
        start = 1;
    }
    if (start == (int)token.size()) {
        stream.quitf(verdict, "invalid integer token '%s' for sequence[%d]", token.c_str(), index);
    }
    for (int i = start; i < (int)token.size(); ++i) {
        if (token[i] < '0' || token[i] > '9') {
            stream.quitf(verdict, "invalid integer token '%s' for sequence[%d]", token.c_str(), index);
        }
    }

    long long value = 0;
    for (int i = start; i < (int)token.size(); ++i) {
        value = value * 10 + (token[i] - '0');
        if (value > n) {
            stream.quitf(verdict, "sequence[%d]=%lld is outside [1, %d]", index, value, n);
        }
    }
    if (value < 1) {
        stream.quitf(verdict, "sequence[%d]=%lld is outside [1, %d]", index, value, n);
    }
    return (int)value;
}

int longestIncreasing(const vector<int>& a) {
    vector<int> tails;
    tails.reserve(a.size());
    for (int x : a) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) {
            tails.push_back(x);
        } else {
            *it = x;
        }
    }
    return (int)tails.size();
}

int longestDecreasing(const vector<int>& a) {
    vector<int> tails;
    tails.reserve(a.size());
    for (int x : a) {
        int y = -x;
        auto it = lower_bound(tails.begin(), tails.end(), y);
        if (it == tails.end()) {
            tails.push_back(y);
        } else {
            *it = y;
        }
    }
    return (int)tails.size();
}

void validateSequence(InStream& stream, const vector<int>& sequence, TResult verdict) {
    vector<char> seen(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        int value = sequence[i];
        if (seen[value]) {
            stream.quitf(verdict, "value %d appears more than once", value);
        }
        seen[value] = 1;
    }

    int lis = longestIncreasing(sequence);
    int lds = longestDecreasing(sequence);
    int longest = max(lis, lds);
    if (longest != k) {
        stream.quitf(verdict,
                     "longest monotone subsequence length is %d, expected %d (LIS=%d, LDS=%d)",
                     longest,
                     k,
                     lis,
                     lds);
    }
}

Output readOutput(InStream& stream, TResult verdict) {
    string first = stream.readToken();
    if (first == "-1") {
        stream.readEoln();
        stream.readEof();
        return {true, {}};
    }

    vector<int> sequence(n);
    sequence[0] = parseIntToken(stream, first, 1, verdict);
    for (int i = 1; i < n; ++i) {
        stream.readSpace();
        sequence[i] = parseIntToken(stream, stream.readToken(), i + 1, verdict);
    }
    stream.readEoln();
    stream.readEof();

    validateSequence(stream, sequence, verdict);
    return {false, sequence};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();

    Output jury = readOutput(ans, _fail);
    Output participant = readOutput(ouf, _wa);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid sequence while jury claimed impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant claimed impossible while jury has a valid sequence");
    }

    quitf(_ok, "valid sequence with longest monotone subsequence length %d", k);
}
