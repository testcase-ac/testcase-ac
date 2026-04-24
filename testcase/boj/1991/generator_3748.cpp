#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of nodes: between 1 and 10 (max 26 allowed by problem, but we keep small)
    int N = rnd.next(1, 10);
    // Prepare child arrays: -1 means no child ('.')
    vector<int> lc(N, -1), rc(N, -1);

    // Choose shape type for diversity: 0=random tree, 1=left chain, 2=right chain, 3=complete tree
    int shape = rnd.next(0, 3);

    if (shape == 0) {
        // Random binary tree: each new node attaches to a random free slot
        vector<pair<int, bool>> slots; // (parent, isLeftSlot)
        // initially root has two free slots
        if (N > 0) {
            slots.emplace_back(0, true);
            slots.emplace_back(0, false);
        }
        for (int i = 1; i < N; i++) {
            int idx = rnd.next(0, int(slots.size()) - 1);
            int p = slots[idx].first;
            bool toLeft = slots[idx].second;
            // assign child
            if (toLeft) lc[p] = i;
            else rc[p] = i;
            // remove used slot
            slots[idx] = slots.back();
            slots.pop_back();
            // new node has two free slots
            slots.emplace_back(i, true);
            slots.emplace_back(i, false);
        }
    } else if (shape == 1) {
        // Strict left chain: A->B->C->...
        for (int i = 1; i < N; i++) {
            lc[i-1] = i;
        }
    } else if (shape == 2) {
        // Strict right chain: A->B->C->...
        for (int i = 1; i < N; i++) {
            rc[i-1] = i;
        }
    } else {
        // Complete binary tree in level order
        for (int i = 1; i < N; i++) {
            int p = (i - 1) / 2;
            if (lc[p] == -1) lc[p] = i;
            else rc[p] = i;
        }
    }

    // Output
    println(N);
    // Print lines sorted by node name: 'A'+i
    for (int i = 0; i < N; i++) {
        char p = char('A' + i);
        char lch = lc[i] == -1 ? '.' : char('A' + lc[i]);
        char rch = rc[i] == -1 ? '.' : char('A' + rc[i]);
        // format "X Y Z"
        string line;
        line += p; line += ' ';
        line += lch; line += ' ';
        line += rch;
        println(line);
    }
    return 0;
}
