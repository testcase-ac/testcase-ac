#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: total number of files and directories
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // parent[i] = parent ID of node i; 0 means no parent assigned yet
    vector<int> parent(N+1, 0);
    long long total_children = 0;

    // Read descriptions for IDs 1..N in order
    for (int i = 1; i <= N; i++) {
        // Name: 1 to 16 chars, lowercase letters or digits
        string name = inf.readToken("[a-z0-9]{1,16}", "name");
        inf.readSpace();

        // m: number of children (0 => file, >0 => directory)
        int m = inf.readInt(0, N-1, "m");
        vector<int> children;
        children.reserve(m);

        // Read m child IDs
        for (int j = 0; j < m; j++) {
            inf.readSpace();
            int c = inf.readInt(1, N, "child");

            // No self-loop
            ensuref(c != i,
                    "Self-loop detected: node %d cannot list itself as a child", i);

            // Each node can have only one parent
            ensuref(parent[c] == 0,
                    "Multiple parents for node %d: previous parent %d, new parent %d",
                    c, parent[c], i);

            parent[c] = i;
            children.push_back(c);
        }
        inf.readEoln();

        // Check no duplicate children within this directory
        if (children.size() > 1) {
            sort(children.begin(), children.end());
            for (size_t k = 1; k < children.size(); k++) {
                ensuref(children[k] != children[k-1],
                        "Duplicate child %d in children of node %d",
                        children[k], i);
            }
        }

        total_children += m;
    }

    // The total number of child references must be exactly N-1 (tree edges)
    ensuref(total_children == (long long)N - 1,
            "Total number of children (sum of all m) = %lld, but expected %d",
            total_children, N-1);

    // Every node except the root (ID=1) must have exactly one parent
    for (int i = 2; i <= N; i++) {
        ensuref(parent[i] != 0,
                "Node %d has no parent; input must form a connected tree", i);
    }
    // Root must have no parent
    ensuref(parent[1] == 0,
            "Root node 1 has a parent; root must be ID 1 with no parent");

    inf.readEof();
    return 0;
}
