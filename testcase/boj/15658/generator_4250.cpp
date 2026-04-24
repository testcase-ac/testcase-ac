#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter for sequence length bias: small, medium, large
    int tN = rnd.any(vector<int>{-1, 0, 1});
    int N;
    if (tN == -1)      N = rnd.next(2, 6);
    else if (tN == 1)  N = rnd.next(7, 11);
    else               N = rnd.next(2, 11);

    // Hyperparameter for element size bias: small, uniform, large
    int tAi = rnd.any(vector<int>{-1, 0, 1});
    int ai_lo, ai_hi;
    if (tAi == -1)      { ai_lo = 1; ai_hi = 3; }
    else if (tAi == 1)  { ai_lo = 4; ai_hi = 6; }
    else                { ai_lo = 1; ai_hi = 6; }

    // Generate the sequence A
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(ai_lo, ai_hi);
    }

    // Hyperparameter for total operator count bias: low, uniform, high
    int sBias = rnd.any(vector<int>{-1, 0, 1});
    int sumLo = N - 1;
    int sumHi = 4 * N;
    int sumOps;
    if (sBias == 0) {
        sumOps = rnd.next(sumLo, sumHi);
    } else {
        // biased sampling in [0 .. sumHi-sumLo], then shift
        sumOps = rnd.wnext(sumHi - sumLo + 1, sBias) + sumLo;
    }

    // Hyperparameter to bias one operator type
    double biasProb = rnd.next(0.3, 0.7);
    int typeBias = rnd.next(0, 3);

    // Build a multiset of available operators
    vector<int> opsList;
    opsList.reserve(sumOps);
    for (int i = 0; i < sumOps; i++) {
        if (rnd.next() < biasProb) 
            opsList.push_back(typeBias);
        else 
            opsList.push_back(rnd.next(0, 3));
    }
    shuffle(opsList.begin(), opsList.end());

    // Count operators: 0:+, 1:-, 2:×, 3:÷
    vector<int> cnt(4, 0);
    for (int x : opsList) cnt[x]++;

    // Output in the required format
    println(N);
    println(A);
    println(cnt[0], cnt[1], cnt[2], cnt[3]);

    return 0;
}
