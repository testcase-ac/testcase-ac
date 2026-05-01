#include "testlib.h"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of stored sites (N) and queries (M), small enough for hand verification
    int N = rnd.next(1, 15);
    int maxM = min(N * 2, 20);
    int M = rnd.next(1, maxM);

    // Allowed characters in a site address
    const string domainChars = "abcdefghijklmnopqrstuvwxyz"
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "-.";
    set<string> used;
    vector<string> domains;

    // Generate N unique site addresses
    while ((int)domains.size() < N) {
        int len = rnd.next(1, 10);
        string s;
        for (int i = 0; i < len; i++) {
            int idx = rnd.next(0, (int)domainChars.size() - 1);
            s.push_back(domainChars[idx]);
        }
        if (used.insert(s).second) {
            domains.push_back(s);
        }
    }

    // Generate a random uppercase password for each site
    vector<string> pwds(N);
    for (int i = 0; i < N; i++) {
        int len = rnd.next(1, 12);
        string p;
        for (int j = 0; j < len; j++) {
            p.push_back(char('A' + rnd.next(0, 25)));
        }
        pwds[i] = p;
    }

    // Build the list of M queries, optionally allowing duplicates
    vector<string> queries;
    bool allowDup = (M > N) || rnd.next(0, 1);
    if (!allowDup && M <= N) {
        // unique queries
        vector<string> tmp = domains;
        shuffle(tmp.begin(), tmp.end());
        for (int i = 0; i < M; i++) {
            queries.push_back(tmp[i]);
        }
    } else {
        // with possible duplicates
        for (int i = 0; i < M; i++) {
            queries.push_back(rnd.any(domains));
        }
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(domains[i], pwds[i]);
    }
    for (auto &q : queries) {
        println(q);
    }

    return 0;
}
