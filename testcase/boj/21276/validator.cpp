#include "testlib.h"
#include <vector>
#include <string>
#include <map>
#include <functional>

using namespace std;

const int MAXN = 1000;

// R[d][a] = true  <=>  a is an ancestor of d (from input)
static bool R[MAXN][MAXN];
// newRel[d][a] = true  <=>  a is an ancestor of d (reconstructed from tree)
static bool newRel[MAXN][MAXN];

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    vector<string> names(N);
    map<string, int> id;

    for (int i = 0; i < N; ++i) {
        if (i > 0) inf.readSpace();
        string name = inf.readToken("[a-z]{1,6}", "name_i");
        ensuref(!id.count(name), "Duplicate name '%s' at position %d", name.c_str(), i + 1);
        id[name] = i;
        names[i] = name;
    }
    inf.readEoln();

    long long maxM = 1LL * N * (N - 1) / 2;
    int M = inf.readInt(0, (int)maxM, "M");
    inf.readEoln();

    // Initialize R and newRel (static globals are already zero-initialized,
    // but be explicit in case of future changes).
    for (int i = 0; i < MAXN; ++i)
        for (int j = 0; j < MAXN; ++j)
            R[i][j] = newRel[i][j] = false;

    vector<vector<int>> ancList(N); // ancList[d] = list of ancestors of d (from input)

    for (int i = 0; i < M; ++i) {
        string X = inf.readToken("[a-z]{1,6}", "descendant");
        inf.readSpace();
        string Y = inf.readToken("[a-z]{1,6}", "ancestor");
        inf.readEoln();

        auto itX = id.find(X);
        ensuref(itX != id.end(), "Unknown descendant name '%s' on relation line %d", X.c_str(), i + 1);
        auto itY = id.find(Y);
        ensuref(itY != id.end(), "Unknown ancestor name '%s' on relation line %d", Y.c_str(), i + 1);

        int d = itX->second;
        int a = itY->second;

        ensuref(d != a, "Person '%s' cannot be their own ancestor (line %d)", X.c_str(), i + 1);
        ensuref(!R[d][a], "Duplicate relation: (%s, %s) on line %d", X.c_str(), Y.c_str(), i + 1);

        R[d][a] = true;
        ancList[d].push_back(a);
    }

    // Compute number of ancestors for each person
    vector<int> ancCount(N);
    for (int i = 0; i < N; ++i)
        ancCount[i] = (int)ancList[i].size();

    // Reconstruct parent for each node assuming:
    //  - Each clan is a rooted tree.
    //  - Input gives the full ancestor transitive closure.
    //
    // In such a tree, ancCount[v] = depth(v), and for each non-root v
    // there is a unique parent p with ancCount[p] == ancCount[v] - 1.
    vector<int> parent(N, -1);
    int rootCount = 0;

    for (int v = 0; v < N; ++v) {
        if (ancCount[v] == 0) {
            parent[v] = -1;
            ++rootCount;
            continue;
        }

        int target = ancCount[v] - 1;
        int par = -1;

        for (int a : ancList[v]) {
            ensuref(ancCount[a] < ancCount[v],
                    "Inconsistent ancestor counts: ancestor '%s' (ancCount=%d) "
                    "not less than descendant '%s' (ancCount=%d)",
                    names[a].c_str(), ancCount[a],
                    names[v].c_str(), ancCount[v]);

            if (ancCount[a] == target) {
                if (par == -1) {
                    par = a;
                } else {
                    ensuref(false,
                            "Multiple possible parents for '%s': '%s' and '%s' "
                            "(both have %d ancestors)",
                            names[v].c_str(),
                            names[par].c_str(),
                            names[a].c_str(),
                            target);
                }
            }
        }

        ensuref(par != -1,
                "No valid parent with %d ancestors found for '%s'; "
                "ancestor information incomplete or inconsistent",
                target, names[v].c_str());
        parent[v] = par;
    }

    ensuref(rootCount >= 1, "There must be at least one root (found %d)", rootCount);

    // Build children adjacency list from parents
    vector<vector<int>> children(N);
    for (int v = 0; v < N; ++v) {
        if (parent[v] != -1) {
            children[parent[v]].push_back(v);
        }
    }

    // Recompute the full ancestor relation newRel from the reconstructed forest:
    // For each root, DFS and propagate all ancestors along the path.
    vector<int> stack;
    stack.reserve(N);

    function<void(int)> dfs = [&](int v) {
        // All nodes currently in stack are ancestors of v
        for (int anc : stack) {
            newRel[v][anc] = true;
        }
        stack.push_back(v);
        for (int ch : children[v]) {
            dfs(ch);
        }
        stack.pop_back();
    };

    for (int v = 0; v < N; ++v) {
        if (parent[v] == -1) {
            stack.clear();
            dfs(v);
        }
    }

    // Compare input relation R with the reconstructed closure newRel.
    // They must match exactly if the input is a consistent full ancestor closure
    // of a forest of rooted trees.
    for (int d = 0; d < N; ++d) {
        ensuref(!newRel[d][d],
                "Internal tree reconstruction error: person '%s' became their own ancestor",
                names[d].c_str());
        for (int a = 0; a < N; ++a) {
            if (R[d][a] != newRel[d][a]) {
                ensuref(false,
                        "Ancestor relation mismatch for descendant '%s' and ancestor '%s': "
                        "input=%d, reconstructed=%d",
                        names[d].c_str(), names[a].c_str(),
                        (int)R[d][a], (int)newRel[d][a]);
            }
        }
    }

    inf.readEof();
}
