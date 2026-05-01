#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of slices
    int S = rnd.next(1, 12);
    // Number of operations, up to ~3*S
    int Q = rnd.next(1, max(1, S * 3));
    // Hyper-parameters for query probability
    vector<double> queryProbs = {0.2, 0.3, 0.4, 0.5, 0.6, 0.7};
    double pQuery = rnd.any(queryProbs);
    // Hyper-parameters for update locality
    int numHot = rnd.next(1, min(3, S));
    vector<int> idxs(S);
    for (int i = 0; i < S; i++) idxs[i] = i + 1;
    shuffle(idxs.begin(), idxs.end());
    vector<int> hot(idxs.begin(), idxs.begin() + numHot);
    double pHot = rnd.next(0.5, 0.9); // bias to update hot slices

    // Output header
    println(S, Q);

    bool sawQuery = false;
    for (int i = 1; i <= Q; i++) {
        bool forceQuery = (i == Q && !sawQuery);
        bool doQuery = forceQuery || (rnd.next() < pQuery);
        if (doQuery) {
            println(2);
            sawQuery = true;
        } else {
            // Update operation
            int a;
            if (rnd.next() < pHot) {
                a = rnd.any(hot);
            } else {
                a = rnd.next(1, S);
            }
            // Value magnitude hyper-parameter
            int b;
            double pSmall = 0.7;
            if (rnd.next() < pSmall) {
                b = rnd.next(1, 10);
            } else {
                b = rnd.next(100, 1000);
            }
            if (rnd.next() < 0.5) b = -b;
            // Occasionally zero
            if (rnd.next() < 0.05) b = 0;
            printf("1 %d %d\n", a, b);
        }
    }
    return 0;
}
