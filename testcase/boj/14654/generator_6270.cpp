#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter: choose N from diverse ranges including edge
    vector<pair<int,int>> ranges = {{1,1}, {2,10}, {11,50}, {51,300}};
    auto rng = rnd.any(ranges);
    int N = rnd.next(rng.first, rng.second);

    // Hyperparameter: probability of draw in rounds >1
    vector<double> draw_probs = {0.0, 0.1, 0.3, 0.5};
    double p_draw = rnd.any(draw_probs);

    vector<int> A(N), B(N);
    auto win = [&](int x) { return x % 3 + 1; };

    // Round 1: no draws
    if (rnd.next(0,1) == 0) {
        // A wins
        B[0] = rnd.next(1,3);
        A[0] = win(B[0]);
    } else {
        // B wins
        A[0] = rnd.next(1,3);
        B[0] = win(A[0]);
    }

    // Subsequent rounds
    for (int i = 1; i < N; i++) {
        double p = rnd.next(0.0, 1.0);
        if (p < p_draw) {
            // draw
            A[i] = rnd.next(1,3);
            B[i] = A[i];
        } else {
            // win by A or B
            if (rnd.next(0.0, 1.0) < 0.5) {
                // A wins
                B[i] = rnd.next(1,3);
                A[i] = win(B[i]);
            } else {
                // B wins
                A[i] = rnd.next(1,3);
                B[i] = win(A[i]);
            }
        }
    }

    // Output
    println(N);
    println(A);
    println(B);

    return 0;
}
