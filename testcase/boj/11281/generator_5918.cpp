#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of variables and clauses
    int N = rnd.next(1, 10);
    int M = rnd.next(1, min(2 * N, 100));

    // Helper to generate a random literal in [-N..-1] U [1..N]
    auto randLit = [&]() {
        int v = rnd.next(1, N);
        return rnd.next(0, 1) ? v : -v;
    };

    // Decide roughly 25% of the time to produce an unsatisfiable core (if possible)
    bool wantUnsat = rnd.next(0, 3) == 0;
    vector<pair<int,int>> clauses;
    vector<int> assignment(N + 1);

    if (!wantUnsat || M < 2) {
        // Generate a guaranteed satisfiable instance
        for (int i = 1; i <= N; i++) {
            assignment[i] = rnd.next(0, 1);  // 0=false, 1=true
        }
        for (int k = 0; k < M; k++) {
            // pick two positions (may coincide occasionally)
            int i = rnd.next(1, N);
            int j = rnd.next(1, N);
            if (rnd.next(0, 9) == 0) {
                j = i;  // same-variable clause sometimes
            }
            // force one of the literals to satisfy under the assignment
            if (rnd.next(0, 1)) {
                int li = (assignment[i] ? i : -i);
                int lj = randLit();
                clauses.emplace_back(li, lj);
            } else {
                int lj = (assignment[j] ? j : -j);
                int li = randLit();
                clauses.emplace_back(li, lj);
            }
        }
    } else {
        // Build a small unsatisfiable core: (u ∨ u) and (¬u ∨ ¬u)
        int u = rnd.next(1, N);
        clauses.emplace_back(u, u);
        clauses.emplace_back(-u, -u);
        // fill the rest randomly
        for (int k = 2; k < M; k++) {
            int i = randLit();
            int j = randLit();
            if (rnd.next(0, 9) == 0) {
                j = i;  // allow same-variable clauses
            }
            clauses.emplace_back(i, j);
        }
    }

    // Shuffle clauses for unpredictability
    shuffle(clauses.begin(), clauses.end());

    // Output
    println(N, M);
    for (auto &c : clauses) {
        println(c.first, c.second);
    }
    return 0;
}
