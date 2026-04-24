#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N = 5;
    const int M = 4;
    vector<int> sums(N, 0);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int x = inf.readInt(1, 5, 
                (string("score_") + to_string(i+1) + "_" + to_string(j+1)).c_str());
            sums[i] += x;
            if (j < M-1) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    // Check for unique maximum sum
    int maxSum = sums[0];
    for (int i = 1; i < N; i++) {
        if (sums[i] > maxSum) maxSum = sums[i];
    }
    int cntMax = 0, who = -1;
    for (int i = 0; i < N; i++) {
        if (sums[i] == maxSum) {
            cntMax++;
            who = i;
        }
    }
    ensuref(cntMax == 1,
        "There must be a unique winner, but max score %d occurs %d times", maxSum, cntMax);

    inf.readEof();
    return 0;
}
