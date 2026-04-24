#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int n, c, b;
vector<char> broken;

// Read an answer (bit string) from the given stream, check it, and return the number of bit changes.
// On participant stream (ouf), errors yield _wa; on jury stream (ans), errors yield _fail.
int readAns(InStream &stream) {
    // Read the bit string as one token
    string s = stream.readToken("bit string");
    int len = (int)s.size();
    if (len != n) {
        stream.quitf(_wa, "length of bit string is %d, but expected %d", len, n);
    }
    // Check characters and broken bits
    for (int i = 0; i < n; i++) {
        char ch = s[i];
        if (ch != '0' && ch != '1') {
            stream.quitf(_wa, "character #%d is '%c', but expected '0' or '1'", i+1, ch);
        }
        if (broken[i] && ch != '0') {
            stream.quitf(_wa, "bit %d is broken and must be '0', but found '%c'", i+1, ch);
        }
    }
    // Count bit changes
    int cnt = 0;
    for (int i = 0; i+1 < n; i++) {
        if (s[i] != s[i+1]) cnt++;
    }
    if (cnt != c) {
        stream.quitf(_wa, "number of bit changes is %d, but expected %d", cnt, c);
    }
    return cnt;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input
    n = inf.readInt();
    c = inf.readInt();
    b = inf.readInt();
    broken.assign(n, 0);
    for (int i = 0; i < b; i++) {
        int z = inf.readInt();
        // Mark broken bits (1-based to 0-based)
        broken[z-1] = 1;
    }

    // Read and validate jury answer
    int jans = readAns(ans);
    // Read and validate participant answer
    int pans = readAns(ouf);

    // Both should equal c, so jans == pans
    if (jans != pans) {
        // Should not really happen if both are valid, but just in case
        quitf(_wa, "jury's bit changes = %d, participant's = %d", jans, pans);
    }
    quitf(_ok, "correct, %d bit changes", pans);
    return 0;
}
