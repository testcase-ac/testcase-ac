#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of boolean variables
    int N = rnd.next(1, 10);
    // Maximum number of clauses, capped for readability
    int M_max = min(N * N, 20);
    int M = rnd.next(1, M_max);

    // Hyper-parameters for clause diversity
    double p_tauto = rnd.next(); // chance to insert a tautology (x ∨ ¬x)
    double p_same  = rnd.next(); // chance both literals refer to the same variable
    double p_neg   = rnd.next(); // chance each literal is negated

    vector<pair<int,int>> clauses;
    clauses.reserve(M);
    for (int k = 0; k < M; ++k) {
        int i, j;
        if (rnd.next() < p_tauto) {
            // Tautology clause (always true)
            int v = rnd.next(1, N);
            i = v; 
            j = -v;
        } else {
            // Pick first variable
            int a = rnd.next(1, N);
            // Decide second variable, avoid infinite loop when N=1
            int b;
            if (N == 1 || rnd.next() < p_same) {
                b = a;
            } else {
                do {
                    b = rnd.next(1, N);
                } while (b == a);
            }
            // Maybe negate each literal
            i = (rnd.next() < p_neg ? -a : a);
            j = (rnd.next() < p_neg ? -b : b);
        }
        clauses.emplace_back(i, j);
    }

    // Shuffle for unpredictability
    shuffle(clauses.begin(), clauses.end());

    // Output in required format
    println(N, M);
    for (auto &c : clauses) {
        println(c.first, c.second);
    }
    return 0;
}
