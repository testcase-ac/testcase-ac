#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> candidates;

    int mode = rnd.next(0, 6);
    if (mode == 0) {
        candidates = {2, 3, 4, 5, 6, 7, 8, 9, 10};
    } else if (mode == 1) {
        int base = rnd.next(2, 60);
        candidates = {base, base + 1, max(2, base - 1)};
    } else if (mode == 2) {
        int k = rnd.next(2, 447);
        candidates = {k * k, k * k + 1, k * k - 1};
    } else if (mode == 3) {
        int k = rnd.next(1, 1000);
        candidates = {2 * k, 2 * k + 1};
    } else if (mode == 4) {
        int offset = rnd.next(0, 30);
        candidates = {200000 - offset};
    } else if (mode == 5) {
        int k = rnd.next(1, 100000);
        candidates = {2 * k};
    } else {
        int k = rnd.next(1, 99999);
        candidates = {2 * k + 1};
    }

    vector<int> valid;
    for (int n : candidates) {
        if (2 <= n && n <= 200000) {
            valid.push_back(n);
        }
    }
    if (valid.empty()) {
        valid.push_back(rnd.next(2, 200000));
    }

    println(rnd.any(valid));
    return 0;
}
