#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll R, G;

// readAns reads all triples (N, X, Y) from the given stream,
// checks their validity, and returns them as a sorted vector.
// If any check fails on the contestant's output (stream == ouf), it quits with _wa,
// if it fails on the jury's answer (stream == ans), it quits with _fail.
vector<tuple<ll,ll,ll>> readAns(InStream &stream) {
    vector<tuple<ll,ll,ll>> res;
    set<ll> usedN;
    // Read until EOF
    while (!stream.seekEof()) {
        ll n = stream.readLong();
        ll x = stream.readLong();
        ll y = stream.readLong();
        // Basic validity
        if (n <= 0)
            stream.quitf(_wa, "found non-positive N = %lld", n);
        if (x <= 0)
            stream.quitf(_wa, "found non-positive X = %lld", x);
        if (y <= 0)
            stream.quitf(_wa, "found non-positive Y = %lld", y);
        // Check that N divides R and G exactly
        if (n * x != R)
            stream.quitf(_wa, "inconsistent: N * X = %lld * %lld = %lld but R = %lld",
                          n, x, n*x, R);
        if (n * y != G)
            stream.quitf(_wa, "inconsistent: N * Y = %lld * %lld = %lld but G = %lld",
                          n, y, n*y, G);
        // Check no duplicate N
        if (usedN.count(n))
            stream.quitf(_wa, "duplicate N = %lld", n);
        usedN.insert(n);
        res.emplace_back(n, x, y);
    }
    // Sort by N
    sort(res.begin(), res.end(), [](auto &a, auto &b){
        return get<0>(a) < get<0>(b);
    });
    return res;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    R = inf.readLong();
    G = inf.readLong();
    // Read jury's answer and participant's answer
    vector<tuple<ll,ll,ll>> jans = readAns(ans);
    vector<tuple<ll,ll,ll>> pans = readAns(ouf);
    // Compare
    if (jans != pans) {
        // Check sizes first
        if (jans.size() != pans.size()) {
            quitf(_wa, "wrong number of solutions: expected %zu, found %zu",
                  jans.size(), pans.size());
        }
        // Same size but different content
        for (size_t i = 0; i < jans.size(); i++) {
            if (jans[i] != pans[i]) {
                ll je_n, je_x, je_y;
                ll pa_n, pa_x, pa_y;
                tie(je_n, je_x, je_y) = jans[i];
                tie(pa_n, pa_x, pa_y) = pans[i];
                quitf(_wa,
                      "solution #%zu differs: expected (%lld %lld %lld), found (%lld %lld %lld)",
                      i+1, je_n, je_x, je_y, pa_n, pa_x, pa_y);
            }
        }
        // Fallback
        quitf(_wa, "solutions differ");
    }
    quitf(_ok, "OK");
    return 0;
}
