#include "testlib.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

string literalToken(int literal) {
    return string(literal > 0 ? "+" : "-") + to_string(abs(literal));
}

int signedLiteral(int variable, bool positive) {
    return positive ? variable : -variable;
}

pair<int, int> randomClause(int n) {
    int a = rnd.next(1, n);
    int b = rnd.next(1, n);
    bool sa = rnd.next(0, 1);
    bool sb = rnd.next(0, 1);
    return {signedLiteral(a, sa), signedLiteral(b, sb)};
}

pair<int, int> satisfiedClause(const vector<bool>& assignment) {
    int n = (int)assignment.size() - 1;
    int a = rnd.next(1, n);
    int b = rnd.next(1, n);
    bool sa = rnd.next(0, 1);
    bool sb = rnd.next(0, 1);

    if (assignment[a] != sa && assignment[b] != sb) {
        if (rnd.next(0, 1)) {
            sa = assignment[a];
        } else {
            sb = assignment[b];
        }
    }
    return {signedLiteral(a, sa), signedLiteral(b, sb)};
}

void printCase(int n, const vector<pair<int, int>>& clauses) {
    println(n, (int)clauses.size());
    for (auto clause : clauses) {
        println(literalToken(clause.first), literalToken(clause.second));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(1, 5);
    for (int tc = 0; tc < cases; ++tc) {
        int mode = rnd.next(0, 5);
        int n = rnd.next(1, 12);
        if (mode == 5) {
            n = rnd.any(vector<int>{50, 100, 999, 1000});
        }

        vector<pair<int, int>> clauses;
        if (mode == 0) {
            vector<bool> assignment(n + 1);
            for (int i = 1; i <= n; ++i) {
                assignment[i] = rnd.next(0, 1);
            }
            int m = rnd.next(1, min(35, max(1, 3 * n)));
            for (int i = 0; i < m; ++i) {
                clauses.push_back(satisfiedClause(assignment));
            }
        } else if (mode == 1) {
            int x = rnd.next(1, n);
            clauses.push_back({x, x});
            clauses.push_back({-x, -x});
            int extra = rnd.next(0, min(20, 2 * n));
            for (int i = 0; i < extra; ++i) {
                clauses.push_back(randomClause(n));
            }
        } else if (mode == 2) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            int repeats = rnd.next(2, 8);
            pair<int, int> base = {signedLiteral(a, rnd.next(0, 1)), signedLiteral(b, rnd.next(0, 1))};
            for (int i = 0; i < repeats; ++i) {
                clauses.push_back(rnd.next(0, 1) ? base : make_pair(base.second, base.first));
            }
            int extra = rnd.next(0, 15);
            for (int i = 0; i < extra; ++i) {
                clauses.push_back(randomClause(n));
            }
        } else if (mode == 3) {
            for (int i = 1; i <= min(n, 8); ++i) {
                bool sign = rnd.next(0, 1);
                clauses.push_back({signedLiteral(i, sign), signedLiteral(i, sign)});
            }
            int extra = rnd.next(1, 15);
            for (int i = 0; i < extra; ++i) {
                clauses.push_back(randomClause(n));
            }
        } else if (mode == 4) {
            int chain = rnd.next(1, min(n, 10));
            for (int i = 1; i <= chain; ++i) {
                int next = i == chain ? 1 : i + 1;
                clauses.push_back({-i, next});
            }
            if (chain > 1 && rnd.next(0, 1)) {
                clauses.push_back({-chain, -1});
                clauses.push_back({1, 1});
            }
        } else {
            int m = rnd.next(1, 25);
            for (int i = 0; i < m; ++i) {
                int a = rnd.next(max(1, n - 5), n);
                int b = rnd.next(max(1, n - 5), n);
                clauses.push_back({signedLiteral(a, rnd.next(0, 1)), signedLiteral(b, rnd.next(0, 1))});
            }
        }

        shuffle(clauses.begin(), clauses.end());
        printCase(n, clauses);
    }

    return 0;
}
