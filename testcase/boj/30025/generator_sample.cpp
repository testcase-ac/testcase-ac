#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> sortedPrefixSubset(int n, bool forceZero) {
    vector<int> digits;
    for (int d = 0; d <= 9; ++d) {
        if (d == 0 && !forceZero) continue;
        digits.push_back(d);
    }
    shuffle(digits.begin(), digits.end());

    vector<int> picked;
    if (forceZero) {
        picked.push_back(0);
        digits.erase(find(digits.begin(), digits.end(), 0));
    }
    while ((int)picked.size() < n) {
        picked.push_back(digits.back());
        digits.pop_back();
    }
    sort(picked.begin(), picked.end());
    return picked;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n;
    int m;
    int k;
    vector<int> digits;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 8);
        k = rnd.any(vector<int>{2, 3, 5, 7, 10, 11, 37, 101});
        digits = {rnd.next(0, 9)};
    } else if (mode == 1) {
        n = rnd.next(2, 6);
        m = 1;
        k = rnd.next(2, 40);
        digits = sortedPrefixSubset(n, rnd.next(2) == 0);
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        m = rnd.next(2, 12);
        k = rnd.any(vector<int>{2, 4, 5, 8, 10, 20, 25, 40, 100});
        digits = sortedPrefixSubset(n, true);
    } else if (mode == 3) {
        n = 10;
        m = rnd.next(1, 20);
        k = rnd.next(2, 1000);
        digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    } else if (mode == 4) {
        n = rnd.next(2, 5);
        m = rnd.next(20, 100);
        k = rnd.any(vector<int>{2, 3, 7, 9, 11, 13, 37, 101, 999, 1000});
        digits = sortedPrefixSubset(n, rnd.next(2) == 0);
    } else if (mode == 5) {
        n = rnd.next(2, 7);
        m = rnd.next(2, 30);
        k = rnd.next(900, 1000);
        digits = sortedPrefixSubset(n, true);
    } else if (mode == 6) {
        n = rnd.next(2, 9);
        m = rnd.next(2, 25);
        k = rnd.next(2, 120);
        digits = sortedPrefixSubset(n, false);
    } else {
        n = rnd.next(1, 10);
        m = rnd.next(1, 100);
        k = rnd.next(2, 1000);
        digits = sortedPrefixSubset(n, rnd.next(3) != 0);
    }

    println(n, m, k);
    println(digits);

    return 0;
}
