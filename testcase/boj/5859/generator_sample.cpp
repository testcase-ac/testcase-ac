#include "testlib.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Statement {
    int x;
    int y;
    string kind;
};

string relationFor(const vector<int>& truth, int x, int y) {
    return truth[x] == truth[y] ? "T" : "L";
}

void addConsistent(vector<Statement>& statements, const vector<int>& truth, int x, int y) {
    statements.push_back({x, y, relationFor(truth, x, y)});
}

void addFlipped(vector<Statement>& statements, const vector<int>& truth, int x, int y) {
    statements.push_back({x, y, relationFor(truth, x, y) == "T" ? "L" : "T"});
}

pair<int, int> randomOrderedPair(int n) {
    int x = rnd.next(1, n);
    int y = rnd.next(1, n - 1);
    if (y >= x) ++y;
    return {x, y};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 12);
    if (mode == 4) n = rnd.next(20, 60);

    vector<int> truth(n + 1);
    for (int i = 1; i <= n; ++i) {
        truth[i] = rnd.next(0, 1);
    }

    vector<Statement> statements;

    if (mode == 0) {
        int m = rnd.next(1, 2 * n);
        for (int i = 0; i < m; ++i) {
            auto [x, y] = randomOrderedPair(n);
            addConsistent(statements, truth, x, y);
        }
    } else if (mode == 1) {
        auto [x, y] = randomOrderedPair(n);
        addConsistent(statements, truth, x, y);
        statements.push_back({x, y, statements.back().kind == "T" ? "L" : "T"});

        int extra = rnd.next(0, n);
        for (int i = 0; i < extra; ++i) {
            auto [a, b] = randomOrderedPair(n);
            addConsistent(statements, truth, a, b);
        }
    } else if (mode == 2) {
        int prefix = rnd.next(1, 2 * n);
        for (int i = 0; i < prefix; ++i) {
            auto [x, y] = randomOrderedPair(n);
            addConsistent(statements, truth, x, y);
        }

        auto [x, y] = randomOrderedPair(n);
        addFlipped(statements, truth, x, y);

        int suffix = rnd.next(0, n);
        for (int i = 0; i < suffix; ++i) {
            auto [a, b] = randomOrderedPair(n);
            statements.push_back({a, b, rnd.next(0, 1) ? "T" : "L"});
        }
    } else if (mode == 3) {
        for (int i = 1; i <= n; ++i) {
            int y = i == n ? 1 : i + 1;
            addConsistent(statements, truth, i, y);
        }

        int duplicates = rnd.next(1, n);
        for (int i = 0; i < duplicates; ++i) {
            int x = rnd.next(1, n);
            int y = x == n ? 1 : x + 1;
            addConsistent(statements, truth, x, y);
        }

        int x = rnd.next(1, n);
        int y = x == n ? 1 : x + 1;
        addFlipped(statements, truth, x, y);
    } else {
        int m = rnd.next(25, 80);
        for (int i = 0; i < m; ++i) {
            auto [x, y] = randomOrderedPair(n);
            if (rnd.next(0, 4) == 0) {
                statements.push_back({x, y, rnd.next(0, 1) ? "T" : "L"});
            } else {
                addConsistent(statements, truth, x, y);
            }
        }
    }

    println(n, static_cast<int>(statements.size()));
    for (const Statement& statement : statements) {
        println(statement.x, statement.y, statement.kind);
    }

    return 0;
}
