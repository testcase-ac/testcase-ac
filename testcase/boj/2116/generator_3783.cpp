#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of dice, biased towards smaller values
    int N = rnd.wnext(10, -1) + 1;  // [1..10]
    // Number of distinct base types
    int maxTypes = min(N, 4);
    int typesCount = rnd.next(1, maxTypes);
    // Prepare base face order
    vector<int> base = {1, 2, 3, 4, 5, 6};
    vector<vector<int>> types(typesCount);
    for (int t = 0; t < typesCount; t++) {
        types[t] = base;
        shuffle(types[t].begin(), types[t].end());
    }
    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        // With some probability generate a fresh permutation
        if (rnd.next() < 0.3) {
            vector<int> v = base;
            shuffle(v.begin(), v.end());
            println(v);
        } else {
            println(types[rnd.next(0, typesCount - 1)]);
        }
    }
    return 0;
}
