#include "testlib.h"
#include <vector>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: size of set S
    int N = rnd.next(1, 10);
    // Hyper-parameter: alphabet size for S
    int K = rnd.next(2, 4);
    vector<char> alph;
    for (int i = 0; i < K; i++) alph.push_back(char('a' + i));

    // Generate unique strings for S
    set<string> S_set;
    while ((int)S_set.size() < N) {
        int len = rnd.next(1, 6);
        string s;
        for (int i = 0; i < len; i++)
            s.push_back(rnd.any(alph));
        S_set.insert(s);
    }
    vector<string> S(S_set.begin(), S_set.end());
    shuffle(S.begin(), S.end());

    // Number of queries
    int Q = rnd.next(1, 10);
    // Hyper-parameter: number of positive cases
    int num_hits;
    if (Q == 1) num_hits = rnd.next(0, 1);
    else num_hits = rnd.next(1, Q - 1);

    vector<string> queries;
    // Generate hit cases
    for (int i = 0; i < num_hits; i++) {
        string pat = rnd.any(S);
        int plen = pat.size();
        int L = rnd.next(plen, 15);
        int pre = rnd.next(0, L - plen);
        int post = L - plen - pre;
        string t;
        for (int j = 0; j < pre; j++) t.push_back(rnd.any(alph));
        t += pat;
        for (int j = 0; j < post; j++) t.push_back(rnd.any(alph));
        queries.push_back(t);
    }
    // Generate miss cases (use 'z' which is not in alph)
    for (int i = 0; i < Q - num_hits; i++) {
        int L = rnd.next(1, 15);
        string t(L, 'z');
        queries.push_back(t);
    }
    shuffle(queries.begin(), queries.end());

    // Output
    println(N);
    for (auto &s : S) println(s);
    println(Q);
    for (auto &t : queries) println(t);

    return 0;
}
