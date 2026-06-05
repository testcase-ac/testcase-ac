#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

using int64 = long long;

const int64 MIN_A = -2147483648LL;
const int64 MAX_A = 2147483647LL;

int64 randomValue(int alphabet) {
    if (rnd.next(0, 9) == 0) {
        return rnd.next(0, 1) ? MIN_A : MAX_A;
    }
    int x = rnd.next(-alphabet, alphabet);
    return x;
}

vector<int64> randomArray(int n, int alphabet) {
    vector<int64> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = randomValue(alphabet);
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 60);
    int alphabet = rnd.next(1, 7);
    vector<int64> a;

    if (mode == 0) {
        a = randomArray(n, alphabet);
    } else if (mode == 1) {
        n = rnd.next(2, 45);
        int64 value = randomValue(alphabet);
        a.assign(n, value);
    } else if (mode == 2) {
        int period = rnd.next(1, min(8, n));
        vector<int64> base = randomArray(period, alphabet);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = base[i % period];
        }
    } else if (mode == 3) {
        n = rnd.next(4, 60);
        int border = rnd.next(1, n / 2);
        a = randomArray(n, alphabet);
        for (int i = 0; i < border; ++i) {
            a[n - border + i] = a[i];
        }
    } else if (mode == 4) {
        n = rnd.next(3, 55);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = static_cast<int64>(i + 1);
        }
        if (rnd.next(0, 1)) {
            reverse(a.begin(), a.end());
        }
    } else {
        n = rnd.next(2, 50);
        int prefix = rnd.next(1, max(1, n / 3));
        int period = rnd.next(1, min(6, n));
        vector<int64> base = randomArray(period, alphabet);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = base[i % period];
        }
        for (int i = 0; i < prefix; ++i) {
            a[i] = randomValue(alphabet);
            a[n - prefix + i] = a[i];
        }
    }

    println(n);
    println(a);
    return 0;
}
