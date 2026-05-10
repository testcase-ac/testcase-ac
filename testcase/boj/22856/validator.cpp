#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
#include <cassert>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // We will store for each node: left child, right child
    // Indexing nodes from 1 to N
    vector<int> leftChild(N+1, -1);
    vector<int> rightChild(N+1, -1);
    vector<int> parent(N+1, -1);

    // To check uniqueness of nodes a in input lines
    vector<bool> appeared(N+1, false);

    // Read N lines: a b c
    for (int i = 0; i < N; i++) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(-1, N, "b_i");
        inf.readSpace();
        int c = inf.readInt(-1, N, "c_i");
        inf.readEoln();

        // Check a appears only once
        ensuref(!appeared[a], "Node %d appears more than once as 'a_i'", a);
        appeared[a] = true;

        // Check b and c are either -1 or valid node number
        if (b != -1) {
            ensuref(b >= 1 && b <= N, "Left child b_i=%d of node %d out of range", b, a);
            ensuref(b != a, "Node %d cannot be its own left child", a);
            ensuref(parent[b] == -1, "Node %d has multiple parents (left child of node %d and node %d)", b, parent[b], a);
            parent[b] = a;
            leftChild[a] = b;
        }
        if (c != -1) {
            ensuref(c >= 1 && c <= N, "Right child c_i=%d of node %d out of range", c, a);
            ensuref(c != a, "Node %d cannot be its own right child", a);
            ensuref(parent[c] == -1, "Node %d has multiple parents (right child of node %d and node %d)", c, parent[c], a);
            parent[c] = a;
            rightChild[a] = c;
        }
    }

    // Check all nodes appear exactly once as 'a_i'
    for (int node = 1; node <= N; node++) {
        ensuref(appeared[node], "Node %d does not appear as 'a_i' in input", node);
    }

    // Check root is node 1 and has no parent
    ensuref(parent[1] == -1, "Root node 1 must have no parent");

    // Check that the tree is connected and has no cycles
    // We do BFS from root and count visited nodes
    vector<bool> visited(N+1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    int visitedCount = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        int l = leftChild[u];
        int r = rightChild[u];
        if (l != -1) {
            ensuref(!visited[l], "Cycle or multiple parents detected at node %d (left child of %d)", l, u);
            visited[l] = true;
            q.push(l);
            visitedCount++;
        }
        if (r != -1) {
            ensuref(!visited[r], "Cycle or multiple parents detected at node %d (right child of %d)", r, u);
            visited[r] = true;
            q.push(r);
            visitedCount++;
        }
    }
    ensuref(visitedCount == N, "Tree is not connected: only %d nodes reachable from root out of %d", visitedCount, N);

    // Now we must find the "end node" of the inorder traversal (the last node in inorder)
    // Inorder traversal: left subtree, current node, right subtree
    // We find the inorder sequence and get the last node
    vector<int> inorder_seq;
    // Recursive function to do inorder traversal
    // Use iterative to avoid stack overflow for large N
    vector<int> stack;
    int cur = 1;
    vector<bool> visited_inorder(N+1, false);
    while (true) {
        while (cur != -1) {
            stack.push_back(cur);
            cur = leftChild[cur];
        }
        if (stack.empty()) break;
        int node = stack.back();
        stack.pop_back();
        inorder_seq.push_back(node);
        cur = rightChild[node];
    }
    ensuref((int)inorder_seq.size() == N, "Inorder traversal size %d does not match N=%d", (int)inorder_seq.size(), N);

    int inorder_end_node = inorder_seq.back();

    // Now we simulate the "유사 중위 순회" (pseudo inorder traversal) as described:
    // Start at root (node 1)
    // At each step:
    // 1. If left child exists and not visited, go there
    // 2. Else if right child exists and not visited, go there
    // 3. Else if current node is the inorder end node, stop
    // 4. Else if parent exists, go to parent
    // Repeat until stop

    // We must count the number of moves (each move from one node to another counts as 1)

    // We need to track visited nodes (visited means visited at least once)
    vector<bool> visited_nodes(N+1, false);
    int current = 1;
    visited_nodes[current] = true;
    int moves = 0;

    while (true) {
        int l = leftChild[current];
        int r = rightChild[current];
        if (l != -1 && !visited_nodes[l]) {
            current = l;
            visited_nodes[current] = true;
            moves++;
            continue;
        }
        if (r != -1 && !visited_nodes[r]) {
            current = r;
            visited_nodes[current] = true;
            moves++;
            continue;
        }
        if (current == inorder_end_node) {
            break;
        }
        int p = parent[current];
        ensuref(p != -1, "Current node %d is not end node but has no parent to move up", current);
        current = p;
        moves++;
    }

    // The problem states the answer is the total moves during this traversal.
    // The validator does not need to output moves, but we can check that moves is in a reasonable range:
    // Minimum moves is 0 (N=1)
    // Maximum moves is at most 2*N - 2 (since each edge can be traversed at most twice in this traversal)
    // We check moves >= 0 and moves <= 2*N
    ensuref(moves >= 0, "Moves count negative");
    ensuref(moves <= 2LL*N, "Moves count %d exceeds maximum possible moves 2*N=%d", moves, 2*N);

    // Finally, check that after reading all input lines, there is exactly one newline and then EOF
    inf.readEof();
}
