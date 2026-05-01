#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int Z = rnd.next(1, 5);
    println(Z);
    for (int zi = 0; zi < Z; zi++) {
        // Number of investments and benefits
        int A = rnd.next(1, 10);
        int B = rnd.next(1, 10);
        println(A, B);
        // Costs of investments
        vector<int> cost(A);
        for (int i = 0; i < A; i++) {
            // Mix of cheap and expensive investments
            if (rnd.next(0, 1) == 0)
                cost[i] = rnd.next(1, 1000);
            else
                cost[i] = rnd.wnext(1000000, rnd.next(-1, 1)) + 1;
        }
        println(cost);
        // Revenues of benefits
        vector<int> rev(B);
        for (int i = 0; i < B; i++) {
            // Some uniform, some weighted
            if (rnd.next(0, 1) == 0)
                rev[i] = rnd.next(1, 1000);
            else
                rev[i] = rnd.wnext(1000000, rnd.next(-1, 1)) + 1;
        }
        println(rev);
        // Dependencies
        int maxPairs = A * B;
        int t = rnd.any(vector<int>{-2, -1, 0, 1, 2});
        int K = rnd.wnext(maxPairs, t) + 1; // 1 to A*B
        // Build all possible pairs and pick K
        vector<pair<int,int>> deps;
        deps.reserve(maxPairs);
        for (int x = 1; x <= A; x++)
            for (int y = 1; y <= B; y++)
                deps.emplace_back(x, y);
        shuffle(deps.begin(), deps.end());
        deps.resize(K);
        println(K);
        for (auto &p : deps)
            println(p.first, p.second);
    }
    return 0;
}
