#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

struct Segment {
    int in_lo, in_hi;
    int post_lo, post_hi;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Read inorder sequence
    vector<int> inorder = inf.readInts(n, 1, n, "inorder");
    inf.readEoln();

    // Read postorder sequence
    vector<int> postorder = inf.readInts(n, 1, n, "postorder");
    inf.readEoln();

    // Check that inorder has no duplicates
    vector<char> seen(n+1, 0);
    for (int i = 0; i < n; i++) {
        int x = inorder[i];
        ensuref(!seen[x],
                "Duplicate value in inorder at position %d: %d",
                i+1, x);
        seen[x] = 1;
    }

    // Check that postorder has no duplicates
    fill(seen.begin(), seen.end(), 0);
    for (int i = 0; i < n; i++) {
        int x = postorder[i];
        ensuref(!seen[x],
                "Duplicate value in postorder at position %d: %d",
                i+1, x);
        seen[x] = 1;
    }

    // Build map from node value to its index in inorder
    vector<int> pos(n+1, -1);
    for (int i = 0; i < n; i++) {
        pos[inorder[i]] = i;
    }

    // Now validate that inorder and postorder describe a valid binary tree
    vector<Segment> stk;
    stk.reserve(n);
    stk.push_back({0, n-1, 0, n-1});

    while (!stk.empty()) {
        Segment seg = stk.back();
        stk.pop_back();

        int in_lo    = seg.in_lo;
        int in_hi    = seg.in_hi;
        int post_lo  = seg.post_lo;
        int post_hi  = seg.post_hi;

        // Empty subtree
        if (in_lo > in_hi) continue;

        int seg_in_len   = in_hi - in_lo + 1;
        int seg_post_len = post_hi - post_lo + 1;
        ensuref(seg_in_len == seg_post_len,
                "Segment length mismatch: inorder[%d..%d] has length %d, "
                "postorder[%d..%d] has length %d",
                in_lo+1, in_hi+1, seg_in_len,
                post_lo+1, post_hi+1, seg_post_len);

        // Root of this subtree is last of postorder segment
        int root = postorder[post_hi];
        int idx  = pos[root];
        ensuref(idx >= in_lo && idx <= in_hi,
                "Value %d at postorder position %d not found in inorder[%d..%d]",
                root, post_hi+1, in_lo+1, in_hi+1);

        int left_size  = idx - in_lo;
        int right_size = in_hi - idx;
        ensuref(left_size + 1 + right_size == seg_post_len,
                "Subtree size mismatch at root %d: left_size=%d, right_size=%d, total=%d",
                root, left_size, right_size, seg_post_len);

        // Push right subtree
        if (right_size > 0) {
            stk.push_back({
                idx + 1,
                in_hi,
                post_lo + left_size,
                post_hi - 1
            });
        }
        // Push left subtree
        if (left_size > 0) {
            stk.push_back({
                in_lo,
                idx - 1,
                post_lo,
                post_lo + left_size - 1
            });
        }
    }

    inf.readEof();
    return 0;
}
