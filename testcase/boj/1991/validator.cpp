#include "testlib.h"
#include <vector>
#include <string>
#include <stack>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of nodes
    int N = inf.readInt(1, 26, "N");
    inf.readEoln();

    // Storage for the descriptions
    vector<char> parents(N), lefts(N), rights(N);
    // Track which nodes have descriptions
    vector<bool> parentSeen(N, false);

    // Read each node's line
    for (int i = 0; i < N; i++) {
        // parent: single uppercase letter
        string sp = inf.readToken("[A-Z]", "parent");
        inf.readSpace();
        // left child: uppercase letter or '.'
        string sl = inf.readToken("[A-Z\\.]", "left");
        inf.readSpace();
        // right child: uppercase letter or '.'
        string sr = inf.readToken("[A-Z\\.]", "right");
        inf.readEoln();

        char p = sp[0], l = sl[0], r = sr[0];
        // Parent must be in A..A+N-1
        ensuref(p >= 'A' && p < char('A' + N),
                "Parent '%c' at line %d is not in range A..%c",
                p, i+2, char('A' + N - 1));
        int pi = p - 'A';
        // No duplicate parent descriptions
        ensuref(!parentSeen[pi],
                "Duplicate description for node '%c' at line %d",
                p, i+2);
        parentSeen[pi] = true;

        parents[i] = p;
        lefts[i] = l;
        rights[i] = r;
    }

    // All nodes A..A+N-1 must have exactly one description
    for (int c = 0; c < N; c++) {
        if (!parentSeen[c]) {
            ensuref(false,
                    "Missing description for node '%c'",
                    char('A' + c));
        }
    }

    // Check children pointers and count edges
    vector<bool> childHasParent(N, false);
    int edgeCount = 0;
    for (int i = 0; i < N; i++) {
        char p = parents[i];
        int pi = p - 'A';
        // check left child
        if (lefts[i] != '.') {
            char c = lefts[i];
            // in valid range
            ensuref(c >= 'A' && c < char('A' + N),
                    "Left child '%c' of parent '%c' at line %d is not in A..%c",
                    c, p, i+2, char('A' + N - 1));
            int ci = c - 'A';
            // no node can have more than one parent
            ensuref(!childHasParent[ci],
                    "Node '%c' has more than one parent (conflict at parent '%c' line %d)",
                    c, p, i+2);
            childHasParent[ci] = true;
            edgeCount++;
        }
        // check right child
        if (rights[i] != '.') {
            char c = rights[i];
            ensuref(c >= 'A' && c < char('A' + N),
                    "Right child '%c' of parent '%c' at line %d is not in A..%c",
                    c, p, i+2, char('A' + N - 1));
            int ci = c - 'A';
            ensuref(!childHasParent[ci],
                    "Node '%c' has more than one parent (conflict at parent '%c' line %d)",
                    c, p, i+2);
            childHasParent[ci] = true;
            edgeCount++;
        }
    }

    // Root 'A' must have no parent
    ensuref(!childHasParent[0],
            "Root 'A' should not be a child of any node");

    // Must have exactly N-1 edges
    ensuref(edgeCount == N - 1,
            "Number of edges %d does not equal N-1 (%d)",
            edgeCount, N-1);

    // Build adjacency list for directed tree
    vector<vector<int>> adj(N);
    for (int i = 0; i < N; i++) {
        int pi = parents[i] - 'A';
        if (lefts[i] != '.') {
            adj[pi].push_back(lefts[i] - 'A');
        }
        if (rights[i] != '.') {
            adj[pi].push_back(rights[i] - 'A');
        }
    }

    // DFS from root to check connectivity and cycles
    vector<bool> visited(N, false);
    stack<int> st;
    visited[0] = true;
    st.push(0);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        for (int v : adj[u]) {
            ensuref(!visited[v],
                    "Cycle detected: node '%c' revisited from '%c'",
                    char('A' + v), char('A' + u));
            visited[v] = true;
            st.push(v);
        }
    }

    // All nodes must be reachable
    int reachCount = 0;
    for (bool x : visited) if (x) reachCount++;
    ensuref(reachCount == N,
            "Tree is not connected: only %d out of %d nodes reachable from root 'A'",
            reachCount, N);

    // No extra data
    inf.readEof();
    return 0;
}
