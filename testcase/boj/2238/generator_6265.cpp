#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper‐parameter for N: small, medium, or larger
    int N;
    double r = rnd.next();
    if (r < 0.3) {
        N = rnd.next(1, 5);
    } else if (r < 0.8) {
        N = rnd.next(6, 20);
    } else {
        N = rnd.next(21, 50);
    }

    // Hyper‐parameter for U (upper bound on prices)
    int U;
    double ru = rnd.next();
    if (ru < 0.3) {
        U = rnd.next(1, 5);
    } else if (ru < 0.8) {
        U = rnd.next(6, 100);
    } else {
        U = rnd.next(100, 1000);
    }

    // Choose how many distinct people (names) participate
    int maxNames = min(N, 10);
    int nameCount = rnd.next(1, maxNames);
    set<string> nameSet;
    vector<string> names;
    // Generate unique random names (1 to 10 chars, A-Z or a-z)
    while ((int)nameSet.size() < nameCount) {
        int len = rnd.next(1, 10);
        string s;
        for (int i = 0; i < len; i++) {
            if (rnd.next() < 0.5)
                s += char('A' + rnd.next(0, 25));
            else
                s += char('a' + rnd.next(0, 25));
        }
        if (nameSet.insert(s).second) {
            names.push_back(s);
        }
    }

    // Output U and N
    println(U, N);

    // Generate N bids
    for (int i = 0; i < N; i++) {
        string s = rnd.any(names);
        int p = rnd.next(1, U);
        println(s, p);
    }

    return 0;
}
