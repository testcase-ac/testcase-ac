#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of students
    int N = rnd.next(2, 10);
    // Hyperparameters for graph randomness
    double f2p = rnd.next(0.0, 1.0);    // probability to connect friend-of-friend
    double extraP = rnd.next(0.0, 1.0); // extra random edges probability

    // Prepare node list except 1
    vector<int> nodes;
    for (int i = 2; i <= N; i++) nodes.push_back(i);
    shuffle(nodes.begin(), nodes.end());

    // Choose at least one direct friend of 1
    int k1 = rnd.next(1, N-1);
    vector<int> directFriends(nodes.begin(), nodes.begin() + k1);

    // Use a set to avoid duplicate edges
    set<pair<int,int>> edges;

    // Add edges between 1 and its direct friends
    for (int u : directFriends) {
        edges.emplace(1, u);
    }

    // Potential second-degree edges: connect each direct friend to others (excluding 1)
    for (int u : directFriends) {
        for (int v = 2; v <= N; v++) {
            if (v == u) continue;
            if (rnd.next() < f2p) {
                int a = min(u, v), b = max(u, v);
                edges.emplace(a, b);
            }
        }
    }

    // Add some extra random edges among all pairs
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (edges.count({i, j}) == 0 && rnd.next() < extraP) {
                edges.emplace(i, j);
            }
        }
    }

    // Collect edges into a vector and shuffle
    vector<pair<int,int>> out;
    out.insert(out.end(), edges.begin(), edges.end());
    shuffle(out.begin(), out.end());

    // Output
    println(N);
    println((int)out.size());
    for (auto &e : out) {
        println(e.first, e.second);
    }
    return 0;
}
