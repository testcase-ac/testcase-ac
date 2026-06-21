#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static int litFromVar(int var, bool positive) {
    return positive ? var : -var;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 40);
    int vars = rnd.next(1, min(12, n + 1));
    bool useBoundary = rnd.next(0, 4) == 0;

    vector<vector<int>> actions;
    auto addClause = [&](int a, int b) {
        if ((int)actions.size() < n) actions.push_back({1, a, b});
    };
    auto addQuery = [&]() {
        if ((int)actions.size() < n) actions.push_back({2});
    };
    auto pickVar = [&]() {
        if (useBoundary && rnd.next(0, 9) == 0) return rnd.next(99990, 100000);
        return rnd.next(1, vars);
    };
    auto pickLit = [&]() {
        int var = pickVar();
        return litFromVar(var, rnd.next(0, 1) == 1);
    };

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) addQuery();
            else addClause(pickLit(), pickLit());
        }
    } else if (mode == 1) {
        int x = pickVar();
        addClause(x, x);
        if (rnd.next(0, 1)) addQuery();
        addClause(-x, -x);
    } else if (mode == 2) {
        int x = pickVar();
        int y = pickVar();
        if (x == y) y = (y % vars) + 1;
        addClause(x, y);
        addClause(-x, y);
        if (rnd.next(0, 1)) addQuery();
        addClause(x, -y);
        addClause(-x, -y);
    } else if (mode == 3) {
        int chain = rnd.next(2, min(8, max(2, vars)));
        for (int i = 1; i <= chain; ++i) {
            int a = i;
            int b = (i == chain ? 1 : i + 1);
            addClause(-a, b);
            if (rnd.next(0, 2) == 0) addQuery();
        }
        if (rnd.next(0, 1)) {
            int x = rnd.next(1, chain);
            addClause(x, x);
            addClause(-x, -x);
        }
    } else {
        int clauses = rnd.next(1, max(1, n - 1));
        for (int i = 0; i < clauses; ++i) {
            int base = pickVar();
            int a = litFromVar(base, rnd.next(0, 1));
            int b = rnd.next(0, 3) == 0 ? a : pickLit();
            addClause(a, b);
            if (rnd.next(0, 4) == 0) addQuery();
        }
    }

    while ((int)actions.size() < n) {
        if (actions.empty() || rnd.next(0, 3) == 0) addQuery();
        else addClause(pickLit(), pickLit());
    }

    bool hasQuery = false;
    for (const auto& action : actions) {
        if (action[0] == 2) hasQuery = true;
    }
    if (!hasQuery) actions[rnd.next(0, n - 1)] = {2};

    println(n);
    for (const auto& action : actions) {
        if (action[0] == 2) {
            println(2);
        } else {
            println(1, action[1], action[2]);
        }
    }

    return 0;
}
