#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Start from the sorted sequence
    vector<int> p = {1, 2, 3, 4, 5};

    // Hyper-parameter mode: single swap, full reverse, or random shuffle
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        // Single swap of two distinct positions
        int i = rnd.next(0, 4);
        int j = rnd.next(0, 4);
        while (j == i) j = rnd.next(0, 4);
        swap(p[i], p[j]);
    } else if (mode == 1) {
        // Full reverse -> maximally inverted
        reverse(p.begin(), p.end());
    } else {
        // Fully random shuffle
        shuffle(p.begin(), p.end());
    }

    // Guarantee it's not already sorted
    if (is_sorted(p.begin(), p.end())) {
        swap(p[3], p[4]);
    }

    // Output the permutation on one line
    println(p);

    return 0;
}
