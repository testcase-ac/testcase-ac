#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> randomCase(int n, int low, int high) {
    vector<int> a(n);
    for (int& x : a) {
        x = rnd.next(low, high);
    }
    return a;
}

vector<int> alternatingCase(int n) {
    vector<int> a(n);
    int positive = rnd.next(1, 10000);
    int negative = -rnd.next(1, 10000);
    for (int i = 0; i < n; ++i) {
        a[i] = (i % 2 == 0 ? positive : negative);
    }
    if (rnd.next(2)) {
        reverse(a.begin(), a.end());
    }
    return a;
}

vector<int> valleyCase(int n) {
    vector<int> a(n);
    int left = rnd.next(0, n - 1);
    int right = rnd.next(left, n - 1);
    for (int i = 0; i < n; ++i) {
        if (left <= i && i <= right) {
            a[i] = rnd.next(1, 10000);
        } else {
            a[i] = -rnd.next(1, 10000);
        }
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCases = rnd.next(2, 8);
    for (int tc = 0; tc < testCases; ++tc) {
        int mode = rnd.next(5);
        int n;
        vector<int> a;

        if (mode == 0) {
            n = rnd.next(1, 4);
            a = randomCase(n, -10000, 10000);
        } else if (mode == 1) {
            n = rnd.next(3, 20);
            a = randomCase(n, -20, 20);
        } else if (mode == 2) {
            n = rnd.next(2, 18);
            a = alternatingCase(n);
        } else if (mode == 3) {
            n = rnd.next(3, 24);
            a = valleyCase(n);
        } else {
            n = rnd.next(1, 25);
            int value = rnd.next(2) ? rnd.next(1, 10000) : -rnd.next(1, 10000);
            a.assign(n, value);
        }

        println(n);
        for (int x : a) {
            println(x);
        }
    }

    println(0);
    return 0;
}
