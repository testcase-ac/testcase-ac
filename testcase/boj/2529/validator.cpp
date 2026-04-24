#include "testlib.h"
#include <vector>
#include <string>
#include <functional>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read k: number of inequalities
    int k = inf.readInt(2, 9, "k");
    inf.readEoln();

    // Read the line of k inequalities separated by single spaces.
    // We only allow '<', '>' and space characters, then check exact format.
    // Note: to include space in testlib regex, we escape it as "\\ ".
    string line = inf.readLine("[<>\\ ]{1,100}", "inequalities");
    // The line must be exactly k symbols and k-1 spaces: total length = 2*k - 1
    ensuref((int)line.size() == 2*k - 1,
            "inequalities: expected line length %d, got %d",
            2*k - 1, (int)line.size());

    vector<char> ineq(k);
    for (int i = 0; i < k; i++) {
        // At even positions (0-based) there must be '<' or '>'
        char c = line[2*i];
        ensuref(c == '<' || c == '>',
                "inequalities[%d]: expected '<' or '>', got '%c'", i, c);
        ineq[i] = c;
        // At odd positions we must have exactly one space
        if (i < k-1) {
            char sp = line[2*i + 1];
            ensuref(sp == ' ',
                    "inequalities: expected single space between tokens at index %d", i);
        }
    }

    // Check that there exists at least one assignment of k+1 distinct digits (0..9)
    // satisfying the inequalities.
    vector<bool> used(10, false);
    vector<int> assign(k+1, -1);
    bool hasSolution = false;
    function<void(int)> dfs = [&](int pos) {
        if (hasSolution) return;
        if (pos == k+1) {
            hasSolution = true;
            return;
        }
        for (int d = 0; d <= 9; d++) {
            if (used[d]) continue;
            if (pos > 0) {
                char op = ineq[pos-1];
                int prev = assign[pos-1];
                if (op == '<' && !(prev < d)) continue;
                if (op == '>' && !(prev > d)) continue;
            }
            used[d] = true;
            assign[pos] = d;
            dfs(pos + 1);
            used[d] = false;
            if (hasSolution) return;
        }
    };
    dfs(0);
    ensuref(hasSolution,
            "No solution exists for the given inequality sequence");

    inf.readEof();
    return 0;
}
