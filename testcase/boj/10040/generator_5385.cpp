#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small sizes
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 20);

    // Generate N distinct costs in [1,1000] and sort descending (costs must be strictly decreasing)
    vector<int> pool(1000);
    iota(pool.begin(), pool.end(), 1);
    shuffle(pool.begin(), pool.end());
    vector<int> A(pool.begin(), pool.begin() + N);
    sort(A.begin(), A.end(), greater<int>());

    // Compute threshold intervals [low[i], high[i]] for voting for game i (1-based fun order)
    vector<int> low(N), high(N);
    for (int i = 0; i < N; i++) {
        low[i] = A[i];
        high[i] = (i == 0 ? 1000 : A[i - 1] - 1);
    }

    // Assign vote counts ensuring a unique winner
    vector<int> v(N, 0);
    int W = rnd.next(0, N - 1);
    // To ensure we can distribute the remaining votes so that nobody ties the winner,
    // winVotes must satisfy remain = M-winVotes <= (N-1)*(winVotes-1)
    int lowerWin = (M + 2 * N - 2) / N;
    lowerWin = max(lowerWin, 1);
    int winVotes = rnd.next(lowerWin, M);
    v[W] = winVotes;
    int remain = M - winVotes;

    // Distribute remaining votes among other games, each at most winVotes-1
    vector<int> idx;
    for (int i = 0; i < N; i++) if (i != W) idx.push_back(i);
    int K = idx.size();
    for (int i = 0; i < K; i++) {
        int cellsLeft = K - i;
        int maxPer = winVotes - 1;
        int lower = max(0, remain - (cellsLeft - 1) * maxPer);
        int upper = min(maxPer, remain);
        int x = rnd.next(lower, upper);
        v[idx[i]] = x;
        remain -= x;
    }

    // Generate thresholds B_j so that exactly v[i] votes go to game i
    vector<int> B;
    for (int i = 0; i < N; i++) {
        for (int cnt = 0; cnt < v[i]; cnt++) {
            B.push_back(rnd.next(low[i], high[i]));
        }
    }
    shuffle(B.begin(), B.end());

    // Output
    println(N, M);
    for (int x : A) println(x);
    for (int x : B) println(x);
    return 0;
}
