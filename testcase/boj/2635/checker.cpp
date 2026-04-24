#include "testlib.h"
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int A;

// Reads an answer (jury or participant) from 'stream', checks its validity
// under the problem rules, and returns the sequence length.
// On any invalidity, quits with _wa if stream==ouf, or _fail if stream==ans.
int readAns(InStream &stream) {
    // Read claimed length
    int k = stream.readInt(1, 100000, "length");
    if (k < 2) {
        stream.quitf(_wa, "length must be at least 2, found %d", k);
    }
    // Read the sequence
    vector<int> s(k);
    for (int i = 0; i < k; i++) {
        char buf[50];
        sprintf(buf, "seq[%d]", i+1);
        // allow large range to catch negatives or too large values
        s[i] = stream.readInt(-1000000000, 1000000000, buf);
    }
    // Check first element equals A
    if (s[0] != A) {
        stream.quitf(_wa, "first element must be %d, found %d", A, s[0]);
    }
    // Check second element is a positive integer in [1, A]
    if (s[1] <= 0 || s[1] > A) {
        stream.quitf(_wa, "second element must be between 1 and %d, found %d", A, s[1]);
    }
    // Check recurrence and non-negativity
    for (int i = 2; i < k; i++) {
        if (s[i] < 0) {
            stream.quitf(_wa, "sequence[%d] is negative: %d", i+1, s[i]);
        }
        int expected = s[i-2] - s[i-1];
        if (s[i] != expected) {
            stream.quitf(_wa, "sequence[%d] is incorrect: expected %d, found %d",
                          i+1, expected, s[i]);
        }
    }
    // Ensure maximality: the next term would be negative
    int nxt = s[k-2] - s[k-1];
    if (nxt >= 0) {
        stream.quitf(_wa, "sequence is not maximal, can be extended with %d", nxt);
    }
    return k;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    A = inf.readInt();  // 1 <= A <= 30000

    // Read jury and participant answers
    int jlen = readAns(ans);
    int plen = readAns(ouf);

    // Compare lengths
    if (plen < jlen) {
        quitf(_wa, "length is not maximal: expected %d, found %d", jlen, plen);
    }
    if (plen > jlen) {
        quitf(_fail, "participant has longer sequence than jury: jury %d, participant %d",
              jlen, plen);
    }
    // If equal, accept
    quitf(_ok, "length = %d", plen);
    return 0;
}
