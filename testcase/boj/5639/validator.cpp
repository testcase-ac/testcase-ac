#include "testlib.h"
#include <vector>
#include <unordered_set>
#include <tuple>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read all node values: one per line, until EOF.
    vector<int> a;
    int line_no = 0;
    // We expect at least one line. Use eof() to detect end.
    while (!inf.eof()) {
        // Read one integer on a line.
        line_no++;
        int x = inf.readInt(1, 999999, "value");
        inf.readEoln();
        a.push_back(x);
        ensuref((int)a.size() <= 10000,
                "Node count %d exceeds limit of 10000", (int)a.size());
    }
    // Must have at least one node.
    ensuref(!a.empty(), "Empty input: at least one node is required");

    // Check uniqueness of values.
    {
        unordered_set<int> seen;
        seen.reserve(a.size());
        for (int i = 0; i < (int)a.size(); i++) {
            auto res = seen.insert(a[i]);
            ensuref(res.second,
                    "Duplicate key %d found at line %d", a[i], i+1);
        }
    }

    // Validate that 'a' is a valid preorder traversal of a BST.
    // We'll use an explicit stack to avoid deep recursion.
    // Each frame: [l, r) is the subtree in a[], with allowed (minv, maxv).
    struct Frame { int l, r; int minv, maxv; };
    vector<Frame> stk;
    stk.reserve(a.size());
    // allowed initial range: (0, 1e6)
    stk.push_back({0, (int)a.size(), 0, 1000000});
    while (!stk.empty()) {
        Frame f = stk.back(); stk.pop_back();
        int l = f.l, r = f.r;
        if (l >= r) continue;
        int root = a[l];
        // root must lie strictly between minv and maxv
        ensuref(root > f.minv && root < f.maxv,
                "Value %d at line %d not in valid range (%d, %d)",
                root, l+1, f.minv, f.maxv);
        // find split point: first index m in (l+1..r) where a[m] > root
        int m = l + 1;
        while (m < r && a[m] < root) m++;
        // In the right subtree [m..r), all values must be > root
        for (int i = m; i < r; i++) {
            ensuref(a[i] > root,
                    "Invalid preorder at line %d: value %d <= root %d",
                    i+1, a[i], root);
        }
        // Push right and left frames
        // right: [m, r), allowed (root, maxv)
        stk.push_back({m, r, root, f.maxv});
        // left: [l+1, m), allowed (minv, root)
        stk.push_back({l+1, m, f.minv, root});
    }

    // Final checks: exactly at EOF now.
    inf.readEof();
    return 0;
}
