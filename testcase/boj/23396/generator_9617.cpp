#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N, M, K;
    long long C;
    vector<vector<long long>> P;
    vector<pair<int,int>> friendsList;

    int caseType = rnd.next(0, 7);

    if (caseType == 0) {
        // Tiny baseline: very small N, M
        N = rnd.next(1, 3);
        M = rnd.next(1, 3);
        int maxPairs = N * (N - 1) / 2;
        K = (maxPairs == 0) ? 0 : rnd.next(0, min(maxPairs, 2));
        C = rnd.next(0, 5);

        P.assign(N, vector<long long>(M));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                P[i][j] = rnd.next(0, 9);

        vector<pair<int,int>> allPairs;
        for (int a = 1; a <= N; a++)
            for (int b = a + 1; b <= N; b++)
                allPairs.emplace_back(a, b);
        shuffle(allPairs.begin(), allPairs.end());
        for (int i = 0; i < K; i++)
            friendsList.push_back(allPairs[i]);

    } else if (caseType == 1) {
        // Degenerate dimension: N=1 or M=1
        if (rnd.next(0, 1) == 0) {
            N = 1;
            M = rnd.next(2, 10);
        } else {
            M = 1;
            N = rnd.next(2, 10);
        }
        int maxPairs = N * (N - 1) / 2;
        if (maxPairs == 0) K = 0;
        else K = rnd.next(0, min(maxPairs, 5));
        C = rnd.next(0, 20);

        P.assign(N, vector<long long>(M));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                P[i][j] = rnd.next(0, 20);

        vector<pair<int,int>> allPairs;
        for (int a = 1; a <= N; a++)
            for (int b = a + 1; b <= N; b++)
                allPairs.emplace_back(a, b);
        shuffle(allPairs.begin(), allPairs.end());
        for (int i = 0; i < K; i++)
            friendsList.push_back(allPairs[i]);

    } else if (caseType == 2) {
        // No penalty: C = 0, friendships irrelevant
        N = rnd.next(2, 8);
        M = rnd.next(2, 8);
        int maxPairs = N * (N - 1) / 2;
        K = (maxPairs == 0) ? 0 : rnd.next(0, min(maxPairs, 6));
        C = 0;

        P.assign(N, vector<long long>(M));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                P[i][j] = rnd.next(0, 50);

        vector<pair<int,int>> allPairs;
        for (int a = 1; a <= N; a++)
            for (int b = a + 1; b <= N; b++)
                allPairs.emplace_back(a, b);
        shuffle(allPairs.begin(), allPairs.end());
        for (int i = 0; i < K; i++)
            friendsList.push_back(allPairs[i]);

    } else if (caseType == 3) {
        // No friendships: K = 0
        N = rnd.next(3, 10);
        M = rnd.next(3, 10);
        K = 0;
        C = rnd.next(0, 100);

        P.assign(N, vector<long long>(M));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                P[i][j] = rnd.next(0, 30);

        // friendsList stays empty

    } else if (caseType == 4) {
        // High penalty, complete friendship graph
        N = rnd.next(3, 7);
        M = rnd.next(2, 7);
        K = N * (N - 1) / 2;
        C = rnd.next(50, 200);

        P.assign(N, vector<long long>(M));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                long long base = rnd.next(0, 20);
                long long bias = rnd.next(0, 3) * j;
                P[i][j] = base + bias;
            }
        }

        for (int a = 1; a <= N; a++)
            for (int b = a + 1; b <= N; b++)
                friendsList.emplace_back(a, b);
        // Optionally shuffle friends
        shuffle(friendsList.begin(), friendsList.end());

    } else if (caseType == 5) {
        // Friend chain with gradient-like preferences
        N = rnd.next(4, 10);
        M = rnd.next(4, 10);
        K = N - 1;
        C = rnd.next(1, 20);

        P.assign(N, vector<long long>(M));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                // Odd-indexed players like right side, even-indexed like left side
                int pos = (i % 2 == 0) ? (j + 1) : (M - j);
                P[i][j] = pos * 10 + rnd.next(0, 3);
            }
        }

        for (int i = 1; i <= N - 1; i++)
            friendsList.emplace_back(i, i + 1);

    } else if (caseType == 6) {
        // Random dense friendships with moderate penalty
        N = rnd.next(5, 10);
        M = rnd.next(2, 7);
        int maxPairs = N * (N - 1) / 2;
        K = rnd.next(1, min(maxPairs, 15));
        C = rnd.next(1, 50);

        P.assign(N, vector<long long>(M));

        int pattern = rnd.next(0, 2);
        if (pattern == 0) {
            // Fully random
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    P[i][j] = rnd.next(0, 20);
        } else if (pattern == 1) {
            // Same row pattern for all players
            vector<long long> baseRow(M);
            for (int j = 0; j < M; j++)
                baseRow[j] = rnd.next(0, 20);
            for (int i = 0; i < N; i++)
                P[i] = baseRow;
        } else {
            // All equal or small variation
            long long base = rnd.next(0, 10);
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    P[i][j] = base + rnd.next(0, 2);
        }

        vector<pair<int,int>> allPairs;
        for (int a = 1; a <= N; a++)
            for (int b = a + 1; b <= N; b++)
                allPairs.emplace_back(a, b);
        shuffle(allPairs.begin(), allPairs.end());
        for (int i = 0; i < K; i++)
            friendsList.push_back(allPairs[i]);

    } else { // caseType == 7
        // Central position preferred, moderate penalties
        N = rnd.next(3, 6);
        M = rnd.next(2, 5);
        int maxPairs = N * (N - 1) / 2;
        K = (maxPairs == 0) ? 0 : rnd.next(0, min(maxPairs, 8));
        C = rnd.next(1, 5);

        int mid = (M + 1) / 2;
        P.assign(N, vector<long long>(M));
        for (int i = 0; i < N; i++) {
            long long base = rnd.next(5, 20);
            long long delta = rnd.next(1, 5);
            for (int j = 0; j < M; j++) {
                long long val = base - delta * llabs((long long)(j + 1 - mid));
                if (val < 0) val = 0;
                P[i][j] = val;
            }
        }

        vector<pair<int,int>> allPairs;
        for (int a = 1; a <= N; a++)
            for (int b = a + 1; b <= N; b++)
                allPairs.emplace_back(a, b);
        shuffle(allPairs.begin(), allPairs.end());
        for (int i = 0; i < K; i++)
            friendsList.push_back(allPairs[i]);
    }

    // Output
    println(N, M, K, C);
    for (int i = 0; i < N; i++) {
        println(P[i]);
    }
    for (auto &pr : friendsList) {
        println(pr.first, pr.second);
    }

    return 0;
}
