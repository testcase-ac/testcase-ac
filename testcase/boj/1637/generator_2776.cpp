#include "testlib.h"
#include <vector>
#include <tuple>
#include <set>
#include <algorithm>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide whether to produce a case with no odd-count integer
    bool produceNothing = rnd.next(0, 9) == 0;
    // Number of pair-sequences to insert (each pair yields even counts)
    int maxPairs = rnd.next(1, 3);
    int minPairs = produceNothing ? 1 : 0;
    int M = rnd.next(minPairs, maxPairs);

    // Define the universe of numbers [1..Umax]
    ll Umax = rnd.next((ll)20, (ll)100);

    vector<tuple<ll,ll,ll>> seqs;
    set<ll> used;

    // Generate M disjoint pairs of sequences
    for (int i = 0; i < M; i++) {
        ll A, B, C;
        int len;
        while (true) {
            len = rnd.next(1, 3);        // length between 1 and 3
            B   = rnd.next(1, 5);        // step between 1 and 5
            ll maxA = Umax - (len - 1) * B;
            if (maxA < 1) continue;
            ll lower = 1;
            A = rnd.next(lower, maxA);
            C = A + (len - 1) * B;
            bool ok = true;
            for (int k = 0; k < len; k++) {
                ll x = A + k * B;
                if (used.count(x)) { ok = false; break; }
            }
            if (ok) break;
        }
        // Mark numbers as used
        for (int k = 0; k < len; k++) {
            used.insert(A + k * B);
        }
        // Add the sequence twice
        seqs.emplace_back(A, C, B);
        seqs.emplace_back(A, C, B);
    }

    // If we need an odd-count integer, add one special single-value sequence
    if (!produceNothing) {
        ll t;
        while (true) {
            t = rnd.next((ll)1, Umax);
            if (!used.count(t)) break;
        }
        ll specialB = rnd.next((ll)1, (ll)5);
        seqs.emplace_back(t, t, specialB);
    }

    // Shuffle and output
    shuffle(seqs.begin(), seqs.end());
    println((int)seqs.size());
    for (auto &tpl : seqs) {
        ll A, C, B;
        tie(A, C, B) = tpl;
        println(A, C, B);
    }
    return 0;
}
