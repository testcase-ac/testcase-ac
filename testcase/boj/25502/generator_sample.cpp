#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

constexpr long long MAX_A = 1000000000000000000LL;

long long mulCap(long long a, long long b) {
    __int128 product = static_cast<__int128>(a) * b;
    return product > MAX_A ? MAX_A + 1 : static_cast<long long>(product);
}

long long randomLong(long long lo, long long hi) {
    __int128 raw = 0;
    for (int i = 0; i < 5; ++i) {
        raw = raw * 10000 + rnd.next(0, 9999);
    }
    return lo + static_cast<long long>(raw % (hi - lo + 1));
}

long long randomSmall(long long lo, long long hi) {
    return randomLong(lo, hi);
}

vector<long long> makeArithmetic(int n, long long first, long long diff) {
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = first + diff * i;
    }
    return a;
}

vector<long long> makeGeometric(int n, long long first, long long ratio) {
    vector<long long> a(n);
    a[0] = first;
    for (int i = 1; i < n; ++i) {
        a[i] = a[i - 1] * ratio;
    }
    return a;
}

long long randomValue() {
    int mode = rnd.next(5);
    if (mode == 0) {
        return randomSmall(1, 20);
    }
    if (mode == 1) {
        return randomSmall(1, 1000000);
    }
    if (mode == 2) {
        return MAX_A - randomSmall(0, 100);
    }
    return randomLong(1, MAX_A);
}

void appendArithmeticUpdate(vector<pair<int, long long>>& queries, const vector<long long>& a) {
    int n = static_cast<int>(a.size());
    long long diff = a[1] - a[0];
    int idx = rnd.next(0, n - 1);
    __int128 expected = static_cast<__int128>(a[0]) + static_cast<__int128>(diff) * idx;
    if (1 <= expected && expected <= MAX_A) {
        queries.push_back({idx + 1, static_cast<long long>(expected)});
    } else {
        queries.push_back({idx + 1, randomValue()});
    }
}

void appendGeometricUpdate(vector<pair<int, long long>>& queries, const vector<long long>& a) {
    int n = static_cast<int>(a.size());
    if (a[0] == 0 || a[1] % a[0] != 0) {
        queries.push_back({rnd.next(1, n), randomValue()});
        return;
    }

    long long ratio = a[1] / a[0];
    if (ratio <= 0) {
        queries.push_back({rnd.next(1, n), randomValue()});
        return;
    }
    int idx = rnd.next(0, n - 1);
    long long value = a[0];
    for (int i = 0; i < idx; ++i) {
        value = mulCap(value, ratio);
    }
    if (1 <= value && value <= MAX_A) {
        queries.push_back({idx + 1, value});
    } else {
        queries.push_back({idx + 1, randomValue()});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(3, 12);
    int m = rnd.next(1, 14);
    vector<long long> a;

    if (mode == 0) {
        long long diff = randomSmall(1, 20);
        long long first = randomSmall(1, min(1000LL, MAX_A - diff * (n - 1)));
        a = makeArithmetic(n, first, diff);
    } else if (mode == 1) {
        long long ratio = randomSmall(1, 6);
        long long first = randomSmall(1, 12);
        a = makeGeometric(n, first, ratio);
    } else if (mode == 2) {
        long long diff = randomSmall(1, 100);
        long long first = randomSmall(1, min(1000000LL, MAX_A - diff * (n - 1)));
        a = makeArithmetic(n, first, diff);
        int broken = rnd.next(0, n - 1);
        a[broken] = randomValue();
    } else if (mode == 3) {
        long long ratio = randomSmall(2, 5);
        long long first = randomSmall(1, 10);
        while (true) {
            a = makeGeometric(n, first, ratio);
            if (a.back() <= MAX_A) {
                break;
            }
            --n;
        }
        n = max(n, 3);
        int broken = rnd.next(0, n - 1);
        a[broken] = randomValue();
    } else if (mode == 4) {
        n = rnd.next(3, 6);
        a.assign(n, MAX_A);
        for (int i = 0; i < n; ++i) {
            a[i] -= randomSmall(0, 100);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            a.push_back(randomValue());
        }
    }

    vector<long long> initial = a;
    vector<pair<int, long long>> queries;
    for (int q = 0; q < m; ++q) {
        int updateMode = rnd.next(5);
        if (updateMode == 0 && n >= 3) {
            appendArithmeticUpdate(queries, a);
        } else if (updateMode == 1 && n >= 3) {
            appendGeometricUpdate(queries, a);
        } else {
            int idx;
            if (updateMode == 2) {
                idx = rnd.next(0, 1) == 0 ? 1 : n;
            } else {
                idx = rnd.next(1, n);
            }
            queries.push_back({idx, randomValue()});
        }
        a[queries.back().first - 1] = queries.back().second;
    }

    println(n, static_cast<int>(queries.size()));
    println(initial);
    for (auto [idx, value] : queries) {
        println(idx, value);
    }

    return 0;
}
