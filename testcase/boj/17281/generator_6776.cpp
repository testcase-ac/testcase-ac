#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Diverse choice of innings count, keeping manual verification manageable
    vector<int> possibleN = {2, 3, 4, 5, 10, 15, 20};
    int N = rnd.any(possibleN);
    println(N);

    // Generate each inning's results with a weighted randomness hyper-parameter
    for (int i = 0; i < N; i++) {
        // t controls distribution bias: negative tends to more outs, positive to more hits
        int t = rnd.next(-2, 2);
        vector<int> row(9);
        for (int j = 0; j < 9; j++) {
            // Values in [0..4], with bias controlled by t
            row[j] = rnd.wnext(5, t);
        }
        // Ensure at least one out (0) per inning
        bool hasOut = false;
        for (int x : row) if (x == 0) { hasOut = true; break; }
        if (!hasOut) {
            int idx = rnd.next(0, 8);
            row[idx] = 0;
        }
        println(row);
    }

    return 0;
}
