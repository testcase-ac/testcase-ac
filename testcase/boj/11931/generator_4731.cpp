#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter to bias N toward small or large
    int bias = rnd.next(-2, 2);
    int base = rnd.wnext(10, bias); // in [0,9], biased
    int N = base + 1;               // now in [1,10]

    // Choose a value range [minV, maxV] with enough distinct integers
    int minV = rnd.next(-20, 20);
    int maxV = rnd.next(minV, 20);
    if (maxV - minV + 1 < N) {
        maxV = minV + N - 1;
    }

    // Generate N distinct integers in [minV, maxV]
    set<int> vals;
    while ((int)vals.size() < N) {
        vals.insert(rnd.next(minV, maxV));
    }
    vector<int> v(vals.begin(), vals.end());
    shuffle(v.begin(), v.end());

    // Output
    println(N);
    for (int x : v) {
        println(x);
    }
    return 0;
}
