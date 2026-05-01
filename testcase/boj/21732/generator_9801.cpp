#include "testlib.h"
using namespace std;

struct Token {
    int var;
    int lit;
    bool isTrue;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose n with some variety, but small.
    int bucket = rnd.next(0, 4);
    int n;
    if (bucket == 0) n = 1;
    else if (bucket == 1) n = rnd.next(2, 3);
    else if (bucket == 2) n = rnd.next(3, 5);
    else if (bucket == 3) n = rnd.next(5, 8);
    else n = rnd.next(8, 12);

    vector<vector<int>> clauses;

    int scenario = rnd.next(0, 2); // 0: simple, 1: guaranteed SAT, 2: guaranteed UNSAT

    if (scenario == 0) {
        // Very simple edge cases
        if (n == 1) {
            int sub = rnd.next(0, 1);
            if (sub == 0) {
                // Single unit clause
                int sign = rnd.next(0, 1) ? 1 : -1;
                clauses.push_back(vector<int>{sign * 1});
            } else {
                // Tautology x1 v ¬x1
                clauses.push_back(vector<int>{1, -1});
            }
        } else {
            // Each variable appears once as a unit clause
            for (int i = 1; i <= n; i++) {
                int sign = rnd.next(0, 1) ? 1 : -1;
                clauses.push_back(vector<int>{sign * i});
            }
        }
    } else if (scenario == 1) {
        // Guaranteed satisfiable CNF via random assignment and limited occurrences
        vector<int> assign(n + 1);
        for (int i = 1; i <= n; i++)
            assign[i] = rnd.next(0, 1);

        vector<int> occCount(n + 1, 0);
        int totOcc = 0;
        for (int i = 1; i <= n; i++) {
            int r = rnd.next(0, 2); // 0,1,2 occurrences
            occCount[i] = r;
            totOcc += r;
        }
        if (totOcc == 0) {
            int v = rnd.next(1, n);
            occCount[v] = 1;
            totOcc = 1;
        }

        vector<Token> tokens;
        tokens.reserve(totOcc);

        int cntTrue = 0;
        for (int i = 1; i <= n; i++) {
            for (int t = 0; t < occCount[i]; t++) {
                bool useTrue = (rnd.next(0, 2) != 0); // 2/3 chance to be true literal
                int lit;
                bool isTrue;
                if (useTrue) {
                    if (assign[i] == 1) lit = i;
                    else lit = -i;
                    isTrue = true;
                } else {
                    if (assign[i] == 1) lit = -i;
                    else lit = i;
                    isTrue = false;
                }
                tokens.push_back({i, lit, isTrue});
                if (isTrue) cntTrue++;
            }
        }

        if (cntTrue == 0) {
            // Flip one token to become true under the assignment
            int idx = rnd.next(0, (int)tokens.size() - 1);
            tokens[idx].lit = -tokens[idx].lit;
            tokens[idx].isTrue = true;
            cntTrue = 1;
        }

        // Number of clauses between 1 and cntTrue
        int m = rnd.next(1, cntTrue);
        clauses.assign(m, vector<int>());

        // Ensure at least one true literal per clause
        vector<int> trueIdxs;
        for (int i = 0; i < (int)tokens.size(); i++)
            if (tokens[i].isTrue)
                trueIdxs.push_back(i);

        shuffle(trueIdxs.begin(), trueIdxs.end());
        vector<int> assignedClause(tokens.size(), -1);

        for (int i = 0; i < m; i++) {
            int ti = trueIdxs[i];
            assignedClause[ti] = i;
        }

        for (int i = 0; i < (int)tokens.size(); i++) {
            if (assignedClause[i] == -1) {
                assignedClause[i] = rnd.next(0, m - 1);
            }
        }

        for (int i = 0; i < (int)tokens.size(); i++) {
            int cid = assignedClause[i];
            clauses[cid].push_back(tokens[i].lit);
        }

        // Shuffle literals within each clause for variety
        for (auto &cl : clauses)
            shuffle(cl.begin(), cl.end());

        // Optionally shuffle order of clauses
        shuffle(clauses.begin(), clauses.end());

    } else {
        // Guaranteed UNSAT patterns, still respecting <=2 occurrences per variable
        if (n == 1) {
            // x1 and ¬x1
            int sign = rnd.next(0, 1) ? 1 : -1;
            clauses.push_back(vector<int>{sign * 1});
            clauses.push_back(vector<int>{-sign * 1});
        } else {
            bool useSingleVar = (rnd.next(0, 1) == 0);
            if (useSingleVar) {
                // Single variable contradiction: (xv) & (¬xv)
                int v = rnd.next(1, n);
                int sign = rnd.next(0, 1) ? 1 : -1;
                clauses.push_back(vector<int>{sign * v});
                clauses.push_back(vector<int>{-sign * v});
            } else {
                // Two-variable unsat pattern:
                // (La ∨ Lb) ∧ (¬La) ∧ (¬Lb)
                int a = rnd.next(1, n);
                int b = a;
                while (b == a) b = rnd.next(1, n);

                int signA = rnd.next(0, 1) ? 1 : -1;
                int signB = rnd.next(0, 1) ? 1 : -1;
                int La = signA * a;
                int Lb = signB * b;

                vector<int> c1{La, Lb};
                vector<int> c2{-La};
                vector<int> c3{-Lb};
                clauses.push_back(c1);
                clauses.push_back(c2);
                clauses.push_back(c3);

                // Shuffle clause order
                shuffle(clauses.begin(), clauses.end());
            }
        }
    }

    int m = (int)clauses.size();
    println(n, m);
    for (const auto &cl : clauses) {
        vector<int> line;
        line.reserve(cl.size() + 1);
        line.push_back((int)cl.size());
        for (int x : cl) line.push_back(x);
        println(line);
    }

    return 0;
}
