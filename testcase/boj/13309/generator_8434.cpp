#include "testlib.h"
#include <vector>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of nodes: between 2 and 12 for hand-checkable sizes
    int N = rnd.next(2, 12);
    // Tree shape bias: negative => star-like, zero => uniform, positive => chain-like
    vector<int> biases = {-3, 0, 3};
    int bias = rnd.any(biases);

    // Generate a random rooted tree with root = 1
    vector<int> par(N+1);
    par[1] = 0;
    for (int i = 2; i <= N; i++) {
        // rnd.wnext(i-1, bias) gives [0..i-2] with bias
        par[i] = rnd.wnext(i-1, bias) + 1;
    }

    // Number of queries: between 1 and 20
    int Q = rnd.next(1, 20);
    vector<tuple<int,int,int>> qs;
    qs.reserve(Q);
    bool has0 = false, has1 = false;

    for (int i = 0; i < Q; i++) {
        int b = rnd.next(1, N);
        int c;
        // ensure b != c
        do {
            c = rnd.next(1, N);
        } while (c == b);
        int d = rnd.next(0, 1);
        if (d == 0) has0 = true;
        else has1 = true;
        qs.emplace_back(b, c, d);
    }
    // If we have at least 2 queries, ensure both d=0 and d=1 appear
    if (Q >= 2) {
        if (!has0) {
            auto &t = qs[0];
            get<2>(t) = 0;
        }
        if (!has1) {
            auto &t = qs[1];
            get<2>(t) = 1;
        }
    }

    // Output the test case
    println(N, Q);
    for (int i = 2; i <= N; i++) {
        println(par[i]);
    }
    for (auto &t : qs) {
        println(get<0>(t), get<1>(t), get<2>(t));
    }

    return 0;
}
