#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int t = rnd.next(5, 12);
    // Some special edge-case values to expose rounding boundaries
    vector<int> special = {
        0, 1, 4, 5, 9, 10, 11, 14, 15,
        49, 50, 51, 99, 100, 450, 5000,
        50000, 500000, 99999999
    };
    // Shuffle specials and pick a random subset
    shuffle(special.begin(), special.end());
    int sp = rnd.next(3, min((int)special.size(), t - 1));
    vector<int> xs;
    for (int i = 0; i < sp; i++) {
        xs.push_back(special[i]);
    }
    // Fill the rest with random values
    for (int i = 0; i < t - sp; i++) {
        xs.push_back(rnd.next(0, 99999999));
    }
    // Final shuffle to randomize order
    shuffle(xs.begin(), xs.end());
    // Output
    println(t);
    for (int x : xs) {
        println(x);
    }
    return 0;
}
