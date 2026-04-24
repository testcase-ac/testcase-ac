#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small N, A, D for hand-checkable cases
    int N = rnd.next(1, 10);
    int A = rnd.next(1, 20);
    int D = rnd.next(1, 10);

    // Bias to favor short or long embedded AP
    int bias = rnd.any(vector<int>{-1, 0, 1});
    int len = rnd.wnext(N, bias);
    if (len < 1) len = 1;

    // Pick 'len' distinct positions to embed the AP
    vector<int> idx(N);
    iota(idx.begin(), idx.end(), 0);
    shuffle(idx.begin(), idx.end());
    idx.resize(len);
    sort(idx.begin(), idx.end());

    // Build sequence with random noise
    vector<int> seq(N);
    for (int i = 0; i < N; i++) {
        // Noise in [1..100] (within problem bounds)
        seq[i] = rnd.next(1, 100);
    }
    // Embed the AP terms A, A+D, ..., A+(len-1)*D
    for (int i = 0; i < len; i++) {
        seq[idx[i]] = A + i * D;
    }

    // Output in required format
    println(N, A, D);
    println(seq);

    return 0;
}
