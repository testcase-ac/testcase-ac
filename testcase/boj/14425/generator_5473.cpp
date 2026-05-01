#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for hand-checkable cases
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);

    // Alphabet hyper-parameter: choose between 3 and 6 letters
    int alphSize = rnd.next(3, 6);
    vector<char> alph;
    for (int i = 0; i < alphSize; i++)
        alph.push_back(char('a' + i));
    shuffle(alph.begin(), alph.end());

    // Mode for string-length distribution: 0=short, 1=medium, 2=varied
    int mode = rnd.next(0, 2);

    // Generate a random string; if avoid==true, try to avoid the set
    set<string> S_set;
    auto genStr = [&](bool avoid)->string {
        int len;
        if (mode == 0) {
            len = rnd.next(1, 3);
        } else if (mode == 1) {
            len = rnd.next(4, 7);
        } else {
            len = rnd.next(1, 8);
        }
        string s;
        const int MAX_TRIES = 100;
        int tries = 0;
        do {
            s.clear();
            for (int i = 0; i < len; i++)
                s.push_back(rnd.any(alph));
            tries++;
        } while (avoid && tries < MAX_TRIES && S_set.count(s));
        return s;
    };

    // Build the set S of unique strings
    vector<string> S;
    while ((int)S.size() < N) {
        string s = genStr(true);
        if (!S_set.count(s)) {
            S_set.insert(s);
            S.push_back(s);
        }
    }

    // Probability that a query matches an element of S
    double matchProb = rnd.next();  // in [0,1)

    // Build M queries
    vector<string> Q;
    for (int i = 0; i < M; i++) {
        if (!S.empty() && rnd.next() < matchProb) {
            // Pick an existing string for a match
            Q.push_back(rnd.any(S));
        } else {
            // Generate a non-matching string
            Q.push_back(genStr(true));
        }
    }

    // Output in required format
    println(N, M);
    for (auto &s : S) println(s);
    for (auto &q : Q) println(q);

    return 0;
}
