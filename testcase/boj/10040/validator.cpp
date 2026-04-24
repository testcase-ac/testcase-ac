#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // Read A_i
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = inf.readInt(1, 1000, "A_i");
        inf.readEoln();
    }

    // Read B_j
    vector<int> B(M);
    for (int j = 0; j < M; j++) {
        B[j] = inf.readInt(1, 1000, "B_j");
        inf.readEoln();
    }

    // For each judge, there must exist at least one game with cost <= B_j
    int minA = *min_element(A.begin(), A.end());
    for (int j = 0; j < M; j++) {
        ensuref(B[j] >= minA,
                "No valid game for judge %d: B_j=%d is less than all A_i (min A_i=%d)",
                j+1, B[j], minA);
    }

    // Simulate voting: each judge picks the smallest index i (1-based) with A_i <= B_j
    vector<int> cnt(N, 0);
    for (int j = 0; j < M; j++) {
        int vote = -1;
        for (int i = 0; i < N; i++) {
            if (A[i] <= B[j]) {
                vote = i;
                break;
            }
        }
        // By previous check, vote should always be found
        ensuref(vote != -1, "Internal error: judge %d could not find a game", j+1);
        cnt[vote]++;
    }

    // Check that the winner is unique
    int maxCnt = *max_element(cnt.begin(), cnt.end());
    int winners = 0;
    for (int i = 0; i < N; i++) {
        if (cnt[i] == maxCnt) winners++;
    }
    ensuref(winners == 1,
            "There must be exactly one winner, but %d games have %d votes each",
            winners, maxCnt);

    inf.readEof();
    return 0;
}
