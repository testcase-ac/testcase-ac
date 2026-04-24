#include "testlib.h"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of names
    int N = rnd.next(3, 10);
    // Alphabet size
    int K = rnd.next(2, 5);
    // Compute minimal max length so we can generate at least N distinct names
    long long tot = 0, pw = 1;
    int L_req = 0;
    while (tot < N) {
        ++L_req;
        pw *= K;
        tot += pw;
    }
    if (L_req > 7) L_req = 7;
    // Allow some randomness in max length, but at least L_req
    int L_max = rnd.next(L_req, 7);

    // Number of clusters of common-prefix names
    int maxClusters = min(N/2, 3);
    int C = rnd.next(0, maxClusters);

    vector<string> names;
    set<string> used;

    // Generate clusters with common prefixes
    for (int ci = 0; ci < C; ++ci) {
        int rem = N - int(names.size());
        if (rem < 2 || L_max < 2) break;

        // prefix length at least 1, at most L_max-1
        int prefLen = rnd.next(1, L_max - 1);
        // cluster at least size 2, at most remaining
        int clusterSize = rnd.next(2, rem);

        // build a random prefix
        string prefix;
        for (int i = 0; i < prefLen; i++) {
            prefix.push_back(char('A' + rnd.next(0, K - 1)));
        }

        int added = 0, tries = 0;
        while (added < clusterSize && tries < 1000) {
            ++tries;
            int sufLen = rnd.next(0, L_max - prefLen);
            string w = prefix;
            for (int j = 0; j < sufLen; j++) {
                w.push_back(char('A' + rnd.next(0, K - 1)));
            }
            if (!used.count(w)) {
                used.insert(w);
                names.push_back(w);
                added++;
            }
        }
    }

    // Fill remaining names with random unique strings
    int fillTries = 0;
    while (int(names.size()) < N) {
        if (++fillTries > 10000) {
            // fallback: generate sequential distinct strings if random fails
            for (int i = 0; int(names.size()) < N; ++i) {
                string w = "X" + to_string(i);
                if (!used.count(w)) {
                    used.insert(w);
                    names.push_back(w);
                }
            }
            break;
        }
        int len = rnd.next(1, L_max);
        string w;
        for (int j = 0; j < len; j++) {
            w.push_back(char('A' + rnd.next(0, K - 1)));
        }
        if (!used.count(w)) {
            used.insert(w);
            names.push_back(w);
        }
    }

    // Shuffle the final list
    shuffle(names.begin(), names.end());

    // Output
    println(N);
    for (auto &s : names) println(s);

    return 0;
}
