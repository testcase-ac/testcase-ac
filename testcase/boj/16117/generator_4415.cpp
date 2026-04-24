#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size hyper-parameters: keep total cells ≤ 20
    int N = rnd.next(1, 5);
    int maxM = min(5, 20 / N);
    int M = rnd.next(1, maxM);

    // Value distribution hyper-parameters
    vector<int> maxValChoices = {10, 20, 50, 100, 1000};
    int maxVal = rnd.any(maxValChoices);
    vector<int> tvals = {-2, 0, 2};
    int t = rnd.any(tvals);           // bias: negative for small, positive for large, zero for uniform
    double zeroProb = rnd.next(0.0, 1.0);  // probability of zero entries

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        vector<int> row;
        row.reserve(M);
        for (int j = 0; j < M; j++) {
            if (rnd.next() < zeroProb) {
                row.push_back(0);
            } else {
                // rnd.wnext(maxVal, t) returns [0, maxVal-1], so +1 → [1, maxVal]
                int v = rnd.wnext(maxVal, t) + 1;
                row.push_back(v);
            }
        }
        println(row);
    }

    return 0;
}
