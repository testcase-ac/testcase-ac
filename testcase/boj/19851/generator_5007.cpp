#include "testlib.h"
#include <vector>
#include <tuple>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: length of the bakery line
    int N = rnd.next(2, 10);
    // Hyper-parameter: bias to open vs close bread
    double pOpen = rnd.next();
    string s;
    s.reserve(N);
    for (int i = 0; i < N; i++) {
        s += (rnd.next() < pOpen ? '(' : ')');
    }

    // Number of events
    int Q = rnd.next(1, 20);
    // Hyper-parameter: fraction of flips vs orders
    double pFlip = rnd.next();
    vector<tuple<int,int,int>> qs;
    qs.reserve(Q);
    int cntType2 = 0;
    for (int i = 0; i < Q; i++) {
        int t = (rnd.next() < pFlip ? 1 : 2);
        if (t == 2) cntType2++;
        int a = rnd.next(1, N);
        int b = rnd.next(a, N);
        qs.emplace_back(t, a, b);
    }
    // Ensure at least one order (type 2)
    if (cntType2 == 0) {
        int idx = rnd.next(0, Q - 1);
        get<0>(qs[idx]) = 2;
    }

    // Output
    println(N);
    printf("%s\n", s.c_str());
    println(Q);
    for (auto &qt : qs) {
        int t, a, b;
        tie(t, a, b) = qt;
        println(t, a, b);
    }
    return 0;
}
