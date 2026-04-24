/* generator code */
#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small N
    int N = rnd.next(2, 10);

    vector<int> blocks;

    // With some probability, create a guaranteed solvable instance
    if (rnd.next(100) < 70) {
        // Choose size of one tower
        int k = rnd.next(1, N / 2);
        // Determine a target sum h between k and k*20
        int h = rnd.next(k, k * 20);
        // Build first tower blocks summing to h
        vector<int> tower;
        int rem = h;
        for (int i = 0; i < k - 1; ++i) {
            // leave at least 1 for each remaining block
            int hi = rnd.next(1, rem - (k - i - 1));
            tower.push_back(hi);
            rem -= hi;
        }
        tower.push_back(rem);
        // Add two identical towers
        for (int x : tower) blocks.push_back(x);
        for (int x : tower) blocks.push_back(x);
        // Fill the rest with random small blocks
        for (int i = 2 * k; i < N; ++i) {
            blocks.push_back(rnd.next(1, 20));
        }
    } else {
        // Random instance, may or may not be solvable
        for (int i = 0; i < N; ++i) {
            blocks.push_back(rnd.wnext(50, rnd.next(-3, 3)) + 1);
        }
    }

    // Shuffle to hide structure
    shuffle(blocks.begin(), blocks.end());

    // Output
    println(N);
    for (int i = 0; i < N; ++i) {
        printf("%d%c", blocks[i], i + 1 == N ? '\n' : ' ');
    }

    return 0;
}
