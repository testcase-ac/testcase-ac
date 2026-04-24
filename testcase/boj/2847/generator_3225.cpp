#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of levels
    int N = rnd.next(1, 10);

    // Hyper-parameter: maximum possible score (ensures Ai >= i)
    int maxScore = rnd.next(N, 20);

    // Hyper-parameter for uneven distribution in score generation
    vector<int> weights = { -2, -1, 0, 1, 2 };
    int t = rnd.any(weights);

    // Generate scores ensuring Ai >= i so a solution always exists
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        int lo = i + 1;
        int range = maxScore - lo + 1;
        if (range <= 1) {
            A[i] = lo;
        } else {
            int delta = rnd.wnext(range, t);  // weighted toward small or large
            A[i] = lo + delta;
        }
    }

    // Output
    println(N);
    for (int x : A) println(x);

    return 0;
}
