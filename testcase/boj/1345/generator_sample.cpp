#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

constexpr int kMinValue = -1000000;
constexpr int kMaxValue = 1000000;

int clampValue(long long x) {
    return static_cast<int>(max<long long>(kMinValue, min<long long>(kMaxValue, x)));
}

vector<int> makeArithmeticFloors(int n, int a0) {
    int numerator = rnd.next(0, 40);
    int denominator = rnd.next(1, 12);
    vector<int> s;
    s.reserve(n);
    for (int i = 1; i <= n; ++i) {
        long long value = static_cast<long long>(a0) + numerator * 1LL * i / denominator;
        s.push_back(clampValue(value));
    }
    return s;
}

vector<int> makePlateaus(int n, int start) {
    vector<int> s;
    s.reserve(n);
    int cur = start;
    for (int i = 0; i < n; ++i) {
        if (i > 0 && rnd.next(100) < 35) {
            cur = clampValue(static_cast<long long>(cur) + rnd.next(1, 4));
        }
        s.push_back(cur);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int a0 = rnd.next(-20, 20);
    vector<int> s;

    if (mode == 0) {
        n = 0;
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        a0 = rnd.next(-10, 10);
        s = makeArithmeticFloors(n, a0);
    } else if (mode == 2) {
        n = rnd.next(1, 18);
        int start = rnd.next(-15, 15);
        a0 = rnd.next(start - 5, start + 5);
        s = makePlateaus(n, start);
    } else if (mode == 3) {
        n = rnd.next(1, 50);
        a0 = rnd.any(vector<int>{kMinValue, kMinValue + 1, kMaxValue - 1, kMaxValue});
        int start = rnd.next(kMinValue, kMinValue + 20);
        if (rnd.next(2) == 1) start = rnd.next(kMaxValue - 20, kMaxValue);
        s = makePlateaus(n, start);
    } else if (mode == 4) {
        n = rnd.next(1, 10);
        a0 = rnd.next(-5, 20);
        int start = rnd.next(-20, min(a0 - 1, 10));
        s = makePlateaus(n, start);
    } else {
        n = rnd.next(2, 16);
        a0 = rnd.next(-20, 20);
        int start = rnd.next(max(kMinValue, a0), min(kMaxValue - 30, a0 + 20));
        s.push_back(start);
        for (int i = 1; i < n; ++i) {
            int jump = rnd.next(0, 18);
            if (i == n - 1 && rnd.next(2) == 1) jump += rnd.next(20, 80);
            s.push_back(clampValue(static_cast<long long>(s.back()) + jump));
        }
    }

    println(n, a0);
    if (n > 0) {
        println(s);
    }

    return 0;
}
