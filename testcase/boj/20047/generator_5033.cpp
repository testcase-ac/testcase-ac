#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: small n
    int n = rnd.next(3, 10);

    // Generate random S with at least one 'o' and one 'x'
    int cnt_o = rnd.next(1, n-1);
    int cnt_x = n - cnt_o;
    vector<char> sv;
    for (int i = 0; i < cnt_o; i++) sv.push_back('o');
    for (int i = 0; i < cnt_x; i++) sv.push_back('x');
    shuffle(sv.begin(), sv.end());
    string S(sv.begin(), sv.end());

    // Choose positions i<j
    int i = rnd.next(0, n-2);
    int j = rnd.next(i+1, n-1);

    // Precompute all reachable T strings by one two-finger move on S at (i,j)
    // First remove S[i], S[j] to get S_rest
    string S_rest;
    for (int k = 0; k < n; k++) {
        if (k == i || k == j) continue;
        S_rest.push_back(S[k]);
    }
    set<string> reachable;
    // Insert the two selected coins (in original order) into S_rest at positions p1<p2
    char a = S[i], b = S[j];
    for (int p1 = 0; p1 < n-1; p1++) {
        for (int p2 = p1+1; p2 < n; p2++) {
            string t(n, '?');
            // place a at p1, b at p2
            t[p1] = a;
            t[p2] = b;
            // fill the rest from S_rest
            int idx = 0;
            for (int k = 0; k < n; k++) {
                if (k == p1 || k == p2) continue;
                t[k] = S_rest[idx++];
            }
            reachable.insert(t);
        }
    }

    // Compute number of unique permutations of S (factorial-based)
    long long fact[11];
    fact[0] = 1;
    for (int k = 1; k <= n; k++) fact[k] = fact[k-1] * k;
    long long totalPerm = fact[n] / (fact[cnt_o] * fact[cnt_x]);

    // Decide YES or NO
    bool want_yes = rnd.next(0,1) == 1;
    // If no unreachable exists, force YES
    if (!want_yes && (int)reachable.size() >= totalPerm) {
        want_yes = true;
    }

    string T;
    if (want_yes) {
        // Pick a random reachable T
        int idx = rnd.next(0, (int)reachable.size()-1);
        auto it = reachable.begin();
        while (idx--) ++it;
        T = *it;
    } else {
        // want NO: find a T preserving counts but not in reachable
        vector<char> tv = sv;
        for (int tries = 0; tries < 1000; tries++) {
            shuffle(tv.begin(), tv.end());
            string cand(tv.begin(), tv.end());
            if (!reachable.count(cand)) {
                T = cand;
                break;
            }
        }
        // Fallback: if not found (rare), pick a random reachable to at least output something
        if (T.empty()) {
            int idx = rnd.next(0, (int)reachable.size()-1);
            auto it = reachable.begin();
            while (idx--) ++it;
            T = *it;
        }
    }

    // Output
    println(n);
    printf("%s\n", S.c_str());
    printf("%s\n", T.c_str());
    println(i, j);

    return 0;
}
