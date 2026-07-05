#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 12);
    } else if (mode == 2) {
        n = rnd.next(13, 40);
    } else if (mode == 3) {
        n = rnd.next(41, 90);
    } else {
        n = rnd.next(91, 123);
    }

    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    if (mode == 0) {
        // Keep the single-disk edge case unchanged.
    } else if (mode == 1) {
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        reverse(a.begin(), a.end());
    } else if (mode == 3) {
        rotate(a.begin(), a.begin() + rnd.next(n), a.end());
    } else {
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);

    return 0;
}
