#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Sequence size and query count
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 20);
    // Sequence value bounds
    int minA = rnd.next(1, 10);
    int maxA = rnd.next(minA, min(minA + 50, 1000000000));
    int tA = rnd.next(-3, 3);
    // Build sequence
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = minA + rnd.wnext(maxA - minA + 1, tA);
    }
    // Output sequence
    println(N);
    println(A);
    println(M);
    // Generate queries with XOR-based encoding
    long long last_ans = 0;
    for (int qi = 0; qi < M; qi++) {
        // Hyper: probability of small interval
        double p_small = rnd.next(0.0, 1.0);
        int len;
        if (rnd.next() < p_small) {
            len = rnd.next(0, min(N - 1, 2));
        } else {
            len = rnd.next(0, N - 1);
        }
        int i = rnd.next(1, N - len);
        int j = i + len;
        // Hyper: choose k low or high
        bool low = rnd.next(0, 1) == 0;
        int highK = (int)min(1000000000LL, (long long)maxA + (maxA - minA));
        int k;
        if (low) {
            k = rnd.next(1, maxA);
        } else {
            k = rnd.next(maxA, highK);
        }
        // Compute raw a,b,c so that after XOR with last_ans we get i,j,k
        long long a_raw = i ^ last_ans;
        long long b_raw = j ^ last_ans;
        long long c_raw = k ^ last_ans;
        println(a_raw, b_raw, c_raw);
        // Simulate answer and update last_ans
        int cnt = 0;
        for (int x = i - 1; x < j; x++) if (A[x] > k) cnt++;
        last_ans = cnt;
    }
    return 0;
}
