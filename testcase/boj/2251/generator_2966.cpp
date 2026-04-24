#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter: choose an upper bound for small capacities (5 to 10)
    int hi = rnd.next(5, 10);

    // Generate three capacities in [1..hi]
    vector<int> v(3);
    for (int i = 0; i < 3; i++) {
        v[i] = rnd.next(1, hi);
    }

    // Hyperparameter: sometimes sort ascending, sometimes descending, sometimes leave random
    double sp = rnd.next();
    if (sp < 0.3) {
        sort(v.begin(), v.end());
    } else if (sp < 0.6) {
        sort(v.begin(), v.end(), greater<int>());
    }
    // else leave in generated random order

    // Hyperparameter: occasionally make two capacities equal
    if (rnd.next() < 0.3) {
        vector<pair<int,int>> pairs = {{0,1}, {0,2}, {1,2}};
        auto choice = rnd.any(pairs);
        v[choice.second] = v[choice.first];
    }

    // Output A, B, C on one line
    println(v);

    return 0;
}
