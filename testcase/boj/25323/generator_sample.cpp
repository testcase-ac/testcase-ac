#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long makeValue(long long kernel, long long base) {
    return kernel * base * base;
}

vector<long long> buildGroup(long long kernel, int count, const vector<long long>& bases) {
    vector<long long> values;
    for (int i = 0; i < count; ++i) {
        values.push_back(makeValue(kernel, bases[i % (int)bases.size()]));
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<long long> a;

    if (mode == 0) {
        int n = rnd.next(2, 16);
        vector<long long> bases = {1, 2, 3, 5, 7, 11, 13, 17};
        a = buildGroup(rnd.any(vector<long long>{1, 2, 3, 5, 6, 10}), n, bases);
        shuffle(a.begin(), a.end());
    } else if (mode == 1) {
        int n = rnd.next(3, 18);
        vector<long long> kernels = {1, 2, 3, 5, 6, 7, 10, 14};
        for (int i = 0; i < n; ++i) {
            long long kernel = rnd.any(kernels);
            long long base = rnd.next(1, 12);
            a.push_back(makeValue(kernel, base));
        }
        sort(a.begin(), a.end());
        int swaps = rnd.next(1, n);
        while (swaps--) {
            int i = rnd.next(0, n - 1);
            int j = rnd.next(0, n - 1);
            swap(a[i], a[j]);
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 14);
        vector<long long> kernels = {1, 2, 3, 5};
        for (int i = 0; i < n; ++i) {
            long long kernel = kernels[i % (int)kernels.size()];
            long long base = rnd.next(1, 10);
            a.push_back(makeValue(kernel, base));
        }
        sort(a.begin(), a.end());
    } else if (mode == 3) {
        int n = rnd.next(4, 20);
        vector<long long> kernels = {1, 2, 3, 6};
        for (int i = 0; i < n; ++i) {
            long long kernel = rnd.any(kernels);
            long long base = rnd.any(vector<long long>{1, 1, 2, 3, 3, 5});
            a.push_back(makeValue(kernel, base));
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 4) {
        vector<long long> values = {
            1,
            4,
            9,
            16,
            1000000000000000000LL,
            2,
            8,
            18,
            50,
            200000000000000000LL,
            3,
            12,
            27,
            75,
            300000000000000000LL,
        };
        int n = rnd.next(5, (int)values.size());
        shuffle(values.begin(), values.end());
        a.assign(values.begin(), values.begin() + n);
    } else {
        int n = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            long long kernel = rnd.any(vector<long long>{1, 2, 3});
            long long base = rnd.any(vector<long long>{1, 1000000000LL, 999999937LL});
            a.push_back(makeValue(kernel, base));
            if (a.back() > 1000000000000000000LL) {
                a.back() = kernel;
            }
        }
    }

    println((int)a.size());
    println(a);
    return 0;
}
