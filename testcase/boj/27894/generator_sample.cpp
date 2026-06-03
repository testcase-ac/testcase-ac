#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

vector<int> identityPermutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    return p;
}

vector<int> randomPermutation(int n) {
    vector<int> p = identityPermutation(n);
    shuffle(p.begin(), p.end());
    return p;
}

vector<int> alternatingPermutation(int n) {
    vector<int> odds;
    vector<int> evens;
    for (int x = 1; x <= n; ++x) {
        if (x % 2 == 1) {
            odds.push_back(x);
        } else {
            evens.push_back(x);
        }
    }

    if (rnd.next(2)) {
        reverse(odds.begin(), odds.end());
    }
    if (rnd.next(2)) {
        reverse(evens.begin(), evens.end());
    }

    vector<int> p;
    int oddIndex = 0;
    int evenIndex = 0;
    bool takeOdd = rnd.next(2);
    while ((int)p.size() < n) {
        if (takeOdd && oddIndex < (int)odds.size()) {
            p.push_back(odds[oddIndex++]);
        } else if (!takeOdd && evenIndex < (int)evens.size()) {
            p.push_back(evens[evenIndex++]);
        } else if (oddIndex < (int)odds.size()) {
            p.push_back(odds[oddIndex++]);
        } else {
            p.push_back(evens[evenIndex++]);
        }
        takeOdd = !takeOdd;
    }
    return p;
}

void applyLocalTripleSorts(vector<int>& p, int steps) {
    int n = (int)p.size();
    for (int step = 0; step < steps; ++step) {
        int left = rnd.next(0, n - 3);
        if (rnd.next(2)) {
            sort(p.begin() + left, p.begin() + left + 3);
        } else {
            sort(p.begin() + left, p.begin() + left + 3, greater<int>());
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 5) {
        n = rnd.next(40, 120);
    } else {
        n = rnd.next(3, 18);
    }

    vector<int> original = randomPermutation(n);
    vector<int> ideal;

    if (mode == 0) {
        ideal = original;
    } else if (mode == 1) {
        ideal = identityPermutation(n);
    } else if (mode == 2) {
        ideal = identityPermutation(n);
        reverse(ideal.begin(), ideal.end());
    } else if (mode == 3) {
        ideal = alternatingPermutation(n);
    } else if (mode == 4) {
        ideal = original;
        applyLocalTripleSorts(ideal, rnd.next(1, 8));
    } else {
        ideal = randomPermutation(n);
        applyLocalTripleSorts(original, rnd.next(0, 20));
    }

    println(n);
    println(original);
    println(ideal);

    return 0;
}
