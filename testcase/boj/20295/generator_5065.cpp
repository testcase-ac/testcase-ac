#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size for hand-checkability
    int N = rnd.next(2, 10);

    // Assign candy types (1 to 5) to each shop
    vector<int> candy(N);
    for (int i = 0; i < N; i++) {
        candy[i] = rnd.next(1, 5);
    }

    // Build a tree with different shapes for diversity
    vector<pair<int,int>> edges;
    int shapeType = rnd.next(0, 2);
    if (shapeType == 0) {
        // Chain
        for (int i = 1; i < N; i++) {
            edges.emplace_back(i, i+1);
        }
    } else if (shapeType == 1) {
        // Star
        int center = rnd.next(1, N);
        for (int i = 1; i <= N; i++) {
            if (i != center) edges.emplace_back(center, i);
        }
    } else {
        // Random tree (random parent)
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i-1);
            edges.emplace_back(p, i);
        }
    }
    // Randomize edge order
    shuffle(edges.begin(), edges.end());

    // Number of friends
    int M = rnd.next(1, 10);

    // Generate friend queries
    vector<pair<int,int>> friends;
    for (int i = 0; i < M; i++) {
        int loc = rnd.next(1, N);
        int fav = rnd.next(1, 5);
        friends.emplace_back(loc, fav);
    }

    // Output
    println(N);
    println(candy);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    println(M);
    for (auto &f : friends) {
        println(f.first, f.second);
    }

    return 0;
}
