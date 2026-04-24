#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sequence length
    int N = rnd.next(2, 10);

    // Small number of queries
    int maxM = min(20, N * (N + 1) / 2);
    int M0 = rnd.next(1, maxM);
    int Mleft = M0;

    // Decide to include a full-range query
    bool hasFull = false, hasSingle = false;
    if (rnd.next(0, 1) == 1 && Mleft >= 1) {
        hasFull = true;
        Mleft--;
    }
    // Decide to include a single-point query
    if (rnd.next(0, 1) == 1 && Mleft >= 1) {
        hasSingle = true;
        Mleft--;
    }

    // Prepare queries
    int tVal = rnd.next(-2, 2);
    vector<pair<int,int>> queries;
    if (hasFull) {
        queries.emplace_back(1, N);
    }
    if (hasSingle) {
        int idx = rnd.next(1, N);
        queries.emplace_back(idx, idx);
    }
    for (int k = 0; k < Mleft; k++) {
        // Length biased by weighted next
        int len = rnd.wnext(N, tVal) + 1;  // 1..N
        int i = rnd.next(1, N - len + 1);
        int j = i + len - 1;
        queries.emplace_back(i, j);
    }
    shuffle(queries.begin(), queries.end());

    // Build array A with some repeats and some distinct values
    int distinctCount = rnd.next(1, N);
    set<int> s;
    while ((int)s.size() < distinctCount) {
        s.insert(rnd.next(1, 100));
    }
    vector<int> vals(s.begin(), s.end());
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.any(vals);
    }

    // Output
    println(N);
    println(A);
    println(M0);
    for (auto &q : queries) {
        println(q.first, q.second);
    }

    return 0;
}
