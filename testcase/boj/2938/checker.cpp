#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> input_a, sorted_a;

// Reads either "-1" or exactly n integers from stream.
// On format errors quits with _wa (or _fail if stream==ans).
// Returns empty vector for "-1", otherwise the sequence of length n.
vector<int> readAns(InStream &stream) {
    stream.skipBlanks();
    if (stream.eof())
        stream.quitf(_wa, "no output");
    string tok = stream.readToken();
    if (tok == "-1") {
        // should be no more tokens
        stream.skipBlanks();
        if (!stream.eof())
            stream.quitf(_wa, "extra tokens after -1");
        return vector<int>();
    }
    // tok must be a positive integer
    for (char c : tok) {
        if (!isdigit(c))
            stream.quitf(_wa, "invalid token '%s'", tok.c_str());
    }
    long long x = 0;
    try {
        x = stoll(tok);
    } catch (...) {
        stream.quitf(_wa, "invalid integer '%s'", tok.c_str());
    }
    if (x < 1 || x > 1000000)
        stream.quitf(_wa, "number %lld out of range [1,1000000]", x);
    vector<int> res;
    res.push_back((int)x);
    for (int i = 1; i < n; i++) {
        int v = stream.readInt(1, 1000000, format("output[%d]", i+1).c_str());
        res.push_back(v);
    }
    stream.skipBlanks();
    if (!stream.eof())
        stream.quitf(_wa, "extra tokens after output");
    return res;
}

// Validates that seq is a permutation of input_a and
// that for all adjacent pairs, (a[i]+a[i+1])%3 != 0.
// On failure quits via stream.quitf.
void validateSeq(const vector<int> &seq, InStream &stream) {
    if ((int)seq.size() != n)
        stream.quitf(_wa, "expected %d numbers, found %d", n, (int)seq.size());
    vector<int> tmp = seq;
    sort(tmp.begin(), tmp.end());
    if (tmp != sorted_a)
        stream.quitf(_wa, "output is not a permutation of input");
    for (int i = 0; i + 1 < n; i++) {
        int s = seq[i] + seq[i+1];
        if (s % 3 == 0) {
            stream.quitf(_wa,
                "sum of output[%d] and output[%d] (%d+%d=%d) is divisible by 3",
                i+1, i+2, seq[i], seq[i+1], s);
        }
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // read input
    n = inf.readInt();
    input_a.resize(n);
    for (int i = 0; i < n; i++)
        input_a[i] = inf.readInt(1, 1000000);
    sorted_a = input_a;
    sort(sorted_a.begin(), sorted_a.end());
    // read jury and participant answers
    vector<int> j_seq = readAns(ans);
    vector<int> p_seq = readAns(ouf);
    // if jury says impossible
    if (j_seq.empty()) {
        if (!p_seq.empty())
            quitf(_wa, "expected -1, found a sequence");
        else
            quitf(_ok, "both say -1");
    }
    // jury says possible: validate jury
    validateSeq(j_seq, ans);
    // now check participant
    if (p_seq.empty())
        quitf(_wa, "expected a sequence of length %d, found -1", n);
    validateSeq(p_seq, ouf);
    quitf(_ok, "valid arrangement");
    return 0;
}
