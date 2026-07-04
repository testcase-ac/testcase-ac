#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static long long randomValue(int band) {
    if (band == 0) return rnd.next(1, 20);
    if (band == 1) return rnd.next(1, 1000);
    return rnd.next(1LL, 1000000000LL);
}

static vector<long long> randomValues(int n, int band) {
    vector<long long> a(n);
    for (long long& x : a) x = randomValue(band);
    return a;
}

static void rotateRandomly(vector<long long>& a) {
    int shift = rnd.next((int)a.size());
    rotate(a.begin(), a.begin() + shift, a.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n = rnd.next(2, 20);
    if (rnd.next(10) == 0) n = rnd.next(21, 80);
    int band = rnd.next(3);

    vector<long long> a;
    if (mode == 0) {
        a = randomValues(n, band);
        sort(a.begin(), a.end());
        if (rnd.next(2)) reverse(a.begin(), a.end());
    } else if (mode == 1) {
        a = randomValues(n, band);
        sort(a.begin(), a.end());
        rotateRandomly(a);
    } else if (mode == 2) {
        a = randomValues(n, band);
        sort(a.begin(), a.end(), greater<long long>());
        rotateRandomly(a);
    } else if (mode == 3) {
        int lowCount = rnd.next(1, n - 1);
        long long low = randomValue(band);
        long long high = randomValue(band);
        if (low > high) swap(low, high);
        if (low == high && high < 1000000000LL) ++high;
        a.assign(lowCount, low);
        a.resize(n, high);
        shuffle(a.begin(), a.end());
    } else if (mode == 4) {
        a = randomValues(n, band);
        sort(a.begin(), a.end());
        int split = rnd.next(1, n - 1);
        reverse(a.begin() + split, a.end());
        rotateRandomly(a);
    } else if (mode == 5) {
        a = randomValues(n, band);
        sort(a.begin(), a.end(), greater<long long>());
        int split = rnd.next(1, n - 1);
        reverse(a.begin() + split, a.end());
        rotateRandomly(a);
    } else if (mode == 6) {
        a = randomValues(n, 0);
    } else {
        n = rnd.next(2, 8);
        a = randomValues(n, 2);
        if (rnd.next(2)) {
            a[rnd.next(n)] = 1;
            a[rnd.next(n)] = 1000000000LL;
        }
    }

    println(n);
    println(a);
    return 0;
}
