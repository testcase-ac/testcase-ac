#include "testlib.h"

#include <vector>

using namespace std;

vector<int> randomArray(int n, const vector<int>& values) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rnd.any(values);
    }
    return a;
}

int xorAll(const vector<int>& a) {
    int result = 0;
    for (int x : a) {
        result ^= x;
    }
    return result;
}

vector<int> makeCase(int mode) {
    if (mode == 0) {
        int n = rnd.next(1, 18);
        return randomArray(n, {0, 1, 2});
    }

    if (mode == 1) {
        return {3};
    }

    if (mode == 2) {
        int n = rnd.next(2, 18);
        for (int attempt = 0; attempt < 100; ++attempt) {
            vector<int> a = randomArray(n, {0, 1, 2, 3});
            bool hasThree = false;
            for (int x : a) {
                hasThree |= x == 3;
            }
            if (hasThree && xorAll(a) != 3) {
                return a;
            }
        }
        return {3, rnd.next(0, 2)};
    }

    if (mode == 3) {
        int n = rnd.next(3, 18);
        vector<int> a = randomArray(n, {0, 1, 2, 3});
        a[0] = rnd.any(vector<int>{1, 2});
        a[n - 1] = 3;
        int current = xorAll(a);
        a[1] ^= current ^ 3;
        return a;
    }

    if (mode == 4) {
        int n = rnd.next(2, 18);
        return vector<int>(n, 3);
    }

    if (mode == 5) {
        int n = rnd.next(4, 18);
        vector<int> a(n, 3);
        int inner = rnd.next(1, n - 2);
        a[inner] = rnd.any(vector<int>{0, 1, 2});
        int current = xorAll(a);
        a[1] ^= current ^ 3;
        if (a[1] == 0 && n > 4) {
            a[2] ^= 1;
            a[3] ^= 1;
        }
        return a;
    }

    int coreSize = rnd.next(2, 12);
    vector<int> a = randomArray(coreSize, {1, 2, 3});
    a[0] = 3;
    a[coreSize - 1] = rnd.any(vector<int>{1, 2, 3});
    int leftZeros = rnd.next(0, 3);
    int rightZeros = rnd.next(0, 3);
    vector<int> result(leftZeros, 0);
    result.insert(result.end(), a.begin(), a.end());
    result.insert(result.end(), rightZeros, 0);
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 16);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = tc < 7 ? tc : rnd.next(0, 6);
        vector<int> a = makeCase(mode);
        println((int)a.size());
        println(a);
    }

    return 0;
}
