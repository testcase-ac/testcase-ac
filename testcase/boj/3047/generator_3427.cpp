#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate A < B < C within [1,100]
    int A = rnd.next(1, 90);
    // choose gap distributions to allow small or large gaps
    vector<int> weights = {-3, -1, 0, 1, 3};
    int t1 = rnd.any(weights);
    int maxGap1 = max(1, 100 - A - 1);
    int g1 = max(1, rnd.wnext(maxGap1, t1));
    int B = A + g1;
    int t2 = rnd.any(weights);
    int maxGap2 = max(1, 100 - B);
    int g2 = max(1, rnd.wnext(maxGap2, t2));
    int C = B + g2;

    // Prepare the three values in sorted order
    vector<int> values = {A, B, C};
    // Shuffle first-line input order
    vector<int> idx = {0, 1, 2};
    shuffle(idx.begin(), idx.end());
    println(values[idx[0]], values[idx[1]], values[idx[2]]);

    // Choose a random permutation of "ABC"
    vector<string> perms = {"ABC", "ACB", "BAC", "BCA", "CAB", "CBA"};
    println(rnd.any(perms));

    return 0;
}
