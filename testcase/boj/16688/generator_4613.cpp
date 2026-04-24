#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small n for hand-checkable cases
    int n = rnd.next(1, 10);
    int k = rnd.next(1, n);
    // Hyper-parameter to bias number of distinct difficulties
    int bias = rnd.next(-1, 1);
    int distinct0 = rnd.wnext(n, bias); // in [0, n-1]
    int distinctCount = distinct0 + 1;  // in [1, n]
    // Generate distinct difficulty values from 1..20
    vector<int> pool(20);
    iota(pool.begin(), pool.end(), 1);
    shuffle(pool.begin(), pool.end());
    vector<int> vals(pool.begin(), pool.begin() + distinctCount);
    // Assign multiplicities summing to n
    vector<int> mult(distinctCount, 1);
    int rem = n - distinctCount;
    for (int i = 0; i < rem; i++) {
        int idx = rnd.next(0, distinctCount - 1);
        mult[idx]++;
    }
    // Build the difficulty array and shuffle
    vector<int> a;
    for (int i = 0; i < distinctCount; i++) {
        for (int j = 0; j < mult[i]; j++) {
            a.push_back(vals[i]);
        }
    }
    shuffle(a.begin(), a.end());
    // Output
    println(n, k);
    println(a);
    return 0;
}
