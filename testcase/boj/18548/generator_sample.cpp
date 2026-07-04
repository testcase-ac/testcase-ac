#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

vector<int> identityPermutation(int n) {
    vector<int> values(n);
    iota(values.begin(), values.end(), 1);
    return values;
}

void applySparseSwaps(vector<int>& values, int swaps) {
    int n = (int)values.size();
    for (int i = 0; i < swaps; ++i) {
        int a = rnd.next(0, n - 1);
        int b = rnd.next(0, n - 1);
        swap(values[a], values[b]);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(2, 40);
    } else if (mode == 2) {
        n = rnd.next(10, 80);
    } else if (mode == 3) {
        n = rnd.next(2, 120);
    } else if (mode == 4) {
        n = rnd.next(100, 500);
    } else {
        n = rnd.next(1, 500);
    }

    vector<int> permutation = identityPermutation(n);

    if (mode == 1) {
        reverse(permutation.begin(), permutation.end());
    } else if (mode == 2) {
        int shift = rnd.next(0, n - 1);
        rotate(permutation.begin(), permutation.begin() + shift, permutation.end());
    } else if (mode == 3) {
        applySparseSwaps(permutation, rnd.next(1, max(1, n / 8)));
    } else if (mode == 4) {
        shuffle(permutation.begin(), permutation.end());
    } else if (mode == 5) {
        shuffle(permutation.begin(), permutation.end());
        applySparseSwaps(permutation, rnd.next(0, max(1, n / 4)));
    }

    println(n);
    println(permutation);
    return 0;
}
