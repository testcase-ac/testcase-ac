#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // 2. Read N lines: each is a permutation of 1..N (men's preferences)
    vector< vector<int> > men_pref(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        men_pref[i] = inf.readInts(N, 1, N, "men_pref[i]");
        // Check permutation
        set<int> s(men_pref[i].begin(), men_pref[i].end());
        ensuref((int)s.size() == N, "Men's preference line %d is not a permutation", i+1);
        inf.readEoln();
    }

    // 3. Read N lines: each is a permutation of 1..N (women's preferences)
    vector< vector<int> > women_pref(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        women_pref[i] = inf.readInts(N, 1, N, "women_pref[i]");
        set<int> s(women_pref[i].begin(), women_pref[i].end());
        ensuref((int)s.size() == N, "Women's preference line %d is not a permutation", i+1);
        inf.readEoln();
    }

    inf.readEof();
}
