#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose N even between 4 and 10
    vector<int> choices = {4, 6, 8, 10};
    int N = rnd.any(choices);

    // Hyper-parameter: decide small or large value range
    bool smallRange = rnd.next(0, 1) == 0;
    int maxVal = smallRange ? rnd.next(10, 20) : rnd.next(50, 100);

    // Hyper-parameter: probability to make S symmetric
    double symProb = rnd.next();

    // Build S matrix
    vector<vector<int>> S(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        S[i][i] = 0;
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (rnd.next() < symProb) {
                // make the pair symmetric
                int v = rnd.next(1, maxVal);
                S[i][j] = S[j][i] = v;
            } else {
                S[i][j] = rnd.next(1, maxVal);
                S[j][i] = rnd.next(1, maxVal);
            }
        }
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        println(S[i]);
    }
    return 0;
}
