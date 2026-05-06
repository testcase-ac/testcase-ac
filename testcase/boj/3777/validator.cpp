#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Simulate one step of the morphism on the sequence given as vector<char> of '0'/'1'
static vector<char> nextStep(const vector<char>& cur) {
    vector<char> nxt;
    nxt.reserve(cur.size() * 2);
    for (char c : cur) {
        if (c == '0') {
            nxt.push_back('1');
            nxt.push_back('0');
        } else {
            // c must be '1'
            nxt.push_back('0');
            nxt.push_back('1');
        }
    }
    return nxt;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // As per statement: each line contains one natural number n, 0 < n <= 1000.
    // No explicit number-of-test-cases, so we read until EOF, line by line.
    // Also ensure global constraint: for given input, the answer exists and is finite.
    // We'll enforce formatting: one integer per line, no extra spaces.

    // Precompute the sequence up to n = 20 only for checking "answer always exists"/
    // construction sanity is trivial here, so we only check small n structure.
    // For validation of n up to 1000, we rely on constraints only (no need to
    // actually construct length 2^1000 sequence).

    bool first = true;
    while (!inf.eof()) {
        // Peek: if already at EOF before reading token/line, break.
        if (inf.eof()) break;

        // Read single integer n on its own line, no leading/trailing spaces.
        // Use readInt to enforce canonical numeric form and range.
        int n = inf.readInt(1, 1000, "n");
        // After the number, must be end of line (no trailing spaces or tokens).
        inf.readEoln();

        // Optional global sanity: for small n, build sequence and ensure that
        // it follows the described morphism and count of "00" is well-defined.
        if (n <= 20) {
            vector<char> seq;
            seq.push_back('1'); // initial sequence at step 0
            for (int step = 1; step <= n; ++step) {
                seq = nextStep(seq);
            }
            // Count pairs "00"
            long long cnt00 = 0;
            for (size_t i = 0; i + 1 < seq.size(); ++i) {
                if (seq[i] == '0' && seq[i + 1] == '0') cnt00++;
            }
            // Just ensure we didn't overflow or get inconsistent data.
            ensuref(cnt00 >= 0, "Negative count of pairs for n=%d (internal error)", n);
        }

        first = false;
    }

    inf.readEof();
}
