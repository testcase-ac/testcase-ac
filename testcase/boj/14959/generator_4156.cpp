#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters: choose small N, then a period p and prefix length k
    int N = rnd.next(1, 10);
    int p = rnd.next(1, N);
    int k = rnd.next(0, N - p);

    // Build the sequence
    vector<int> T(N);
    // Prefix of length k: arbitrary values
    for (int i = 0; i < k; i++) {
        T[i] = rnd.next(0, 999999);
    }
    // Generate a primitive cycle of length p with distinct values
    vector<int> C;
    while ((int)C.size() < p) {
        int x = rnd.next(0, 999999);
        if (find(C.begin(), C.end(), x) == C.end()) {
            C.push_back(x);
        }
    }
    // Fill the tail to enforce T[i+p] = T[i] for all i > k
    for (int i = k; i < N; i++) {
        T[i] = C[(i - k) % p];
    }

    // Output
    println(N);
    println(T);
    return 0;
}
