#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Op {
    char type;
    int a, b;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of operations
    int N = rnd.next(10, 50);
    // Upper bound for part IDs, biased towards smaller numbers
    int id_space = rnd.wnext(1000000, -3) + 1;
    // Number of distinct parts we'll reference
    int distinct_count = rnd.next(3, min(N, 20));
    unordered_set<int> st;
    while ((int)st.size() < distinct_count) {
        st.insert(rnd.next(1, id_space));
    }
    vector<int> pool(st.begin(), st.end());
    // Ensure at least one query, up to about half queries
    int count_Q = rnd.wnext(N / 2 + 1, -1) + 1;
    if (count_Q >= N) count_Q = rnd.next(1, N - 1);
    int count_I = N - count_Q;

    // Generate operations
    vector<Op> ops;
    // I operations: unify two distinct parts
    for (int i = 0; i < count_I; i++) {
        int a = rnd.any(pool);
        int b = rnd.any(pool);
        while (b == a) b = rnd.any(pool);
        ops.push_back({'I', a, b});
    }
    // Q operations: query a part
    for (int i = 0; i < count_Q; i++) {
        int c = rnd.any(pool);
        ops.push_back({'Q', c, 0});
    }
    // Shuffle to mix I and Q
    shuffle(ops.begin(), ops.end());

    // Output
    println(N);
    for (auto &op : ops) {
        if (op.type == 'I') {
            println("I", op.a, op.b);
        } else {
            println("Q", op.a);
        }
    }
    return 0;
}
