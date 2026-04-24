#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a small number of trees
    int N = rnd.next(2, 10);
    // Probability to duplicate a previous coordinate
    double dupProb = rnd.next(0.0, 1.0);

    vector<int> X;
    X.reserve(N);
    for (int i = 0; i < N; i++) {
        int x;
        if (i > 0 && rnd.next() < dupProb) {
            // duplicate a previous coordinate
            x = rnd.any(X);
        } else {
            // sometimes small, sometimes large
            if (rnd.next() < 0.5)
                x = rnd.next(0, 100);
            else
                x = rnd.next(0, 200000);
        }
        X.push_back(x);
    }

    // Output
    println(N);
    for (int v : X)
        println(v);

    return 0;
}
