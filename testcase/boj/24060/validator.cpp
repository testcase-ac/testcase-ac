#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// Simulate merge sort and count the number of writes to A
// Return the total number of writes
// Optionally, can stop early if count > K, but for validation, we need the exact count
long long merge_sort_and_count(vector<int>& A, int l, int r, vector<int>& tmp) {
    long long cnt = 0;
    if (l < r) {
        int m = (l + r) / 2;
        cnt += merge_sort_and_count(A, l, m, tmp);
        cnt += merge_sort_and_count(A, m + 1, r, tmp);

        int i = l, j = m + 1, t = 0;
        while (i <= m && j <= r) {
            if (A[i] <= A[j]) tmp[t++] = A[i++];
            else tmp[t++] = A[j++];
        }
        while (i <= m) tmp[t++] = A[i++];
        while (j <= r) tmp[t++] = A[j++];

        for (int k = 0; k < t; ++k) {
            A[l + k] = tmp[k];
            cnt++;
        }
    }
    return cnt;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(5, 500000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100000000, "K");
    inf.readEoln();

    // Read A
    vector<int> A = inf.readInts(N, 1, 1000000000, "A_i");
    inf.readEoln();

    // Check all elements are distinct
    set<int> aset(A.begin(), A.end());
    ensuref((int)aset.size() == N, "Array A contains duplicate elements");

    // Validate that the number of writes during merge sort is at most 108
    // (Implied by: "If the number of writes is less than K, output -1")
    // So, for any input, the number of writes can be less than K, but never more than 108
    // But since K can be up to 1e8, and N up to 5e5, we must check that the number of writes is <= 1e8
    // (Otherwise, the answer is always -1 for K > total_writes.)

    // But more importantly, the problem says: "If the number of writes is less than K, output -1"
    // So, for any input, the number of writes can be less than K, but never more than 1e8.
    // But the only global property is that the array is of size N, all elements are distinct, and in range.

    // However, let's check that the number of writes does not overflow int (i.e., is <= N*logN)
    // and that the simulation does not overflow.

    // Simulate merge sort and count the number of writes
    vector<int> Acopy = A;
    vector<int> tmp(N);
    long long total_writes = merge_sort_and_count(Acopy, 0, N - 1, tmp);

    // The number of writes must be at most N*ceil(log2(N)) (for N=5e5, that's about 9.5 million)
    // But K can be up to 1e8, so it's fine.
    // Let's check that total_writes <= 1e8 (since K can be up to 1e8, and the answer is -1 if K > total_writes)
    ensuref(total_writes <= 100000000LL, "Total number of writes during merge sort exceeds 1e8: %lld", total_writes);

    inf.readEof();
}
