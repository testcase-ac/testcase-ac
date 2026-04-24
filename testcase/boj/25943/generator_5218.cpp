#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small number of stones
    int n = rnd.next(2, 10);

    // Hyper-parameter 1: choose a maximum stone weight
    vector<int> possibleMax = {1, 5, 10, 20, 50, 100};
    int Wmax = rnd.any(possibleMax);

    // Hyper-parameter 2: skew parameter for rnd.wnext
    vector<int> skews = {-2, -1, 0, 1, 2};
    int skew = rnd.any(skews);

    // Generate stone weights w[i] in [1..Wmax] with the chosen skew
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        int x = rnd.wnext(Wmax, skew); // in [0..Wmax-1]
        w[i] = x + 1;
    }

    // Hyper-parameter 3: ordering pattern
    int mode = rnd.next(0, 2);
    if (mode == 1) {
        sort(w.begin(), w.end());  // increasing
    } else if (mode == 2) {
        sort(w.begin(), w.end(), greater<int>()); // decreasing
    }

    // Occasionally shuffle to break full order
    if (rnd.next(0, 1) == 0) {
        shuffle(w.begin(), w.end());
    }

    // Output
    println(n);
    println(w);

    return 0;
}
