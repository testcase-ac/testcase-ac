#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with varied distribution: small, medium, larger (but <=15)
    double rd = rnd.next();
    int N;
    if (rd < 0.3) {
        N = rnd.next(1, 3);
    } else if (rd < 0.7) {
        N = rnd.next(4, 7);
    } else {
        N = rnd.next(8, 15);
    }

    // Number of clauses M, at least 1
    int M = rnd.next(1, max(1, N * 3));

    // Decide whether to inject a guaranteed contradiction
    bool makeUnsat = (M >= 2 && rnd.next() < 0.3);
    int inject = makeUnsat ? 2 : 0;
    int rem = M - inject;

    vector<pair<int,int>> clauses;

    // Inject unsatisfiable pair: (u v u) and (~u v ~u)
    if (makeUnsat) {
        int u = rnd.next(1, N);
        clauses.emplace_back(u, u);
        clauses.emplace_back(-u, -u);
    }

    // Generate the remaining random clauses
    for (int i = 0; i < rem; i++) {
        int x = rnd.next(1, N);
        int y = rnd.next(1, N);
        int sx = rnd.next(0,1) ? x : -x;
        int sy = rnd.next(0,1) ? y : -y;
        clauses.emplace_back(sx, sy);
    }

    // Shuffle clause order for variability
    shuffle(clauses.begin(), clauses.end());

    // Output
    println(N, (int)clauses.size());
    for (auto &c : clauses) {
        println(c.first, c.second);
    }
    return 0;
}
