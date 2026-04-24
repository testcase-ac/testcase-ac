#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: biased small/large around [1..20]
    int tN = rnd.next(-1, 1);
    int N = rnd.wnext(20, tN) + 1;

    // Maximum clauses based on N, capped at 100
    int Mmax = min(100, 4 * N + 5);
    int tM = rnd.next(-1, 1);
    int M = rnd.wnext(Mmax, tM) + 1;

    // Decide unsatisfiable instance with ~30% probability
    bool unsat = rnd.next(0, 9) < 3;
    if (unsat && M < 2) M = 2;

    vector<pair<int,int>> clauses;
    clauses.reserve(M);
    int numRand = unsat ? M - 2 : M;

    // Generate random clauses with different types
    for (int i = 0; i < numRand; i++) {
        int r = rnd.next(0, 99);
        if (r < 40) {
            // Fully random clause
            int a = rnd.next(1, N), b = rnd.next(1, N);
            int la = rnd.next(0, 1) ? a : -a;
            int lb = rnd.next(0, 1) ? b : -b;
            clauses.emplace_back(la, lb);
        } else if (r < 60) {
            // Tautology (x OR ¬x)
            int k = rnd.next(1, N);
            clauses.emplace_back(k, -k);
        } else if (r < 80) {
            // Unit positive duplication (x OR x)
            int k = rnd.next(1, N);
            clauses.emplace_back(k, k);
        } else {
            // Unit negative duplication (¬x OR ¬x)
            int k = rnd.next(1, N);
            clauses.emplace_back(-k, -k);
        }
    }

    // If unsatisfiable, add a direct contradiction on one variable
    if (unsat) {
        int v = rnd.next(1, N);
        clauses.emplace_back(v, v);
        clauses.emplace_back(-v, -v);
    }

    // Shuffle clause order
    shuffle(clauses.begin(), clauses.end());

    // Output
    println(N, M);
    for (auto &p : clauses)
        println(p.first, p.second);

    return 0;
}
