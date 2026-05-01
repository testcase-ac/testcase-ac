#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of islands
    int n = rnd.next(3, 10);
    // Number of operations
    int k = rnd.next(5, min(2*n + 5, 20));
    // Number of additions and queries
    int A = rnd.next(1, k-1);
    int Q = k - A;
    // Build operation sequence: ensure first is a query to test unreachable
    vector<int> ops(k);
    ops[0] = 0;
    vector<int> rest;
    // One query used
    for (int i = 0; i < A; i++) rest.push_back(1);
    for (int i = 0; i < Q-1; i++) rest.push_back(0);
    shuffle(rest.begin(), rest.end());
    for (int i = 1; i < k; i++) ops[i] = rest[i-1];
    // Output n and k
    println(n, k);
    // Generate operations
    for (int i = 0; i < k; i++) {
        if (ops[i] == 1) {
            // Add route: choose two distinct islands
            int c = rnd.next(1, n);
            int d = rnd.next(1, n);
            while (d == c) d = rnd.next(1, n);
            // Weight: half small, half large
            int e;
            if (rnd.next(0, 1) == 0) e = rnd.next(1, 100);
            else e = rnd.next(101, 1000000);
            println(1, c, d, e);
        } else {
            // Query
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            while (b == a) b = rnd.next(1, n);
            println(0, a, b);
        }
    }
    return 0;
}
