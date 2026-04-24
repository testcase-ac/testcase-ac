#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of rows
    int N = rnd.next(1, 10);
    // Distribution type: 0 = uniform, 1 = high-biased, 2 = low-biased
    int distType = rnd.next(0, 2);
    // Bias strength for weighted sampling
    int bias = rnd.next(1, 4);

    println(N);
    for (int i = 0; i < N; i++) {
        vector<int> row(3);
        // Generate three values according to the chosen distribution
        for (int j = 0; j < 3; j++) {
            if (distType == 0) {
                row[j] = rnd.next(0, 9);
            } else if (distType == 1) {
                // high-biased: take max of (bias+1) samples
                row[j] = rnd.wnext(10, bias);
            } else {
                // low-biased: take min of (bias+1) samples
                row[j] = rnd.wnext(10, -bias);
            }
        }
        // Per-row pattern: 0 = random, 1 = ascending, 2 = descending
        int pattern = rnd.next(0, 2);
        if (pattern == 1) {
            sort(row.begin(), row.end());
        } else if (pattern == 2) {
            sort(row.begin(), row.end(), greater<int>());
        }
        println(row);
    }

    return 0;
}
