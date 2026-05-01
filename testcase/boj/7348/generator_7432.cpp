#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        // Generate N moves, biased towards smaller for readability
        int N = rnd.wnext(30, -1) + 1;  // in [1,30], bias small
        println(N);
        // Prepare unique room numbers from 1..200
        vector<int> rooms(200);
        iota(rooms.begin(), rooms.end(), 1);
        shuffle(rooms.begin(), rooms.end());
        rooms.resize(2 * N);
        // Split into two halves for pairing
        vector<int> A(rooms.begin(), rooms.begin() + N);
        vector<int> B(rooms.begin() + N, rooms.end());
        // Hyper-parameter: choose pairing strategy
        double p = rnd.next();
        if (p < 0.3) {
            // Many small intervals: pair sorted-small with sorted-small
            sort(A.begin(), A.end());
            sort(B.begin(), B.end());
        } else if (p < 0.6) {
            // Uniform random pairing
            shuffle(B.begin(), B.end());
        } else {
            // Many large intervals: pair small with large
            sort(A.begin(), A.end());
            sort(B.begin(), B.end(), greater<int>());
        }
        // Output moves
        for (int i = 0; i < N; ++i) {
            println(A[i], B[i]);
        }
    }
    return 0;
}
