#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: size of the permutation
    int N = rnd.next(1, 10);

    // Hyper-parameter: cycle structure
    vector<int> clens;
    if (rnd.next(0, 1) == 0) {
        // one big cycle
        clens.push_back(N);
    } else {
        // random partition into cycles
        int rem = N;
        while (rem > 0) {
            int l = rnd.next(1, rem);
            clens.push_back(l);
            rem -= l;
        }
    }

    // shuffle nodes and build permutation according to cycle lengths
    vector<int> nodes(N);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());

    vector<int> A(N+1);
    int idx = 0;
    for (int len : clens) {
        // extract a cycle of length len
        vector<int> cyc;
        for (int j = 0; j < len; j++) {
            cyc.push_back(nodes[idx++]);
        }
        // link the cycle
        for (int j = 0; j + 1 < len; j++) {
            A[cyc[j]] = cyc[j+1];
        }
        A[cyc.back()] = cyc.front();
    }

    // Hyper-parameter: choose M small or large
    string M_str;
    if (rnd.next(0, 1) == 0) {
        // small M in [1,20]
        int m = rnd.next(1, 20);
        M_str = to_string(m);
    } else {
        // large M as a big integer string of length [1,20]
        int L = rnd.next(1, 20);
        M_str.resize(L);
        M_str[0] = char('1' + rnd.next(0, 8)); // non-zero first digit
        for (int i = 1; i < L; i++) {
            M_str[i] = char('0' + rnd.next(0, 9));
        }
    }

    // Output
    println(N, M_str);
    // print A_1 ... A_N
    for (int i = 1; i <= N; i++) {
        printf("%d%c", A[i], i==N?'\n':' ');
    }

    return 0;
}
