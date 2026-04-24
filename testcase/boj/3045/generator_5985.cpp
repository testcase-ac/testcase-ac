#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of nodes
    int N = rnd.next(2, 10);
    // Number of operations, sometimes small, sometimes large
    int maxM = N * 2;
    int t = rnd.next(0, 1) ? 1 : -1; // bias high when 1, low when -1
    int M = rnd.wnext(maxM, t);

    // Probability of choosing operation A
    double aProb = rnd.next(0.0, 1.0);

    // Simulate the list to keep operations valid
    vector<int> lst(N);
    iota(lst.begin(), lst.end(), 1);

    // Store operations
    vector<pair<char, pair<int,int>>> ops;
    ops.reserve(M);

    for (int i = 0; i < M; i++) {
        char op = (rnd.next() < aProb ? 'A' : 'B');
        int X = rnd.next(1, N);
        int Y = rnd.next(1, N);
        while (Y == X) Y = rnd.next(1, N);

        // Remove X
        auto itX = find(lst.begin(), lst.end(), X);
        lst.erase(itX);
        // Find Y in the updated list
        auto itY = find(lst.begin(), lst.end(), Y);

        // Insert X before or after Y
        if (op == 'A') {
            lst.insert(itY, X);
        } else {
            lst.insert(itY + 1, X);
        }
        ops.emplace_back(op, make_pair(X, Y));
    }

    // Output
    println(N, M);
    for (auto &e : ops) {
        // print operation, X, Y
        println(string(1, e.first), e.second.first, e.second.second);
    }
    return 0;
}
