#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

// Build a "balanced" insertion order so that insertion sequence == preorder
void buildBalanced(const vector<int>& a, vector<int>& out) {
    int n = a.size();
    if (n == 0) return;
    int mid = n / 2;
    // For even sizes, randomly pick lower or upper middle for diversity
    if (n % 2 == 0 && rnd.next(0, 1)) mid = mid - 1;
    out.push_back(a[mid]);
    vector<int> left(a.begin(), a.begin() + mid);
    vector<int> right(a.begin() + mid + 1, a.end());
    buildBalanced(left, out);
    buildBalanced(right, out);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of nodes
    int N = rnd.next(1, 10);

    // Keys are 1..N to keep it small and hand-checkable
    vector<int> keys(N);
    for (int i = 0; i < N; i++) keys[i] = i + 1;

    // Hyper-parameter: shape mode (0 = increasing chain, 1 = decreasing chain, 2 = balanced tree)
    int mode = rnd.next(0, 2);

    vector<int> insertionOrder;
    if (mode == 0) {
        // Chain to the right: 1,2,3,...
        insertionOrder = keys;
    } else if (mode == 1) {
        // Chain to the left: N,N-1,...
        insertionOrder = keys;
        reverse(insertionOrder.begin(), insertionOrder.end());
    } else {
        // Balanced
        buildBalanced(keys, insertionOrder);
    }

    // The insertion order for these shapes equals the preorder traversal.
    // Print each key on its own line (no count given in input)
    for (int x : insertionOrder) {
        println(x);
    }

    return 0;
}
