#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of items
    int N = rnd.next(1, 10);

    // Maximum position value
    int maxPos = rnd.next(5, 30);

    // Mode for generating destination positions
    int mode = rnd.next(0, 2);
    vector<int> dest;
    if (mode == 0) {
        // Uniform random positions
        for (int i = 0; i < N; i++)
            dest.push_back(rnd.next(1, maxPos));
    } else if (mode == 1) {
        // Cluster around a random center
        int center = rnd.next(1, maxPos);
        for (int i = 0; i < N; i++) {
            int offset = rnd.next(0, 5) - 2;  // [-2,2]
            int v = center + offset;
            if (v < 1) v = 1;
            if (v > maxPos) v = maxPos;
            dest.push_back(v);
        }
    } else {
        // Choose from a small set of values
        int k = rnd.next(1, min(N, 5));
        vector<int> choices;
        for (int i = 0; i < k; i++)
            choices.push_back(rnd.next(1, maxPos));
        for (int i = 0; i < N; i++)
            dest.push_back(rnd.any(choices));
    }

    // Randomize order
    shuffle(dest.begin(), dest.end());

    // Truck and helicopter costs
    int C_t = rnd.next(1, 20);
    int C_h = rnd.next(1, 200);

    // Output the test case
    println(N);
    println(dest);
    println(C_t, C_h);

    return 0;
}
