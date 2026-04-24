#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of nodes
    int N = rnd.next(2, 10);
    // Maximum distinct values less than N to ensure at least one duplicate
    int K = rnd.next(1, N - 1);

    // Assign values with guaranteed duplicate
    vector<int> c(N);
    for (int i = 0; i < N; i++) {
        c[i] = rnd.next(1, K);
    }

    // Build a tree with three shapes: line, star, or random via Prüfer code
    vector<pair<int,int>> edges;
    int shape = rnd.next(0, 2);
    if (shape == 0) {
        // Line
        for (int i = 1; i < N; i++) {
            edges.emplace_back(i, i + 1);
        }
    } else if (shape == 1) {
        // Star
        int center = rnd.next(1, N);
        for (int i = 1; i <= N; i++) {
            if (i != center) edges.emplace_back(center, i);
        }
    } else {
        // Random tree via Prüfer code
        vector<int> prufer(N - 2);
        for (int i = 0; i < N - 2; i++) {
            prufer[i] = rnd.next(1, N);
        }
        vector<int> degree(N + 1, 1);
        for (int x : prufer) degree[x]++;
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 1; i <= N; i++) {
            if (degree[i] == 1) pq.push(i);
        }
        for (int x : prufer) {
            int leaf = pq.top(); pq.pop();
            edges.emplace_back(leaf, x);
            degree[leaf]--;
            degree[x]--;
            if (degree[x] == 1) pq.push(x);
        }
        int u = pq.top(); pq.pop();
        int v = pq.top(); pq.pop();
        edges.emplace_back(u, v);
    }

    // Shuffle edge order for diversity
    shuffle(edges.begin(), edges.end());

    // Output
    println(N);
    println(c);
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
