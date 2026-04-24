#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

struct Probe {
    int x, y, r;
};

int K, N;
vector<Probe> probes;

// Reads an answer (either from jury = ans, or contestant = ouf).
// Returns an empty vector if the answer is "NONE",
// otherwise returns a vector<int> of length K with 0/1.
// If any check fails, quits with _wa (for ouf) or _fail (for ans).
vector<int> readAns(InStream& stream) {
    vector<int> res;
    // Read the first token
    string s = stream.readToken();
    if (s == "NONE") {
        // No further tokens allowed
        if (!stream.seekEof())
            stream.quitf(_wa, "extra content after NONE");
        return res; // empty => indicates NONE
    }
    // Otherwise s must be the solution string of length K
    if ((int)s.size() != K) {
        stream.quitf(_wa, "string length = %d, expected = %d", (int)s.size(), K);
    }
    res.resize(K);
    for (int i = 0; i < K; i++) {
        if (s[i] == '#') {
            res[i] = 1;
        } else if (s[i] == '-') {
            res[i] = 0;
        } else {
            stream.quitf(_wa, "invalid character '%c' at position %d", s[i], i+1);
        }
    }
    // No extra tokens allowed
    if (!stream.seekEof())
        stream.quitf(_wa, "extra content after answer string");
    // Validate all probes
    for (auto& p : probes) {
        int sum = 0;
        for (int i = p.x - 1; i < p.y; i++)
            sum += res[i];
        if (sum != p.r) {
            stream.quitf(_wa,
                "constraint [%d,%d] requires %d objects, found %d",
                p.x, p.y, p.r, sum);
        }
    }
    return res;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    K = inf.readInt();
    N = inf.readInt();
    probes.reserve(N);
    for (int i = 0; i < N; i++) {
        Probe p;
        p.x = inf.readInt();
        p.y = inf.readInt();
        p.r = inf.readInt();
        probes.push_back(p);
    }
    // Read jury answer and contestant answer
    vector<int> jans = readAns(ans);
    vector<int> pans = readAns(ouf);
    bool jnone = jans.empty();
    bool pnone = pans.empty();
    if (jnone && pnone) {
        quitf(_ok, "NONE");
    }
    if (jnone && !pnone) {
        quitf(_wa, "expected NONE, found a solution");
    }
    if (!jnone && pnone) {
        quitf(_wa, "found NONE, but a solution exists");
    }
    // Both provided valid (possibly different) solutions
    quitf(_ok, "OK");
    return 0;
}
