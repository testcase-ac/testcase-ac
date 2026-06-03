#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> randomCase(int n) {
    int lo = rnd.next(1, 1000000);
    int hi = rnd.next(lo, 1000000);
    vector<int> d(n);
    for (int& x : d) x = rnd.next(lo, hi);
    return d;
}

vector<int> monotoneCase(int n, bool increasing) {
    vector<int> d(n);
    int cur = rnd.next(1, 30);
    for (int i = 0; i < n; ++i) {
        cur += rnd.next(0, 8);
        d[i] = cur;
    }
    if (!increasing) reverse(d.begin(), d.end());
    return d;
}

vector<int> valleyCase(int n) {
    vector<int> d(n);
    int mid = n / 2;
    int base = rnd.next(1, 20);
    for (int i = 0; i < n; ++i) {
        int dist = abs(i - mid);
        d[i] = base + dist * rnd.next(2, 9) + rnd.next(0, 3);
    }
    return d;
}

vector<int> peakCase(int n) {
    vector<int> d = valleyCase(n);
    int mx = *max_element(d.begin(), d.end());
    for (int& x : d) x = mx - x + 1;
    return d;
}

vector<int> plateauCase(int n) {
    vector<int> values;
    int kinds = rnd.next(1, min(5, n));
    for (int i = 0; i < kinds; ++i) values.push_back(rnd.next(1, 40));

    vector<int> d(n);
    for (int& x : d) x = rnd.any(values);
    return d;
}

vector<int> boundaryCase(int n) {
    vector<int> d(n);
    for (int i = 0; i < n; ++i) {
        if (rnd.next(3) == 0) d[i] = 1;
        else if (rnd.next(3) == 0) d[i] = 1000000;
        else d[i] = rnd.next(2, 999999);
    }
    return d;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n = rnd.next(2, 30);
        int mode = rnd.next(6);

        vector<int> d;
        if (mode == 0) d = randomCase(n);
        else if (mode == 1) d = monotoneCase(n, rnd.next(2) == 0);
        else if (mode == 2) d = valleyCase(n);
        else if (mode == 3) d = peakCase(n);
        else if (mode == 4) d = plateauCase(n);
        else d = boundaryCase(n);

        println(n);
        println(d);
    }

    return 0;
}
