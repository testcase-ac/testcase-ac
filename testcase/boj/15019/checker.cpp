#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int n, k;
vector<string> chars;

// This function reads one answer string from the given stream,
// validates it, computes and returns the maximum similarity
// to the input characters.
// On invalid answer, it quits with _wa if stream == ouf, or _fail if stream == ans.
int readAns(InStream &stream) {
    string s = stream.readToken();
    if ((int)s.size() != k) {
        stream.quitf(_wa, "answer should be a string of length %d, found length %d", k, (int)s.size());
    }
    for (int i = 0; i < k; i++) {
        if (s[i] != '0' && s[i] != '1') {
            stream.quitf(_wa, "answer contains invalid character '%c' at position %d, expected '0' or '1'", s[i], i+1);
        }
    }
    int maxSim = 0;
    for (int i = 0; i < n; i++) {
        int sim = 0;
        for (int j = 0; j < k; j++) {
            if (s[j] == chars[i][j]) sim++;
        }
        if (sim > maxSim) maxSim = sim;
    }
    return maxSim;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    n = inf.readInt();
    k = inf.readInt();
    chars.resize(n);
    for (int i = 0; i < n; i++) {
        chars[i] = inf.readToken();
        // We trust the input is correct per problem statement
    }
    // Read jury's answer and participant's answer, compute their max similarities
    int jans = readAns(ans);
    int pans = readAns(ouf);
    // Compare
    if (pans > jans) {
        quitf(_wa, "participant's maximum similarity = %d is greater than jury's = %d", pans, jans);
    } else if (pans == jans) {
        quitf(_ok, "maximum similarity = %d", pans);
    } else {
        // Participant found a better answer than jury
        quitf(_fail, "participant's maximum similarity = %d is less than jury's = %d", pans, jans);
    }
    return 0;
}
