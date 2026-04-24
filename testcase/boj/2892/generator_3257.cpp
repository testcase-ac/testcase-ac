#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of encrypted bytes
    int N = rnd.next(1, 10);
    println(N);

    // Choose a distribution type for diversity
    // 0 = uniform, 1 = bias towards small, 2 = bias towards large
    int dist = rnd.next(0, 2);

    vector<int> bytes;
    bytes.reserve(N);
    for (int i = 0; i < N; i++) {
        int x;
        if (dist == 0) {
            x = rnd.next(0, 127);
        } else if (dist == 1) {
            // bias towards small values
            x = rnd.wnext(128, -1); 
        } else {
            // bias towards large values
            x = rnd.wnext(128, 1);
        }
        bytes.push_back(x);
    }

    // Shuffle to avoid ordered patterns
    shuffle(bytes.begin(), bytes.end());

    // Output as hex integers without prefix
    for (int i = 0; i < N; i++) {
        if (i) printf(" ");
        printf("%X", bytes[i]);
    }
    printf("\n");

    return 0;
}
