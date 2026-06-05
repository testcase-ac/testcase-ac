#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

vector<int> randomArray(int n, int lo, int hi) {
    vector<int> v(n);
    for (int& x : v) {
        x = rnd.next(lo, hi);
    }
    return v;
}

void adjustSum(vector<int>& v, int target) {
    int sum = accumulate(v.begin(), v.end(), 0);
    while (sum < target) {
        vector<int> can;
        for (int i = 0; i < (int)v.size(); ++i) {
            if (v[i] < 100) {
                can.push_back(i);
            }
        }
        int idx = rnd.any(can);
        int add = rnd.next(1, min(100 - v[idx], target - sum));
        v[idx] += add;
        sum += add;
    }
    while (sum > target) {
        vector<int> can;
        for (int i = 0; i < (int)v.size(); ++i) {
            if (v[i] > 1) {
                can.push_back(i);
            }
        }
        int idx = rnd.any(can);
        int sub = rnd.next(1, min(v[idx] - 1, sum - target));
        v[idx] -= sub;
        sum -= sub;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    vector<int> a, b;

    if (mode == 0) {
        n = rnd.next(1, 6);
        a = randomArray(n, 1, 12);
        b = randomArray(n, 1, 12);
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        a = randomArray(n, 1, 100);
        b = a;
        shuffle(b.begin(), b.end());
    } else if (mode == 2) {
        n = rnd.next(3, 25);
        int target = rnd.next(n, 100 * n);
        a = randomArray(n, 1, 100);
        b = randomArray(n, 1, 100);
        adjustSum(a, target);
        adjustSum(b, target);
    } else if (mode == 3) {
        n = rnd.next(5, 40);
        a = randomArray(n, 1, 5);
        b = randomArray(n, 80, 100);
    } else if (mode == 4) {
        n = rnd.next(5, 40);
        a = randomArray(n, 80, 100);
        b = randomArray(n, 1, 5);
    } else {
        n = rnd.next(20, 80);
        a = randomArray(n, 1, 100);
        b = randomArray(n, 1, 100);
        for (int i = 0; i < n; i += rnd.next(3, 8)) {
            a[i] = rnd.any(vector<int>{1, 100});
        }
        for (int i = 1; i < n; i += rnd.next(3, 8)) {
            b[i] = rnd.any(vector<int>{1, 100});
        }
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
