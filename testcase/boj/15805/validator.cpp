#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 200000;

    int n = inf.readInt(1, MAX_N, "N");
    inf.readEoln();

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readInt(0, MAX_N, "A_i");
        if (i + 1 < n) {
            inf.readSpace();
        }
    }
    inf.readEoln();
    inf.readEof();

    ensuref(a[0] == 0, "tour must start at root city 0");
    ensuref(a[n - 1] == 0, "tour must end at root city 0");
    ensuref(n % 2 == 1, "minimal tree tour length must be odd, got %d", n);

    int max_city = *max_element(a.begin(), a.end());
    int k = max_city + 1;
    ensuref(n == 2 * k - 1,
            "minimal tour over %d cities must have length %d, got %d",
            k, 2 * k - 1, n);

    vector<int> seen(k, 0);
    for (int i = 0; i < n; ++i) {
        ensuref(a[i] < k, "A[%d] = %d is outside [0, %d]", i + 1, a[i], k - 1);
        seen[a[i]] = 1;
    }
    for (int v = 0; v < k; ++v) {
        ensuref(seen[v], "city %d does not appear in the tour", v);
    }

    vector<int> parent(k, -2);
    vector<int> stack;
    parent[0] = -1;
    stack.push_back(0);

    for (int i = 1; i < n; ++i) {
        int current = stack.back();
        int next = a[i];

        if (parent[next] == -2) {
            parent[next] = current;
            stack.push_back(next);
            continue;
        }

        ensuref(next != current, "step %d stays at city %d", i + 1, current);
        ensuref(parent[current] == next,
                "step %d moves from %d to %d instead of backtracking to parent %d",
                i + 1, current, next, parent[current]);
        stack.pop_back();
    }

    ensuref(stack.size() == 1 && stack.back() == 0,
            "tour must finish after backtracking to root");
}
