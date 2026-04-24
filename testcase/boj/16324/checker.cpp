#include "testlib.h"
#include <string>
#include <vector>
#include <cctype>
using namespace std;

long long a, b, c, d;

// This struct holds the parsed answer.
// If impossible == true, it means the output was "impossible".
// Otherwise we have validated the bitstring and its counts match (a,b,c,d).
struct Answer {
    bool impossible;
};

// Reads an answer from the given stream (ans or ouf).
// If the stream prints "impossible", returns {true}.
// Otherwise reads a bitstring, checks it's non-empty and consists of '0'/'1',
// computes the subsequence counts 00,01,10,11 and compares to (a,b,c,d).
// On any mismatch or invalid format, calls stream.quitf(_wa,...) or stream.quitf(_fail,...)
// depending on which stream is passed (testlib handles verdict conversion).
Answer readAns(InStream &stream) {
    // Read one token
    string s = stream.readToken();
    if (s == "impossible") {
        // Participant/jury claims no solution.
        return { true };
    }
    // It must be a non-empty bitstring
    if (s.empty()) {
        stream.quitf(_wa, "empty string is not allowed");
    }
    // Validate and count total zeros and ones
    long long total0 = 0, total1 = 0;
    for (char ch : s) {
        if (ch == '0') total0++;
        else if (ch == '1') total1++;
        else {
            stream.quitf(_wa, "invalid character '%c' in output; only '0' and '1' are allowed", ch);
        }
    }
    if (total0 + total1 == 0) {
        stream.quitf(_wa, "empty bitstring is not allowed");
    }
    // Compute subsequence counts
    // count00 = number of pairs of zeros = total0 choose 2
    long long c00 = total0 * (total0 - 1) / 2;
    // count11 = total1 choose 2
    long long c11 = total1 * (total1 - 1) / 2;
    // count01 = sum over each '0' of number of '1's to its right
    long long ones_rem = total1;
    long long c01 = 0;
    for (char ch : s) {
        if (ch == '1') {
            ones_rem--;
        } else { // '0'
            c01 += ones_rem;
        }
    }
    // count10 = sum over each '1' of number of '0's to its right
    long long zeros_rem = total0;
    long long c10 = 0;
    for (char ch : s) {
        if (ch == '0') {
            zeros_rem--;
        } else { // '1'
            c10 += zeros_rem;
        }
    }
    // Compare to required (a,b,c,d)
    if (c00 != a || c01 != b || c10 != c || c11 != d) {
        stream.quitf(_wa,
            "subsequence counts mismatch: expected (00,01,10,11) = (%lld,%lld,%lld,%lld), "
            "found (%lld,%lld,%lld,%lld)",
            a, b, c, d, c00, c01, c10, c11);
    }
    return { false };
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input parameters
    a = inf.readLong();
    b = inf.readLong();
    c = inf.readLong();
    d = inf.readLong();
    // Read jury and participant answers
    Answer jans = readAns(ans);
    Answer pans = readAns(ouf);
    // Compare
    if (jans.impossible && pans.impossible) {
        quitf(_ok, "both say impossible");
    }
    if (jans.impossible && !pans.impossible) {
        quitf(_wa, "found solution while expected impossible");
    }
    if (!jans.impossible && pans.impossible) {
        quitf(_wa, "no solution while expected solution");
    }
    // Both provided valid bitstrings matching (a,b,c,d)
    quitf(_ok, "correct solution");
    return 0;
}
