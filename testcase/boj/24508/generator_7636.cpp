#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int mode = rnd.next(0, 3);
    int N, K;
    long long T;
    vector<int> A;

    if (mode == 0) {
        // sum % K != 0 case
        N = rnd.next(2, 10);
        K = rnd.next(2, 20);
        A.resize(N);
        int sum;
        do {
            sum = 0;
            for (int i = 0; i < N; i++) {
                A[i] = rnd.next(0, K - 1);
                sum += A[i];
            }
        } while (sum == 0 || sum % K == 0);
        T = rnd.next(0, sum + K);
    } else if (mode == 1) {
        // sum == K, but T too small (NO)
        N = rnd.next(2, 10);
        K = rnd.next(2, 20);
        int sum1 = rnd.next(1, K - 1);
        // partition sum1 into N-1 parts
        vector<int> cuts;
        cuts.push_back(0);
        cuts.push_back(sum1);
        for (int i = 0; i < N - 2; i++) {
            cuts.push_back(rnd.next(0, sum1));
        }
        sort(cuts.begin(), cuts.end());
        A.clear();
        for (int i = 0; i + 1 < (int)cuts.size(); i++) {
            A.push_back(cuts[i+1] - cuts[i]);
        }
        // last basket
        A.push_back(K - sum1);
        shuffle(A.begin(), A.end());
        int maxA = *max_element(A.begin(), A.end());
        int minMoves = K - maxA; // at least 1
        T = rnd.next(0, minMoves - 1);
    } else if (mode == 2) {
        // sum == K, T sufficient (YES)
        N = rnd.next(2, 10);
        K = rnd.next(2, 20);
        int sum1 = rnd.next(1, K - 1);
        // partition sum1 into N-1 parts
        vector<int> cuts;
        cuts.push_back(0);
        cuts.push_back(sum1);
        for (int i = 0; i < N - 2; i++) {
            cuts.push_back(rnd.next(0, sum1));
        }
        sort(cuts.begin(), cuts.end());
        A.clear();
        for (int i = 0; i + 1 < (int)cuts.size(); i++) {
            A.push_back(cuts[i+1] - cuts[i]);
        }
        A.push_back(K - sum1);
        shuffle(A.begin(), A.end());
        int maxA = *max_element(A.begin(), A.end());
        int minMoves = K - maxA;
        T = rnd.next(minMoves, minMoves + 5);
    } else {
        // sum == 2K, multiple explosions, T large (YES)
        N = rnd.next(4, 10);
        K = rnd.next(2, 20);
        A.assign(N, 0);
        int rem = 2 * K;
        while (rem > 0) {
            int i = rnd.next(0, N - 1);
            if (A[i] < K - 1) {
                A[i]++;
                rem--;
            }
        }
        shuffle(A.begin(), A.end());
        T = rnd.next(K, 5 * K);
    }

    // Output the test case
    println(N, K, T);
    println(A);
    return 0;
}
