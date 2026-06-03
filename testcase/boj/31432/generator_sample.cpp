#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> digits;

    if (mode == 0) {
        digits.push_back(rnd.next(0, 9));
    } else if (mode == 1) {
        digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    } else if (mode == 2) {
        vector<int> pool = {0, 2, 4, 6, 8};
        int n = rnd.next(1, (int)pool.size());
        shuffle(pool.begin(), pool.end());
        digits.assign(pool.begin(), pool.begin() + n);
    } else if (mode == 3) {
        vector<int> pool = {1, 3, 5, 7, 9};
        int n = rnd.next(1, (int)pool.size());
        shuffle(pool.begin(), pool.end());
        digits.assign(pool.begin(), pool.begin() + n);
    } else if (mode == 4) {
        vector<int> pool = {2, 3, 5, 7};
        int n = rnd.next(1, (int)pool.size());
        shuffle(pool.begin(), pool.end());
        digits.assign(pool.begin(), pool.begin() + n);
    } else {
        int n = rnd.next(1, 10);
        vector<int> pool = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        shuffle(pool.begin(), pool.end());
        digits.assign(pool.begin(), pool.begin() + n);
    }

    sort(digits.begin(), digits.end());

    println((int)digits.size());
    println(digits);

    return 0;
}
