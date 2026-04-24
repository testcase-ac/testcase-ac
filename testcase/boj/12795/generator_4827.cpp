#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter: total operations Q between 5 and 15
    int Q = rnd.next(5, 15);
    // Ensure at least one query
    int K = Q - 1;
    int qCnt = rnd.next(1, K);
    int aCnt = K - qCnt;

    // Build operation types: 1 for add, 2 for query
    vector<int> ops;
    for (int i = 0; i < aCnt; i++) ops.push_back(1);
    for (int i = 0; i < qCnt; i++) ops.push_back(2);
    shuffle(ops.begin(), ops.end());
    // First operation must be an add
    ops.insert(ops.begin(), 1);

    // Limits
    const ll A_LIM = 1000000;
    const ll B_LIM = 1000000000000LL;
    const ll X_LIM = 1000000000000LL;

    // Output Q
    println(Q);
    // Generate operations
    for (int op : ops) {
        if (op == 1) {
            // Add line y = a x + b
            ll a = rnd.next(-A_LIM, A_LIM);
            ll b = rnd.next(-B_LIM, B_LIM);
            println(1, a, b);
        } else {
            // Query at x
            ll x = rnd.next(-X_LIM, X_LIM);
            println(2, x);
        }
    }

    return 0;
}
