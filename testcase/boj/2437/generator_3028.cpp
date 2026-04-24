#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small number of weights
    int N = rnd.next(1, 10);

    // Hyper-parameters for weight distribution
    vector<int> his = {1, 5, 20, 100, 1000000};
    vector<int> ts  = {-2, -1, 0, 1, 2};
    int hi = rnd.any(his);
    int t  = rnd.any(ts);

    // Generate weights using weighted randomness
    vector<int> w;
    for (int i = 0; i < N; i++) {
        // rnd.wnext(hi, t) yields [0..hi-1] with bias; +1 => [1..hi]
        w.push_back(rnd.wnext(hi, t) + 1);
    }

    // Occasionally sort to test sorted-input assumptions
    if (rnd.next(0, 1) == 0) {
        sort(w.begin(), w.end());
    } else {
        shuffle(w.begin(), w.end());
    }

    // Output
    println(N);
    println(w);

    return 0;
}
